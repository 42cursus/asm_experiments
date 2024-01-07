/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:54:32 by abelov            #+#    #+#             */
/*   Updated: 2024/01/06 16:54:34 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <errno.h>
#include <asm/unistd.h>
#include <unistd.h>

int	*__errno_location(void)
{
	static int	errnum;

	return (&errnum);
}

void	ft_exit(int exit_code)
{
	__asm__ volatile ("int $0x80" :: "a"(__NR_exit), "b"(exit_code));
}

/**
 * https://gcc.gnu.org/onlinedocs/gcc/Constraints.html
 * https://gcc.gnu.org/onlinedocs/gcc/Simple-Constraints.html
 * https://gcc.gnu.org/onlinedocs/gcc/Modifiers.html
 * https://gcc.gnu.org/onlinedocs/gcc/extensions-to-the-c-language-family
 * 	/how-to-use-inline-assembly-language-in-c-code.html
 * 	asm asm-qualifiers ( AssemblerTemplate
                      : OutputOperands
                      : InputOperands
                      : Clobbers
                      : GotoLabels)
 */
int	syscall3(int num, int arg1, long arg2, int arg3)
{
	int	res;

	__asm__ volatile
	("int $0x80" 		/* make the request to the OS */
		: "=a" (res),	/* return result in eax ("a") */
		  "+b" (arg1),	/* pass arg1 in ebx ("b") [as a "+" output because the syscall may change it] */
		  "+c" (arg2),	/* pass arg2 in ecx ("c") [ditto] */
		  "+d" (arg3)	/* pass arg3 in edx ("d") [ditto] */
		: "a"  (num)	/* pass system call number in eax ("a") */
		: "memory",		/* announce to the compiler that the memory */
		  "cc",			/* and condition codes [cc] have been modified */
		  "esi", "edi", /* these registers are clobbered */
		  "ebp");		/* [changed by the syscall] too (, "ebp") */
	/* The operating system will return a negative value on error;
	 * wrappers return -1 on error and set the errno global variable */
	if (-125 <= res && res < 0)
	{
		res = -1;
		errno = -res;
	}
	else
		res = 0;
	return (res);
}

void	_start(void)
{
	char	*str;
	size_t	len;
	int		exitcode;

	/* write(STDOUT_FILENO,"Hey!\n", 5); */
	str = "Wello Horld!\n";
	len = 13; /* ft_strlen(str); */
	exitcode = syscall3(__NR_write, STDOUT_FILENO, (long)str, len);
	ft_exit(exitcode);
}
