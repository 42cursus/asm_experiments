# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CMakeLists.txt                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelov <abelov@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/12 00:41:22 by abelov            #+#    #+#              #
#    Updated: 2025/03/12 00:41:23 by abelov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

cmake_minimum_required(VERSION 3.8.2)

project(HelloWorldAsm LANGUAGES C ASM)

add_subdirectory(i386)
add_subdirectory(x86_64)
