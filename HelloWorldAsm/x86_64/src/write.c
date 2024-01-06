/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:18:05 by abelov            #+#    #+#             */
/*   Updated: 2024/01/06 17:18:07 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* x86-64 Linux */
#include <asm/unistd.h>
#include <unistd.h>

extern size_t _strlen2 (const char *s);

void	ft_exit(int exit_code)
{
	__asm__ ("syscall" :: "a" (__NR_exit), "D" (exit_code)); /* D for EDI */
}

ssize_t	ft_write(int fd, const char *buf, size_t size)
{
	ssize_t	ret;

	__asm__ volatile (
		"syscall"
		: "=a" (ret)
		/*                 EDI      RSI       RDX */
		: "0"(__NR_write), "D"(fd), "S"(buf), "d"(size)
		: "rcx", "r11", "memory"
		);
	return (ret);
}

void	_start(void)
{
	char	*str;
	size_t	len;

	str = "Wello Horld!\n";
	len = _strlen2(str);
	/* write(STDOUT_FILENO,"Hey!\n", 5); */
	ft_write(STDOUT_FILENO, str, len);
	ft_exit(0);
}
