#ifndef _SYSCALLS_H_
#define _SYSCALLS_H_

typedef struct s_syscall
{
	const int nparam;
	const char *name;
	const char *params;
} t_syscall;

enum
{
	NUM = '1',
	STR = '2',
	PTR = '3',
	CHAR = '4',
	STRUCT = '5',
	VOID = '0'
};

#ifndef NULL
#define NULL 0
#endif
#define SYSCALL_COUNT 300

typedef struct s_sysent {
	int ent;
	unsigned ncalls;
} t_sysent;

static const t_syscall g_syscall_table[] =
{
	{ 3,	"read", "1211"},  		/* 0 */
	{ 3,	"write", "1211"},  		/* 1 */
	{ 2,	"open", "211"},  		/* 2 */
	{ 1,	"close", "11"},  		/* 3 */
	{ 2,	"stat", "231"},  		/* 4 */
	{ 2,	"fstat", "131"},  		/* 5 */
	{ 2,	"lstat", "213"},  		/* 6 */
	{ 3,	"poll", "3111"},  		/* 7 */
	{ 3,	"lseek", "1111"},  		/* 8 */
	{ 6,	"mmap", "3111113"},  		/* 9 */
	{ 3,	"mprotect", "3111"},  		/* 10 */
	{ 2,	"munmap", "311"},  		/* 11 */
	{ 1,	"brk", "33"},			/* 12 */
	{ 4,	"rt_sigaction", "13331"},  	/* 13 */
	{ 4,	"rt_sigprocmask", "13331"},  	/* 14 */
	{ 1,	"rt_sigreturn", "11"},  	/* 15 */
	{ 3,	"ioctl", "1111"},  		/* 16 */
	{ 4,	"pread"	, "12111"},  		/* 17 */
	{ 4,	"pwrite", "12111"},  		/* 18 */
	{ 3,	"readv"	, "1311"},  		/* 19 */
	{ 3,	"writev", "1311"},  		/* 20 */
	{ 2,	"access", "211"},  		/* 21 */
	{ 1,	"pipe", "31"},  		/* 22 */
	{ 5,	"select", "133331"},  		/* 23 */
	{ 1,	"sched_yield", "01"},  		/* 24 */
	{ 5,	"mremap", "311133"},  		/* 25 */
	{ 3,	"msync", "3111"},  		/* 26 */
	{ 3,	"mincore", "3121"},  		/* 27 */
	{ 3,	"madvise", "3111"},  		/* 28 */
	{ 3,	"shmget", "1111"},  		/* 29 */
	{ 3,	"shmat", "1313"},  		/* 30 */
	{ 3,	"shmctl", "1131"},  		/* 31 */
	{ 1,	"dup", "11"},			/* 32 */
	{ 2,	"dup2", "111"},  		/* 33 */
	{ 1,	"pause", "01"},  		/* 34 */
	{ 2,	"nanosleep", "331"},  		/* 35 */
	{ 2,	"getitimer", "131"},  		/* 36 */
	{ 1,	"alarm", "11"},  		/* 37 */
	{ 3,	"setitimer", "1331"},  		/* 38 */
	{ 1,	"getpid", "01"},  		/* 39 */
	{ 4,	"sendfile", "11311"},  		/* 40 */
	{ 3,	"socket", "1111"},  		/* 41 */
	{ 3,	"connect", "1311"},  		/* 42 */
	{ 3,	"accept", "1331"},  		/* 43 */
	{ 6,	"sendto", "1211311"},  		/* 44 */
	{ 6,	"recvfrom", "1211331"},  	/* 45 */
	{ 3,	"sendmsg", "1311"},  		/* 46 */
	{ 3,	"recvmsg", "1311"},  		/* 47 */
	{ 2,	"shutdown", "111"},  		/* 48 */
	{ 3,	"bind", "1311"},  		/* 49 */
	{ 2,	"listen", "111"},  		/* 50 */
	{ 3,	"getsockname", "1331"},  	/* 51 */
	{ 3,	"getpeername", "1331"},  	/* 52 */
	{ 4,	"socketpair", "11131"},  	/* 53 */
	{ 5,	"setsockopt", "111311"},  	/* 54 */
	{ 5,	"getsockopt", "111331"},  	/* 55 */
	{ 5,	"clone", "331331"},  		/* 56 */
	{ 1,	"fork", "01"},  		/* 57 */
	{ 1,	"vfork", "01"},  		/* 58 */
	{ 3,	"execve", "2111"},  		/* 59 */
	{ 1,	"_exit", "10"},  		/* 60 */
	{ 4,	"wait4", "13131"},  		/* 61 */
	{ 2,	"kill", "111"},  		/* 62 */
	{ 1,	"uname", "31"},  		/* 63 */
	{ 3,	"semget", "1111"},  		/* 64 */
	{ 3,	"semop", "1311"},  		/* 65 */
	{ 4,	"semctl", "11131"},  		/* 66 */
	{ 1,	"shmdt", "31"},  		/* 67 */
	{ 2,	"msgget", "111"},  		/* 68 */
	{ 4,	"msgsnd", "13111"},  		/* 69 */
	{ 5,	"msgrcv", "121111"},  		/* 70 */
	{ 3,	"msgctl", "1131"},  		/* 71 */
	{ 3,	"fcntl", "1131"},  		/* 72 */
	{ 2,	"flock", "111"},  		/* 73 */
	{ 1,	"fsync", "11"},  		/* 74 */
	{ 1,	"fdatasync", "11"},  		/* 75 */
	{ 2,	"truncate", "211"},  		/* 76 */
	{ 2,	"ftruncate", "111"},  		/* 77 */
	{ 3,	"getdents", "1211"},  		/* 78 */
	{ 2,	"getcwd", "211"},  		/* 79 */
	{ 1,	"chdir", "21"},  		/* 80 */
	{ 1,	"fchdir", "11"},  		/* 81 */
	{ 2,	"rename", "221"},  		/* 82 */
	{ 2,	"mkdir", "211"},  		/* 83 */
	{ 1,	"rmdir", "21"},  		/* 84 */
	{ 2,	"creat", "211"},  		/* 85 */
	{ 2,	"link", "221"},  		/* 86 */
	{ 1,	"unlink", "21"},  		/* 87 */
	{ 2,	"symlink", "221"},  		/* 88 */
	{ 3,	"readlink", "2211"},  		/* 89 */
	{ 2,	"chmod", "211"},  		/* 90 */
	{ 2,	"fchmod", "111"},  		/* 91 */
	{ 3,	"chown", "2111"},  		/* 92 */
	{ 3,	"fchown", "1111"},  		/* 93 */
	{ 3,	"lchown", "2111"},  		/* 94 */
	{ 1,	"umask", "11"},  		/* 95 */
	{ 2,	"gettimeofday", "331"},  	/* 96 */
	{ 2,	"getrlimit", "131"},  		/* 97 */
	{ 2,	"getrusage", "131"},  		/* 98 */
	{ 1,	"sysinfo", "31"},  		/* 99 */
	{ 1,	"times", "31"},  		/* 100 */
	{ 4,	"ptrace", "11331"},  		/* 101 */
	{ 1,	"getuid", "01"},  		/* 102 */
	{ 3,	"syslog", "1211"},  		/* 103 */
	{ 1,	"getgid", "01"},  		/* 104 */
	{ 1,	"setuid", "11"},  		/* 105 */
	{ 1,	"setgid", "11"},  		/* 106 */
	{ 1,	"geteuid", "01"},  		/* 107 */
	{ 1,	"getegid", "01"},  		/* 108 */
	{ 2,	"setpgid", "111"},  		/* 109 */
	{ 1,	"getppid", "11"},  		/* 110 */
	{ 1,	"getpgrp", "01"},  		/* 111 */
	{ 1,	"setsid", "01"},  		/* 112 */
	{ 2,	"setreuid", "111"},  		/* 113 */
	{ 2,	"setregid", "111"},  		/* 114 */
	{ 2,	"getgroups", "131"},  		/* 115 */
	{ 2,	"setgroups", "131"},  		/* 116 */
	{ 3,	"setresuid", "1111"},  		/* 117 */
	{ 3,	"getresuid", "3331"},  		/* 118 */
	{ 3,	"setresgid", "1111"},  		/* 119 */
	{ 3,	"getresgid", "3331"},  		/* 120 */
	{ 1,	"getpgid", "11"},  		/* 121 */
	{ 1,	"setfsuid", "11"},  		/* 122 */
	{ 1,	"setfsgid", "11"},  		/* 123 */
	{ 1,	"getsid", "11"},  		/* 124 */
	{ 2,	"capget", "331"},  		/* 125 */
	{ 2,	"capset", "331"},  		/* 126 */
	{ 2,	"rt_sigpending", "311"},  	/* 127 */
	{ 4,	"rt_sigtimedwait", "33311"},  	/* 128 */
	{ 3,	"rt_sigqueueinfo", "1131"},  	/* 129 */
	{ 2,	"rt_sigsuspend", "331"},  	/* 130 */
	{ 2,	"sigaltstack", "331"},  	/* 131 */
	{ 2,	"utime", "231"},  		/* 132 */
	{ 3,	"mknod", "2111"},  		/* 133 */
	{ 1,	"uselib", "21"},  		/* 134 */
	{ 1,	"personality", "11"},  		/* 135 */
	{ 2,	"ustat", "131"},  		/* 136 */
	{ 2,	"statfs", "231"},  		/* 137 */
	{ 2,	"fstatfs", "131"},  		/* 138 */
	{ 3,	"sysfs", "1331"},  		/* 139 */
	{ 2,	"getpriority", "111"},  	/* 140 */
	{ 3,	"setpriority", "1111"},  	/* 141 */
	{ 2,	"sched_setparam", "131"},  	/* 142 */
	{ 2,	"sched_getparam", "131"},  	/* 143 */
	{ 3,	"sched_setscheduler", "1131"},  /* 144 */
	{ 1,	"sched_getscheduler", "11"},  	/* 145 */
	{ 1,	"sched_get_priority_max", "11"},/* 146 */
	{ 1,	"sched_get_priority_min", "11"},/* 147 */
	{ 2,	"sched_rr_get_interval", "131"},/* 148 */
	{ 2,	"mlock", "311"},  		/* 149 */
	{ 2,	"munlock", "311"},  		/* 150 */
	{ 1,	"mlockall", "11"},  		/* 151 */
	{ 1,	"munlockall", "01"},  		/* 152 */
	{ 1,	"vhangup", "01"},  		/* 153 */
	{ 3,	"modify_ldt", "1311"},  	/* 154 */
	{ 2,	"pivot_root", "221"},  		/* 155 */
	{ 1,	"_sysctl", "31"},  		/* 156 */
	{ 5,	"prctl", "111111"},  		/* 157 */
	{ 2,	"arch_prctl", "131"},  		/* 158 */
	{ 1,	"adjtimex", "31"},  		/* 159 */
	{ 2,	"setrlimit", "131"},  		/* 160 */
	{ 1,	"chroot", "21"},  		/* 161 */
	{ 1,	"sync", "00"},  		/* 162 */
	{ 1,	"acct", "21"},  		/* 163 */
	{ 2,	"settimeofday", "331"},  	/* 164 */
	{ 5,	"mount", "222131"},  		/* 165 */
	{ 2,	"umount2", "211"}, 		/* 166 */
	{ 2,	"swapon", "211"},  		/* 167 */
	{ 1,	"swapoff", "21"},  		/* 168 */
	{ 3,	"reboot", "1131"},  		/* 169 */
	{ 2,	"sethostname", "211"},  	/* 170 */
	{ 2,	"setdomainname", "211"},  	/* 171 */
	{ 1,	"iopl", "11"},  		/* 172 */
	{ 3,	"ioperm", "1111"},  		/* 173 */
	{ 2,	"create_module", "213"},  	/* 174 */
	{ 2,	"init_module", "231"},  	/* 175 */
	{ 1,	"delete_module", "21"},  	/* 176 */
	{ 1,	"get_kernel_syms", "31"},  	/* 177 */
	{ 5,	"query_module", "212131"},  	/* 178 */
	{ 4,	"quotactl", "14131"},  		/* 179 */
	{ 3,	"nfsservctl", "1331"},  	/* 180 */
	{ 5,	"getpmsg", NULL}, 		/* 181 */
	{ 5,	"putpmsg", NULL}, 		/* 182 */
	{ 5,	"afs_syscall", NULL},  		/* 183 */
	{ 3,	"tuxcall", NULL}, 		/* 184 */
	{ 3,	"security", NULL}, 		/* 185 */
	{ 1,	"gettid", "01"}, 		/* 186 */
	{ 3,	"readahead", "1111"}, 		/* 187 */
	{ 5,	"setxattr", "223111"}, 		/* 188 */
	{ 5,	"lsetxattr", "223111"}, 	/* 189 */
	{ 5,	"fsetxattr", "123111"}, 	/* 190 */
	{ 4,	"getxattr", "22311"}, 		/* 191 */
	{ 4,	"lgetxattr", "22311"}, 		/* 192 */
	{ 4,	"fgetxattr", "12311"}, 		/* 193 */
	{ 3,	"listxattr", "2211"}, 		/* 194 */
	{ 3,	"llistxattr", "2211"}, 		/* 195 */
	{ 3,	"flistxattr", "1211"}, 		/* 196 */
	{ 2,	"removexattr", "221"}, 		/* 197 */
	{ 2,	"lremovexattr", "221"}, 	/* 198 */
	{ 2,	"fremovexattr", "121"}, 	/* 199 */
	{ 2,	"tkill", "111"}, 		/* 200 */
	{ 1,	"time", "33"},  		/* 201 */
	{ 6,	"futex", "3113311"}, 		/* 202 */
	{ 3,	"sched_setaffinity", "1131"},	/* 203 */
	{ 3,	"sched_getaffinity", "1131"},	/* 204 */
	{ 1,	"set_thread_area", "31"}, 	/* 205 */
	{ 2,	"io_setup", "131"}, 		/* 206 */
	{ 1,	"io_destroy", "31"}, 		/* 207 */
	{ 5,	"io_getevents", "311331"}, 	/* 208 */
	{ 3,	"io_submit", "3131"}, 		/* 209 */
	{ 3,	"io_cancel", "3331"}, 		/* 210 */
	{ 1,	"get_thread_area", "31" }, 	/* 211 */
	{ 3,	"lookup_dcookie", "1211"}, 	/* 212 */
	{ 1,	"epoll_create", "11"}, 		/* 213 */
	{ 4,	"epoll_ctl_old", NULL}, 	/* 214 */
	{ 4,	"epoll_wait_old", NULL}, 	/* 215 */
	{ 5,	"remap_file_pages", "311111"}, 	/* 216 */
	{ 3,	"getdents64", "1311"}, 		/* 217 */
	{ 1,	"set_tid_address", "31"}, 	/* 218 */
	{ 1,	"restart_syscall", "01"}, 	/* 219 */
	{ 4,	"semtimedop", "13131"}, 	/* 220 */
	{ 4,	"fadvise64", "11111"}, 		/* 221 */
	{ 3,	"timer_create", "1331"}, 	/* 222 */
	{ 4,	"timer_settime", "11331"}, 	/* 223 */
	{ 2,	"timer_gettime", "131"}, 	/* 224 */
	{ 1,	"timer_getoverrun", "11"}, 	/* 225 */
	{ 1,	"timer_delete", "11"}, 		/* 226 */
	{ 2,	"clock_settime", "131"}, 	/* 227 */
	{ 2,	"clock_gettime", "131"}, 	/* 228 */
	{ 2,	"clock_getres", "131"}, 	/* 229 */
	{ 4,	"clock_nanosleep", "11331"}, 	/* 230 */
	{ 1,	"exit_group", "10"}, 		/* 231 */
	{ 4,	"epoll_wait", "13111"}, 	/* 232 */
	{ 4,	"epoll_ctl", "11131"}, 		/* 233 */
	{ 3,	"tgkill", "1111"}, 		/* 234 */
	{ 2,	"utimes", "231"}, 		/* 235 */
	{ 5,	"vserver", NULL}, 		/* 236 */
	{ 6,	"mbind", "3113111"}, 		/* 237 */
	{ 3,	"set_mempolicy", "1311"}, 	/* 238 */
	{ 5,	"get_mempolicy", "331111"}, 	/* 239 */
	{ 4,	"mq_open", "21133"}, 		/* 240 */
	{ 1,	"mq_unlink", "21"}, 		/* 241 */
	{ 5,	"mq_timedsend", "121331"}, 	/* 242 */
	{ 5,	"mq_timedreceive", "121331"}, 	/* 243 */
	{ 2,	"mq_notify", "131"}, 		/* 244 */
	{ 3,	"mq_getsetattr", "1331"}, 	/* 245 */
	{ 4,	"kexec_load", "11311"}, 	/* 246 */
	{ 4,	"waitid", "11311"}, 		/* 247 */
	{ 5,	"add_key", "223111"}, 		/* 248 */
	{ 4,	"request_key", "22211"}, 	/* 249 */
	{ 2,	"keyctl", "131"}, 		/* 250 */
	{ 3,	"ioprio_set", "1111"}, 		/* 251 */
	{ 2,	"ioprio_get", "111"}, 		/* 252 */
	{ 1,	"inotify_init", "01"}, 		/* 253 */
	{ 3,	"inotify_add_watch", "1211"}, 	/* 254 */
	{ 2,	"inotify_rm_watch", "111"}, 	/* 255 */
	{ 4,	"migrate_pages", "11331"}, 	/* 256 */
	{ 4,	"openat", "12131"}, 		/* 257 */
	{ 3,	"mkdirat", "1211"}, 		/* 258 */
	{ 4,	"mknodat", "12111"}, 		/* 259 */
	{ 5,	"fchownat", "121111"}, 		/* 260 */
	{ 3,	"futimesat", "1231"}, 		/* 261 */
	{ 4,	"newfstatat", NULL}, 		/* 262 */
	{ 3,	"unlinkat", "1211"}, 		/* 263 */
	{ 4,	"renameat", "12121"}, 		/* 264 */
	{ 5,	"linkat", "121211"}, 		/* 265 */
	{ 3,	"symlinkat", "2121"}, 		/* 266 */
	{ 4,	"readlinkat", "12211"}, 	/* 267 */
	{ 4,	"fchmodat", "12111"}, 		/* 268 */
	{ 4,	"faccessat", "12111"}, 		/* 269 */
	{ 6,	"pselect6", "1333331"}, 	/* 270 */
	{ 4,	"ppoll", "31331"}, 		/* 271 */
	{ 1,	"unshare", "11"}, 		/* 272 */
	{ 2,	"set_robust_list", "311"}, 	/* 273 */
	{ 3,	"get_robust_list", "1331"}, 	/* 274 */
	{ 6,	"splice", "1313111"}, 		/* 275 */
	{ 4,	"tee", "11111"}, 		/* 276 */
	{ 4,	"sync_file_range", "11111"}, 	/* 277 */
	{ 4,	"vmsplice", "13111"}, 		/* 278 */
	{ 6,	"move_pages", "1133311"}, 	/* 279 */
	{ 4,	"utimensat", "12311"}, 		/* 280 */
	{ 5,	"epoll_pwait", "131131"}, 	/* 281 */
	{ 3,	"signalfd", "1311"}, 		/* 282 */
	{ 2,	"timerfd_create", "111"}, 	/* 283 */
	{ 2,	"eventfd", "111"}, 		/* 284 */
	{ 4,	"fallocate", "11111"}, 		/* 285 */
	{ 4,	"timerfd_settime", "11331"}, 	/* 286 */
	{ 2,	"timerfd_gettime", "131"}, 	/* 287 */
	{ 4,	"accept4", "13311"}, 		/* 288 */
	{ 3,	"signalfd4", "1311"}, 		/* 289 */
	{ 2,	"eventfd2", "111"}, 		/* 290 */
	{ 1,	"epoll_create1", "11"}, 	/* 291 */
	{ 3,	"dup3", "1111"}, 		/* 292 */
	{ 2,	"pipe2", "311"}, 		/* 293 */
	{ 1,	"inotify_init1", "11"}, 	/* 294 */
	{ 4,	"preadv", "13111"}, 		/* 295 */
	{ 4,	"pwritev", "13111"}, 		/* 296 */
	{ 4,	"rt_tgsigqueueinfo", "11131"}, 	/* 297 */
	{ 5,	"perf_event_open", NULL}, 	/* 298 */
	{ 5,	"recvmmsg", "131131"} 		/* 299 */
};

static const int g_syscall_count = sizeof(g_syscall_table) / sizeof(t_syscall);
#define SYSCALL_COUNT 300

#endif
