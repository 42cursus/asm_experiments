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
		"fistps %0"  // Store as 32-bit integer (truncating)
		: "=m"(i)
		: "m"(f)
		: "st"
	);
	return (i);
}
/**
 * Round to nearest (default)	00 (0x0000)
 * Round down (toward -∞)		01 (0x0400)
 * Round up (toward +∞)			10 (0x0800)
 * Round toward zero (truncate)	11 (0x0C00)
 *
 * @param f
 * @param mode
 * @return
 */
int float_to_int_x87_round(float f, int mode) {
	int result;
	unsigned short cw, cw_new;

	__asm__("fstcw %0" : "=m" (cw)); // Store current FPU control word
	cw_new = (cw & ~0x0C00) | (mode << 10); // Set rounding mode

	__asm__("fldcw %1\n\t"   // Load new control word
			"flds %2\n\t"    // Load float onto the x87 FPU stack
			"frndint\n\t"    // Round according to new mode
			"fistps %0\n\t"  // Convert to integer and store result
			"fldcw %3"       // Restore original control word
			: "=m" (result)
			: "m" (cw_new), "m" (f), "m" (cw)
			: "st"
			);

	return result;
}
