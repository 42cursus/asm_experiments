/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:17:44 by abelov            #+#    #+#             */
/*   Updated: 2024/01/06 17:17:46 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/**
 * https://people.cs.rutgers.edu/~pxk/419/notes/frames.html
 */
#define MY_FCN __asm__ ("\n\
.text\n\
	.align 16\n\
.globl _my_init\n\
_my_init:\n\
	pushq	%rbp;\n\
	movq	%rsp, %rbp\n\
	sub		$0x10,%rsp\n\
	movl	%edi, -4(%rbp)\n\
	movl	-4(%rbp), %eax\n\
	addl	$1, %eax\n\
	leave\n\
	ret\n\
.previous\n");
MY_FCN

/*
 * https://wiki.osdev.org/System_V_ABI#x86-64
 * https://people.cs.rutgers.edu/~pxk/419/notes/frames.html
 * https://eli.thegreenplace.net/2011/09/06/stack-frame-layout-on-x86-64/
 *
 * High Address
 * +------------------+
 * |  Parameter 2     |   <- rbp + 24 (0x18)
 * +------------------+
 * |  Parameter 1     |   <- rbp + 16 ()
 * +------------------+
 * |  Return Address  |   <- rbp + 8
 * +------------------+
 * |  Saved rbp       |   <- rbp
 * +------------------+
 * |  First Local     |   <- rbp - 8
 * +------------------+
 * |  Second Local    |   <- rbp - 16 ()
 * +------------------+
 * Low Address
 */
#define FT_STRLEN __asm__ ("\n\
.text\n\
	.align 16\n\
.globl _ft_strlen\n\
_ft_strlen:\n\
	push	%rbp\n\
	mov		%rsp,%rbp\n\
	sub		$0x10,%rsp\n\
	movq	0x18(%rbp),%rsi\n\
	xor		%rcx,%rcx\n\
_strlen_next:\n\
	cmpb	$0x0,(%rsi)\n\
	je		_strlen_null\n\
	inc		%rcx\n\
	inc		%rsi\n\
	jmp		_strlen_next\n\
_strlen_null:\n\
	mov		%rcx,%rax\n\
	leave\n\
	ret\n\
.previous\n");

FT_STRLEN

extern int	_my_init(int);
extern size_t	_ft_strlen(char *);

size_t myfcn(char *s, int d)
{
	size_t	len;

	d = _my_init(d);
	len = _ft_strlen(s);
	return (len);
}

int	main(void)
{
	char	*str;

	str = "Wello Horld!\n";
	/* write(STDOUT_FILENO,"Hey!\n", 5); */
	syscall(SYS_write, STDOUT_FILENO, str, myfcn(str, 5));
	return (0);
}
