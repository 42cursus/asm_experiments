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
			"flds %1\n"  // Load 32-bit float onto FPU stack
			"fistpl %0"  // Store as 32-bit integer (truncating)
			: "=m"(i)
			: "m"(f)
			: 	// The clobber list is empty because we do not explicitly
			);	// modify general-purpose registers—only the x87 FPU stack
	return (i);
}

