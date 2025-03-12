# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CMakeLists.txt                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelov <abelov@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/12 00:38:25 by abelov            #+#    #+#              #
#    Updated: 2025/03/12 00:38:26 by abelov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

cmake_minimum_required(VERSION 3.8.2)
#set(CMAKE_C_COMPILER clang)
set(CMAKE_C_COMPILER gcc)

project(asm_experiments LANGUAGES C ASM)
add_subdirectory(HelloWorldAsm)
add_subdirectory(math)
add_subdirectory(SysCall)
