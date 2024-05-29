/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:56:05 by abelov            #+#    #+#             */
/*   Updated: 2024/01/06 16:56:07 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* i385 Linux */
#include <asm/unistd.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>

/**
 * ft_strlen() - calculates the length of the string pointed to by s, excluding
 * the terminating null byte ('\0').
 * Returns the number of bytes in the string pointed to by s.
 */
__attribute__ ((noinline))
size_t	ft_strlen(const char *s)
{
	const char	*o = s;
	ptrdiff_t	diff;

	while (*s != '\0')
		s++;
	diff = s - o;
	return ((size_t)diff);
}

void	ft_exit(int exit_code)
{
	__asm__ volatile (
		"int $0x80"
		:: "a"(__NR_exit), "b"(exit_code));
}

/**
 * ebp - 8 : second local
 * ebp - 4 : first local
 * ebp     : saved ebp
 * ebp + 4 : return address
 * ebp + 8 : pushed parameter
 */
ssize_t	ft_write(int fd, const void *buf, size_t size)
{
	ssize_t	ret;

	__asm__ volatile (
		"int $0x80"
		: "=a" (ret)
		: "0"(__NR_write), "b"(fd), "c"(buf), "d"(size)
		: "memory"); /* the kernel dereferences pointer args */
	return (ret);
}

void	_start(void)
{
	char	*str;
	size_t	len;

	/* write(STDOUT_FILENO,"Hey!\n", 5); */
	str = "Wello Horld!\n";
	len = ft_strlen(str);
	ft_write(STDOUT_FILENO, str, len);
	ft_exit(EXIT_SUCCESS);
}
