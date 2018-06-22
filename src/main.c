#include <unistd.h>

#include "strace.h"
#include "syscalls.h"

t_flags g_flags = { 0 };
int g_target = -1;

static int pid_attach(const int pid)
{
	int ret;

	init_sigs(sighandler);
	ret = ptrace(PTRACE_ATTACH, pid, 0, 0);
	if (ret == -1) {
		printf("strace: attach: ptrace(PTRACE_ATTACH, ...): "	\
		       "No such process\n");
		return (-1);
	}
	g_target = pid;
	printf("strace: Process %d attached\n", pid);
	return (strace(pid, 1));
}

static void print_env(char **params, char **envp)
{
	int i = -1;
	int j = -1;

	printf("execve(\"%s\", [", params[0]);
	while (envp[++i]) {}
	while (params[++j])
		printf((j > 0 ? ", \"%s\"" : "\"%s\""), params[j]);
	printf("], [/* %d vars */]) = 0\n", i);
}

static int init_child(const int argc, char **argv, char **envp)
{
	char *params[argc + 1];
	int ret = 0;

	params[argc] = NULL;
	for (int i = 0; i < argc; i++) {
		params[i] = argv[i];
	}
	if (!g_flags.c && !g_flags.i)
		print_env(params, envp);
	ret = ptrace(PTRACE_TRACEME);
	if (ret == -1) {
		ERR("PTRACE_ERROR\n");
		return (-1);
	}
	ret = kill(getpid(), SIGSTOP);
	return (execvp(params[0], params));
}

static int parse_args(const int argc, char **argv)
{
	for (int i = 0; i < argc; i++) {
		if (*argv[i] == '-' && *(argv[i] + 1)) {
			if (!strcmp(argv[i], "-s"))
				g_flags.s = 1;
			else if (!strcmp(argv[i], "-p"))
				g_flags.p = 1;
			else if (!strcmp(argv[i], "-c"))
				g_flags.c = 1;
			else if (!strcmp(argv[i], "-i"))
				g_flags.i = 1;
			else if (!g_flags.bin)
				die(fmt_invalid_opt, *(argv[i] + 1));
		}				
		else if (!g_flags.bin) {
			g_flags.bin = i;
		}
	}
	return (g_flags.bin == 1);
}

int main(int argc, char **argv, char **envp)
{
	int pid = 0;

	if (argc < 2)
		return (die(fmt_usage));
	if (!strcmp(argv[1], "--help") ||
	    parse_args(argc - 1, argv + 1) == -1)
		return (die(fmt_usage));
	if (!g_flags.p && access(argv[g_flags.bin + 1], F_OK) == -1)
		return (die(fmt_stat_err, argv[g_flags.bin + 1]));
	if (g_flags.p != 0)
		return (pid_attach(atoi(argv[g_flags.bin + 1])));
	pid = fork();
	if (pid == 0)
		return (init_child(argc - g_flags.bin - 1,
				   argv + g_flags.bin + 1, envp));
	else
		!g_flags.c ? strace(pid, 0) : count_sc(pid);
	return (0);
}
