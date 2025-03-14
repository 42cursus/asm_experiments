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


#==============================================================================#
# IEEE lib
#==============================================================================#

set(IEEE_LIB_NAME ft)
set(IEEE_LIB_FILENAME libft.a)
set(IEEE_LIB_DIR "${PROJECT_SOURCE_DIR}/lib/ft")

file(GLOB_RECURSE IEEE_LIB_HEADERS "${IEEE_LIB_DIR}/*.h")
file(GLOB_RECURSE IEEE_LIB_SOURCES "${IEEE_LIB_DIR}/ft_*.c")

add_custom_target(${IEEE_LIB_NAME}_target ALL
        COMMAND make -C ${IEEE_LIB_DIR} #BUILD_WITH_ASAN=1
        BYPRODUCTS "${IEEE_LIB_DIR}/${IEEE_LIB_FILENAME}"
        SOURCES "${IEEE_LIB_HEADERS};${IEEE_LIB_SOURCES}"
        COMMENT "Building IEEE_LIB")

add_library(${IEEE_LIB_NAME} STATIC IMPORTED)

add_dependencies(${IEEE_LIB_NAME} "${IEEE_LIB_NAME}_target")
set_target_properties(${IEEE_LIB_NAME} PROPERTIES
        IMPORTED_LOCATION ${IEEE_LIB_DIR}/${IEEE_LIB_FILENAME}
        INTERFACE_COMPILE_DEFINITIONS ""
        INTERFACE_LINK_OPTIONS ""
        INTERFACE_SOURCES "${IEEE_LIB_HEADERS}"
        INTERFACE_INCLUDE_DIRECTORIES "${IEEE_LIB_DIR};${IEEE_LIB_DIR}/include;${IEEE_LIB_DIR}/include/ft")

project(asm_experiments LANGUAGES C ASM)
add_subdirectory(HelloWorldAsm)
add_subdirectory(FPMath)
add_subdirectory(SysCall)
