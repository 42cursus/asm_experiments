/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:59:14 by abelov            #+#    #+#             */
/*   Updated: 2024/01/06 17:59:16 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# define _GNU_SOURCE
# include <errno.h>
# include <unistd.h>
# include <sys/syscall.h>
# include <string.h>
# define STRINGIFY(x) __STRING(x)

#endif