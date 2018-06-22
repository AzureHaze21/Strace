#include <pthread.h>
#include "strace.h"
#include "syscalls.h"

inline __attribute__((always_inline))
int is_syscall(int id)
{
	return (id > -1 && id < g_syscall_count);
}

static void format_default(t_regs r)
{
	const t_syscall *sc = &g_syscall_table[(int)r.orig_rax];
	const void* p_regs[6] = { &r.rdi, &r.rsi, &r.rdx,
				  &r.rcx, &r.r8, &r.r9 };
	const char ret = sc->params[sc->nparam];

	printf("%s(", sc->name);
	for (int i = 0; i < sc->nparam; i++) {
		if (i && i < sc->nparam)
			printf(", ");
		printf("0x%x", *(unsigned*)(p_regs[i]));
	}
	if (ret == VOID)
		printf(") = ?\n");
	else
		printf(") = 0x%x\n", (unsigned)r.rax);
}

int strace(const int pid, const int is_proc)
{
	int st;
	int first = g_flags.i ? 1 : 0;
	t_regs regs = { 0 };
	int count = 0;

	waitpid(pid, &st, 0);
	if (!WIFSTOPPED(st))
		return (-1);
	ptrace(PTRACE_GETREGS, pid, NULL, &regs);
	while (!WIFEXITED(st)) {
		ptrace(PTRACE_SINGLESTEP, pid, 0, 0);
		waitpid(pid, &st, 0);
		ptrace(PTRACE_GETREGS, pid, NULL, &regs);
		first = (int)regs.orig_rax == 12 ? 1 : first;
		if (is_syscall((int)regs.orig_rax) && (is_proc || first)) {
			if (g_flags.i) printf("[%016llx] ", (long long unsigned)regs.rip);
			g_flags.s ? format_args(pid, regs) : format_default(regs);
		}
	}
	count += g_flags.i ? printf("[%016llx] ", (long long unsigned)regs.rip + 2) : 0;
	count += printf("exit_group(%d)", (int)regs.rdi);
	printf("%*c= ?\n", g_flags.s ? 40 - count : 1, ' ');
	if (g_flags.i) printf("[????????????????] ");
	printf("+++ exited with %d +++\n", (int)regs.rdi);
	return (0);
}
