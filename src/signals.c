#include <unistd.h>
#include <stdio.h>
#include "strace.h"

void sighandler(int __attribute__((__unused__))sig)
{
	ptrace(PTRACE_CONT, g_target, 0, 0);
	ptrace(PTRACE_DETACH, g_target, 0, 0);
	printf("strace: Process %d detached\n", g_target);
	printf(" <detached ...>\n");
	exit(84);
}

void init_sigs(void (*handler)(int))
{
	signal(SIGINT,	handler);
	signal(SIGTERM, handler);
	signal(SIGQUIT, handler);		
}
