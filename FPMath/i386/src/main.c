/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:58:36 by abelov            #+#    #+#             */
/*   Updated: 2025/03/12 13:58:37 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm/unistd.h>
#include <unistd.h>

float int_to_float_x87(int x);
int float_to_int_x87(float f);

void ft_exit(int exit_code) {
	__asm__ volatile ("int $0x80"::"a"(__NR_exit), "b"(exit_code));
}

typedef union u_myunion
{
	char str[4];
	int i;
	float f;
} t_un;

int main(void)
{
	t_un var;

	var.i = 42;

	float f = var.f;

	char *string = var.str;



	float f = int_to_float_x87(-42);
	int i = float_to_int_x87(-42.9f);
	_exit(i);
	return (i);
}
