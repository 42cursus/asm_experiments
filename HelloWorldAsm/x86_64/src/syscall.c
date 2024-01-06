#define _GNU_SOURCE
#include <unistd.h>
#include <errno.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

#define QUAUX(X) #X
#define QU(X) QUAUX(X)

int	*__errno_location (void)
{
	static int errnum;
	return &errnum;
}

/**
 * from man SYSCALL(2)
 * The first table lists the instruction used to transition to kernel mode
 * Arch/ABI    Instruction           System  Ret  Ret  Error
 *                                   call #  val  val2
 * ──────────────────────────────────────────────────────────
 * i386        int $0x80             eax     eax  edx  -
 * x86-64      syscall               rax     rax  rdx  -
 *
 * The second table registers used to pass the system call arguments.
 * Arch/ABI      arg1  arg2  arg3  arg4  arg5  arg6  arg7
 * ───────────────────────────────────────────────────────
 * i386          ebx   ecx   edx   esi   edi   ebp   -
 * x86-64        rdi   rsi   rdx   r10   r8    r9    -
 */
#include <errno.h>

int syscall3(int num, int arg1, long arg2, int arg3) {
	int res;

	__asm__ (
			"syscall"
			: "=a" (res)
			: "a" (num), "D" (arg1), "S" (arg2), "d" (arg3)
			: "memory", "cc"
			);

	/* Check for error */
	if (-125 <= res && res < 0) {
		errno = -res;
		res = -1;
	}

	return res;
}

void ft_exit(int exit_code)
{
	__asm__ (
			"syscall"
			:: "a" (__NR_exit), "D" (exit_code)
			);
}

/**
 * https://gcc.gnu.org/wiki/ConvertBasicAsmToExtended
 */
int _start(int argc, char *argv[])
{
	int src = 1;
	int dst;

	char	*str;
	size_t	len;

	str = "Wello Horld!\n";
	len = 13;  /* ft_strlen(str); */

	syscall3(__NR_write, STDOUT_FILENO, (long)str, len);

	ft_exit(0);

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
			"movl $"QU(SYS_exit)",%eax\n\t" /* ; exit(" */
			"movl $0,%edi\n\t"  /* ;   EXIT_SUCCESS" */
			"syscall"	  /* ; );" */
			);

	return (0);
}
