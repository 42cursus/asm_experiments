/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:33:33 by abelov            #+#    #+#             */
/*   Updated: 2025/03/15 00:33:34 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sysexits.h>
#include "ieee754.h"

inline __attribute__((always_inline, ms_abi))
float __divsf3(float a, float b)
{
	return a / b;
}

int main(void)
{
	float f1 = 250.0f;
	float f2 = 2.0f;
	float f3 = __divsf3(f1, f2);

	_exit(EX_OK);
	(void)f3;
}
