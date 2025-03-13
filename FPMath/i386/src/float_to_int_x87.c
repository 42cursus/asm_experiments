/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_to_int_x87.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:04:02 by abelov            #+#    #+#             */
/*   Updated: 2025/03/12 17:04:03 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html
 * @param f
 * @return
 */
int float_to_int_x87(float f)
{
	int i;
	/**
	 * FLD — Load Floating-Point Value
	 * https://www.felixcloutier.com/x86/fild
	 *
	 * FIST/FISTP — Store Integer
	 * https://www.felixcloutier.com/x86/fist:fistp
	 */
	__asm__ volatile (
		"fld %1\n"  // Load 32-bit float onto FPU stack
		"fistp %0"  // Store as 32-bit integer (truncating)
		: "=m"(i)
		: "m"(f)
		: "st" // https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html#Clobbers-and-Scratch-Registers
	);
	return (i);
}

