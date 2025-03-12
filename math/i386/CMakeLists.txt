# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CMakeLists.txt                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelov <abelov@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/12 14:02:32 by abelov            #+#    #+#              #
#    Updated: 2025/03/12 14:02:33 by abelov           ###   ########.fr        #
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
set(CMAKE_SYSTEM_PROCESSOR i386)
set(CMAKE_LIBRARY_ARCHITECTURE i386-linux-gnu)
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
enable_language(ASM_NASM)
project(math_i386 LANGUAGES C ASM_NASM)

#==============================================================================#

file(GLOB TARGET_HEADERS "src/*.h")
file(GLOB TARGET_SOURCES "src/*.c")
set(EXECUTABLE math_i386)
set(TARGET_LINK_FLAGS -w -lbsd -O0 -m32 -Wl,--build-id -Wl,-melf_i386)
set(TARGET_CFLAGS
        -MMD
        -fno-stack-protector
        -fcf-protection=none
#        -mmanual-endbr
        -fno-pic
        -fno-exceptions
        -ffunction-sections
        -fdata-sections
        -fno-common
        -fno-builtin
        -fno-omit-frame-pointer # Don't keep the frame pointer in a register for functions that don't need one.
        -ffreestanding
        -g3
        -ggdb
        -m32
        -O2)
add_executable(${EXECUTABLE})
target_sources(${EXECUTABLE} PRIVATE ${TARGET_HEADERS} ${TARGET_SOURCES})
target_include_directories(${EXECUTABLE} PRIVATE)
target_link_options(${EXECUTABLE} PUBLIC ${TARGET_LINK_FLAGS})
target_compile_options(${EXECUTABLE}
        PRIVATE
            $<$<COMPILE_LANGUAGE:C>:${TARGET_CFLAGS}>)
set_target_properties(${EXECUTABLE} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        OUTPUT_NAME "${EXECUTABLE}")

