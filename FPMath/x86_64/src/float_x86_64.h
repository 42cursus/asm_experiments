/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_x86_64.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:28:55 by abelov            #+#    #+#             */
/*   Updated: 2025/03/14 00:11:57 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_EXPERIMENTS_FLOAT_X86_64_H
#define ASM_EXPERIMENTS_FLOAT_X86_64_H

int float_to_int_x87_round(float f, int mode);
int float_to_int_x87(float f);
float int_to_float_x87(int x);

#endif //ASM_EXPERIMENTS_FLOAT_X86_64_H
