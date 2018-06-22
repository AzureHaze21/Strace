#include <stdio.h>
#include <unistd.h>

#include "strace.h"
#include "syscalls.h"

static const char header[] = "%6.6s %9.9s %s\n";
static const char data[] = "%6.2f %9u %s (%d)\n";
static const char summary[] = "%6.2f %9lu %s\n";
static const char dashes[] = "----------------";

static inline int syscall_cmp(const void *a, const void *b)
{
	return (((t_sysent*)(a))->ncalls < ((t_sysent*)(b))->ncalls);
}

static void print_entries(const t_sysent *entries, const size_t total)
{
	printf(header, "% time", "calls", "syscall (#)");
	printf(header, dashes, dashes, dashes);
	for (int i = 0; i < g_syscall_count; ++i) {
		if (entries[i].ncalls > 0) {
			printf(data,
			       ((float)entries[i].ncalls/(float)total)*100.f,
			       entries[i].ncalls,
			       g_syscall_table[entries[i].ent].name,
			       entries[i].ent);
		}
	}
	printf(header, dashes, dashes, dashes);
	printf(summary, 100.f, total, "total");
}

int print_sc_count(const size_t *sc_count)
{		
	size_t total = 0;
	t_sysent *entries = (t_sysent*)calloc(g_syscall_count,
					      sizeof(t_sysent));

	if (!entries) return (84);
	for (int i = 0; i < g_syscall_count; ++i) {
		if (sc_count[i] > 0)
			entries[i] = (t_sysent){ i, sc_count[i] };
		total += sc_count[i];
	}
	qsort((void*)entries, g_syscall_count,
	      sizeof(t_sysent), syscall_cmp);
	print_entries(entries, total);
	free(entries);
	return (0);
}

int count_sc(int pid)
{
	int st;
	t_regs regs = { 0 };
	size_t count[SYSCALL_COUNT] = { 0 };

	waitpid(pid, &st, 0);
	if (!WIFSTOPPED(st))
		return (-1);
	while (!WIFEXITED(st)) {
		ptrace(PTRACE_SINGLESTEP, pid, 0, 0);
		waitpid(pid, &st, 0);
		ptrace(PTRACE_GETREGS, pid, NULL, &regs);
		if (is_syscall((int)regs.orig_rax))
			count[(int)regs.orig_rax] += 1;
	}
	return (print_sc_count(count));
}
