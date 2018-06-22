#include "syscalls.h"
#include "strace.h"

static int count(int inc)
{
	static int c = 0;
	c += inc; 
	return (c);
}

static inline __attribute__((always_inline))
int use_hex(char c)
{
	return ((c < ' ' && (unsigned)(c - 9) >= 5) || c > 0x7e);
}

void format_str(pid_t pid, UL arg, int syscall)
{
	int i = 0;
	char val;
	char first;

	count(printf("\""));
	first = ptrace(PTRACE_PEEKTEXT, pid, arg);
	while (i < DEFAULT_STRLEN)
	{
		val = ptrace(PTRACE_PEEKTEXT, pid, (arg + i++));
		if (!val && syscall != 0)
			break;
		if (use_hex(val) && use_hex(first))
			count(printf("\\%o", (unsigned char)val));
		else if (IS_SPACE(val))
			count(printf("%s", ESC_SPACE(val)));
		else
			count(printf("%c", val));
	}
	count(printf("\""));
	if (i == DEFAULT_STRLEN)
		count(printf("..."));
}

void format_single(pid_t pid,
		   unsigned int off,
		   t_regs r,
		   UL arg)
{
	const int id = (int)r.orig_rax;
	const t_syscall *sc = (t_syscall*)&g_syscall_table[id];
	const char *params = (char *)sc->params;
	const unsigned nparam = (unsigned)sc->nparam;
	const char c = params[off];

	if (off != 0 && off != nparam)
		count(FMT_COMMA());
	switch (c) {
	case VOID:	count(FMT_VOID()); break;
	case NUM:	count(FMT_NUM(arg)); break;
	case STR:	format_str(pid, arg, (int)r.orig_rax); break;
	case PTR:	count(FMT_PTR(arg)); break;
	case CHAR:	count(FMT_CHAR(arg)); break;
	}
}

void format_args(pid_t pid, t_regs r)
{
	int i = -1;
	const t_syscall *sc  = &g_syscall_table[(int)r.orig_rax];
	const void* p_regs[6] = { &r.rdi, &r.rsi, &r.rdx,
				  &r.rcx, &r.r8, &r.r9 };

	count(-count(0));
	count(printf("%s(", sc->name));
	while (++i < sc->nparam)
		format_single(pid, i, r, *(UL*)p_regs[i]);
	count(printf(")"));
	if (count(0) < 42)
		printf("%*c= ", 42 - count(0) - 2, ' ');
	else
		printf(" = ");
	format_single(pid, sc->nparam, r, r.rax);
	printf("\n");
}
