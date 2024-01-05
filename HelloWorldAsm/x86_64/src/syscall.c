#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

#define QUAUX(X) #X
#define QU(X) QUAUX(X)


int _start(int argc, char *argv[])
{
	int src = 1;
	int dst;

	__asm__ ("mov %1, %0\n\t"
		 "add $1, %0"
			: "=r" (dst)
			: "r" (src)
			: "cc"
	);

	__asm__ volatile(
			"movl %[syscall_number],%%eax\n\t" /* ; exit(" */
			"movl $0,%%edi\n\t"  /* ;   EXIT_SUCCESS" */
			"syscall"	  /* ; );" */
			:: [syscall_number] "r" (SYS_exit)
			: "eax"
			);

	__asm__ volatile(
			"movl $"QU(SYS_exit) ",%eax\n\t" /* ; exit(" */
			"movl $0,%edi\n\t"  /* ;   EXIT_SUCCESS" */
			"syscall"	  /* ; );" */
	);
}
