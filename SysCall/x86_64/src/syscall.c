/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:17:57 by abelov            #+#    #+#             */
/*   Updated: 2024/01/06 17:17:59 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <sysexits.h>
#include <stdarg.h>

__attribute__((target("arch=haswell")))
int	ft_strlen(char *str)
{
	int cnt;

	cnt = 0;
	while (*str++)
		cnt++;
	return (cnt);
}

int	*__errno_location(void)
{
	static int	errnum;

	return (&errnum);
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
int	ft_syscall3(int num, int arg1, long arg2, int arg3)
{
	int	res;

	__asm__ volatile (
		"syscall"
		: "=a" (res)
		: "a" (num), "D" (arg1), "S" (arg2), "d" (arg3)
		: "memory", "cc");
	if (-125 <= res && res < 0) /* Check for error */
	{
		errno = -res;
		res = -1;
	}
	return (res);
}

/**
 * https://git.musl-libc.org/cgit/musl/tree/arch/x86_64/syscall_arch.h
 */
static __inline__ __attribute__((always_inline)) __attribute__((unused))
long	syscall4(long n, long a1, long a2, long a3, long a4)
{
	long				ret;
	register long r10	__asm__("r10");

	r10 = a4;
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "a"(n), "D"(a1), "S"(a2), "d"(a3), "r"(r10)
		: "memory", "rcx", "r11");
	return (ret);
}

void	ft_exit(int exit_code)
{
	__asm__ volatile ("syscall" :: "a" (__NR_exit), "D" (exit_code));
	__asm__ volatile (
		"movl $"STRINGIFY(SYS_exit)",%eax\n\t" /* 	; exit(" */
		"movl $0,%edi\n\t" /* 						;   EXIT_SUCCESS" */
		"syscall"); /* 								; );" */
	__asm__ volatile (
		"movl %[syscall_number],%%eax\n\t" /*	; exit(" */
		"movl $0,%%edi\n\t" /*					;   EXIT_SUCCESS" */
		"syscall" /*							; );" */
		:: [syscall_number] "r" (SYS_exit)
		: "eax"); /* these registers are clobbered */
}

/**
 * syscall arguments are typically passed in registers and interpreted
 * as integers or pointers, which are effectively the same size.
 *
 * Use the syscall instruction (direct syscall implementation).
 * Get up to 6 arguments (Linux syscall ABI typically supports up to 6 args)
 *
 * @see https://fschoenberger.dev/syscalls-by-hand/
 */
long	ft_syscall_x64(long num, ...)
{
	va_list				args;
	long				result;
	register long r10	__asm__("r10");
	register long r8	__asm__("r8");
	register long r9	__asm__("r9");

	va_start(args, num);
	r10 = va_arg(args, long);
	r8 = va_arg(args, long);
	r9 = va_arg(args, long);
	va_end(args);
	__asm__ __volatile__ (
			"syscall"
			: "=a" (result)
			: "a" (num), "D" (va_arg(args, long)), "S" (va_arg(args, long)),
	"d"(va_arg(args, long)), "r"(r10), "r"(r8), "r"(r9)
			: "rcx", "r11", "memory"
			);
	return (result);
}

/**
 * https://gcc.gnu.org/wiki/ConvertBasicAsmToExtended
 */
void	_start(int argc, char *argv[])
{
	char	*str;
	size_t	len;

	str = "Wello Horld!\n";
	len = ft_strlen(str);
	ft_syscall3(__NR_write, STDOUT_FILENO, (long)str, len);
	ft_exit(EX_OK);
}
