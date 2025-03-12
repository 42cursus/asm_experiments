/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:09:41 by abelov            #+#    #+#             */
/*   Updated: 2025/03/12 16:09:42 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sysexits.h>
//#include <include/libc-symbols.h>
//#define attribute_hidden __attribute__ ((visibility ("hidden")))
#define attribute_hidden
#define IS_IN(lib) 1

#include <asm/unistd_32.h>
#include <sys/types.h>
#include <unistd.h>

#include <sysdeps/unix/sysv/linux/i386/sysdep.h>
#include <errno.h>

int __set_errno(int n) {
	errno = n;
	return -1;
}

__attribute__ ((__regparm__ (1)))
int __syscall_error (int error)
{
	__set_errno (-error);
	return -1;
}

void ft_exit(int exit_code) {
	__asm__ volatile ("int $0x80"::"a"(__NR_exit), "b"(exit_code));
}

ssize_t ft_read(int fd, void *buf, size_t count) {
	return INLINE_SYSCALL(read, __NR_read, fd, buf, count);
	return syscall(__NR_read, fd, buf, count);
}

int main(void) {
	char buf[42];

	ft_read(STDIN_FILENO, buf, 0);

	ft_exit(EX_OK);
	return (EX_OK);
}

