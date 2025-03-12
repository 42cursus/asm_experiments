/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 04:55:06 by abelov            #+#    #+#             */
/*   Updated: 2024/05/29 04:55:07 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static inline unsigned long log2(unsigned long x)
{
	unsigned long r = 0;
	__asm__(
		"bsrl %1, %0\n\t"
		"jnz 1f\n\t"
		"movl $-1, %0\n\t"
		"1:\n\t"
		: "=r" (r)
		: "r" (x)
		);
	return r;
}
