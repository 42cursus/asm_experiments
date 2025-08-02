# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CMakeLists.txt                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelov <abelov@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/15 00:30:13 by abelov            #+#    #+#              #
#    Updated: 2025/03/15 00:30:13 by abelov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

cmake_minimum_required(VERSION 3.8.2)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0048 NEW) # PROJECT_VERSION
cmake_policy(SET CMP0075 NEW) # honor ``CMAKE_REQUIRED_LIBRARIES``

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_VERBOSE_BUILD ON)
set(CMAKE_SYSTEM_PROCESSOR x86_64)
set(CMAKE_LIBRARY_ARCHITECTURE x86_64-linux-gnu)
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64")
enable_language(ASM_NASM)
project(FPMath_common LANGUAGES C CXX ASM ASM_NASM)

#==============================================================================#

file(GLOB TARGET_HEADERS "src/*.h")
file(GLOB TARGET_SOURCES "src/*.c")
set(EXECUTABLE float_common)
set(TARGET_LINK_FLAGS -O0 -m64 -Wl,-melf_x86_64)
set(TARGET_CFLAGS
        -msoft-float
        -mfpmath=387 -mfp-ret-in-387 -mpc80 -m80387
        -mno-sse -mno-sse2 -mno-sse3 -mno-ssse3 -mno-sse4.1
        -mno-sse4.2 -mno-avx -mno-avx2 -mno-fma # -mabi=ms
        -fcf-protection=none
        -fno-unsafe-math-optimizations
        -MMD
        -fno-stack-protector
        -fcf-protection=none
        -mmanual-endbr
        -mno-red-zone
        -ffunction-sections
        -fdata-sections
        -fdwarf2-cfi-asm
        -fno-omit-frame-pointer
        -fno-asynchronous-unwind-tables
        -g3 -gdwarf-3
        -m64
        -O0)
add_executable(${EXECUTABLE})
target_sources(${EXECUTABLE} PRIVATE ${TARGET_HEADERS} ${TARGET_SOURCES})
target_link_options(${EXECUTABLE} PUBLIC ${TARGET_LINK_FLAGS})
#target_link_libraries(${EXECUTABLE} PRIVATE soft-fp64)
#target_link_directories(${EXECUTABLE} PRIVATE "$ENV{HOME}/staging/ieeelib")
target_compile_options(${EXECUTABLE}
        PRIVATE
        $<$<COMPILE_LANGUAGE:C>:
        ${TARGET_CFLAGS}>)
set_target_properties(${EXECUTABLE}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        OUTPUT_NAME "${EXECUTABLE}")

