# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CMakeLists.txt                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelov <abelov@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/12 16:29:31 by abelov            #+#    #+#              #
#    Updated: 2025/03/12 16:29:31 by abelov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

cmake_minimum_required(VERSION 3.8.2)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0048 NEW) # PROJECT_VERSION
cmake_policy(SET CMP0075 NEW) # honor ``CMAKE_REQUIRED_LIBRARIES``

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_VERBOSE_BUILD ON)

enable_language(ASM_NASM)
project(syscall_x86_64 LANGUAGES C ASM_NASM)

#==============================================================================#

file(GLOB TARGET_HEADERS "src/*.h")
file(GLOB TARGET_SOURCES "src/syscall.c" "src/libc_read.c")
set(EXECUTABLE syscall_x86_64)
set(TARGET_LINK_FLAGS -w -lbsd -O0 -m64 -nostdlib -Wl,-melf_x86_64)
set(TARGET_CFLAGS
        -c
        -MMD
        -fno-stack-protector
        -fcf-protection=none
        -mmanual-endbr
        -fno-exceptions
        -ffunction-sections
        -fdata-sections
        -g3
        -gdwarf-3
        -m64
        -O0)
add_executable(${EXECUTABLE})
target_sources(${EXECUTABLE} PRIVATE ${TARGET_HEADERS} ${TARGET_SOURCES})
target_link_options(${EXECUTABLE} PUBLIC ${TARGET_LINK_FLAGS})
set_target_properties(${EXECUTABLE} PROPERTIES
        LINKER_LANGUAGE C
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        OUTPUT_NAME "${EXECUTABLE}")
target_compile_options(${EXECUTABLE}
        PRIVATE
        $<$<COMPILE_LANGUAGE:C>:
        ${TARGET_CFLAGS}>)
