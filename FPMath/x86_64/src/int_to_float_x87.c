/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_to_float_x87.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:40:35 by abelov            #+#    #+#             */
/*   Updated: 2025/03/14 00:11:53 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * https://docs.oracle.com/cd/E19120-01/open.solaris/817-5477/eoizy/index.html
 * @param x
 * @return
 */
__attribute__((ms_abi))
float int_to_float_x87(int x)
{
	float f;

	/**
	 * FILD — Load Integer
	 * https://www.felixcloutier.com/x86/fild
	 *
	 * FST/FSTP — Store Floating-Point Value
	 * https://www.felixcloutier.com/x86/fst:fstp
	 *
	 * filds  short   # Load 16-bit integer
	 * fildl  long    # Load 32-bit integer
	 * fildq  quad    # Load 64-bit integer
	 */
	__asm__ volatile (
		"fildl %1\n"  /* Load the integer onto the FPU stack. */
		"fstps %0"    /* Store the float back to memory. */
		: "=m"(f)
		: "m"(x)
		:
	);
	return (f);
}
