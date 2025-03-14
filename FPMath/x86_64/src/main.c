/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:56:48 by abelov            #+#    #+#             */
/*   Updated: 2025/03/12 15:56:49 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sysexits.h>
#include <stdint-gcc.h>
#include "float_x86_64.h"


int float_to_int_x87_int(float in)
{
	float f2;
	register int res __asm__("edx");  // Force variable into edx
//	register uint64_t mm2 __asm__("mm0");  // Force variable into mm0
	__asm__ volatile (
			"movd %1, %%mm0\n"
			"movd %%mm0, %0\n"
			"emms\n"               /* Exit MMX mode */
			: "=r"(res)
			: "m"(in)
			: "mm0"
			);
	__asm__ volatile (
			"movl %1, %0\n"
			: "=r"(f2)
			: "r"(res)
			:
			);
	return  float_to_int_x87(f2);
}

__attribute__((noreturn))
int main(void)
{
	float j;
	register int i __asm__ ("edi");
	char buff[4] = {0b00000000, 0b10101111, 0b00101001, 0b11000010};

	j = *(float *)buff;
	int k = float_to_int_x87_int(j);

	i = k;

	write(STDOUT_FILENO, "-42.4209f", sizeof("-42.4209f")-1);
	if (i)
		i = EX_OK;
	_exit(i);
}
