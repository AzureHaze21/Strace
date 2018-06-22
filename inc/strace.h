#ifndef _STRACE_H_
#define _STRACE_H_

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/reg.h>
#include <stdarg.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/user.h>
#include <unistd.h>
#include <errno.h>
#include <stdarg.h>

#define DEFAULT_STRLEN 32

#define ERR(...)	(fprintf(stderr, __VA_ARGS__))
#define FMT_COMMA()	(printf(", "))
#define FMT_VOID()	(printf("?"))
#define FMT_NUM(arg)	(printf("%d", (int)arg))
#define FMT_CHAR(arg)	(printf("%c", (char)arg))
#define FMT_PTR(arg)	(printf(arg == 0 ? "NULL" : "0x%lx", arg))

#define IS_SPACE(c) (c == '\n' ||		\
		     c == '\t' ||		\
		     c == '\r' ||		\
		     c == '\v' ||		\
		     c == '\f')

#define ESC_SPACE(c) (c == '\n' ? "\\n" :	\
		      c == '\t' ? "\\t" :	\
		      c == '\r' ? "\\r" :	\
		      c == '\v' ? "\\v" :	\
		      c == '\f' ? "\\f" : "")

typedef unsigned long UL;
typedef struct user_regs_struct t_regs;
typedef struct s_flags t_flags;

struct s_flags
{
	short s;
	short p;
	short c;
	short i;
	short bin;
};

void format_args(pid_t pid, t_regs r);
void init(int argc, char **argv, char **envp);
int is_syscall(int id);
int strace(const int pid, const int is_proc);
void format_single(pid_t, unsigned int, t_regs, UL);
void sighandler(int __attribute__((__unused__))sig);
void init_sigs(void (*handler)(int));
int die(const char *fmt, ...);
int print_sc_count(const size_t *sc_count);
int count_sc(int pid);

extern t_flags g_flags;
extern int g_target;

static const char fmt_usage[] =
	"USAGE : ./strace [-s] [-p <pid>|<command>]\n";

__attribute((unused)) static const char fmt_req_arg[] =
	"strace: option requires an argument -- '%c'\n"	\
	"Try 'strace -h' for more information.\n";

static const char fmt_invalid_opt[] =
	"strace: invalid option -- '%c'\n"			\
	"Try 'strace -h' for more information.\n";

static const char fmt_stat_err[] =
	"strace: Can't stat '%s': "				\
	"No such file or directory\n";

#endif
