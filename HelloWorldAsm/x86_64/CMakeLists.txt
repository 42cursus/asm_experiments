cmake_minimum_required(VERSION 3.8.2)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0048 NEW) # PROJECT_VERSION
cmake_policy(SET CMP0075 NEW) # honor ``CMAKE_REQUIRED_LIBRARIES``

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_VERBOSE_BUILD ON)
set(CMAKE_SYSTEM_PROCESSOR x86_64)
set(CMAKE_LIBRARY_ARCHITECTURE x86_64-linux-gnu)
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64")
enable_language(ASM_NASM)
project(hw_x86_64 LANGUAGES C ASM_NASM)

file(GLOB TARGET_HEADERS "src/*.h")
file(GLOB TARGET_SOURCES "src/hw1.asm")

set(TARGET_CFLAGS
        -c
        -ffunction-sections
        -fdata-sections)
set(TARGET_LINK_FLAGS -w -lbsd -O0 -g -m64 -nostdlib -Wl,-melf_x86_64 )
set(TARGET_ASM_FLAGS -gdwarf -Wall)

# how-to-use-cmake-to-build-binaries-with-nasm
# https://stackoverflow.com/questions/56420035/
set(EXECUTABLE hw1)
add_executable(${EXECUTABLE})
target_sources(${EXECUTABLE} PRIVATE ${TARGET_HEADERS} ${TARGET_SOURCES})
target_link_options(${EXECUTABLE} PUBLIC ${TARGET_LINK_FLAGS})
set_target_properties(${EXECUTABLE} PROPERTIES
        LINKER_LANGUAGE ASM
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
target_compile_options(${EXECUTABLE}
        PRIVATE
        $<$<COMPILE_LANGUAGE:ASM_NASM>:
            ${TARGET_ASM_FLAGS}>
        $<$<COMPILE_LANGUAGE:C>:
            ${TARGET_CFLAGS}>)

set(TARGET_ASM_FLAGS -gdwarf -Wall)
file(GLOB TARGET_HEADERS "src/*.h")
file(GLOB TARGET_SOURCES "src/strlen.asm")
set(EXECUTABLE strlen)
add_executable(${EXECUTABLE})
target_sources(${EXECUTABLE} PRIVATE ${TARGET_HEADERS} ${TARGET_SOURCES})
target_link_options(${EXECUTABLE} PUBLIC ${TARGET_LINK_FLAGS})
set_target_properties(${EXECUTABLE} PROPERTIES
        LINKER_LANGUAGE ASM
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
target_compile_options(${EXECUTABLE}
        PRIVATE
        $<$<COMPILE_LANGUAGE:ASM_NASM>:
        ${TARGET_ASM_FLAGS}>
        $<$<COMPILE_LANGUAGE:C>:
        ${TARGET_CFLAGS}>)

file(GLOB TARGET_HEADERS "src/*.h")
file(GLOB TARGET_SOURCES "src/syscall.c")
set(EXECUTABLE syscall_x86_64)
set(TARGET_LINK_FLAGS -w -lbsd -O0 -m64 -nostdlib -Wl,-melf_x86_64 )
set(TARGET_CFLAGS
        -c
        -MMD
        -fcf-protection=none
        -mmanual-endbr
        -fno-exceptions
        -ffunction-sections
        -fdata-sections
        -g3
        -ggdb
        -m64
        -O0)
add_executable(${EXECUTABLE})
target_sources(${EXECUTABLE} PRIVATE ${TARGET_HEADERS} ${TARGET_SOURCES})
target_link_options(${EXECUTABLE} PUBLIC ${TARGET_LINK_FLAGS})
set_target_properties(${EXECUTABLE} PROPERTIES
        LINKER_LANGUAGE C
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
target_compile_options(${EXECUTABLE}
        PRIVATE
        $<$<COMPILE_LANGUAGE:C>:
            ${TARGET_CFLAGS}>)


file(GLOB TARGET_HEADERS "src/*.h")
file(GLOB TARGET_SOURCES "src/main.c")
set(EXECUTABLE main)
set(TARGET_LINK_FLAGS -w -lbsd -O0 -m64  -Wl,-melf_x86_64 )
set(TARGET_CFLAGS
        -c
        -MMD
        -fcf-protection=none
        -mmanual-endbr
        -fno-exceptions
        -ffunction-sections
        -fdata-sections
        -g3
        -ggdb
        -m64
        -O0)
add_executable(${EXECUTABLE})
target_sources(${EXECUTABLE} PRIVATE ${TARGET_HEADERS} ${TARGET_SOURCES})
target_link_options(${EXECUTABLE} PUBLIC ${TARGET_LINK_FLAGS})
set_target_properties(${EXECUTABLE} PROPERTIES
        LINKER_LANGUAGE C
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
target_compile_options(${EXECUTABLE}
        PRIVATE
        $<$<COMPILE_LANGUAGE:C>:
        ${TARGET_CFLAGS}>)

set(EXECUTABLE write_x86_64)
set(TARGET_ASM_FLAGS -gdwarf -Wall)
set(TARGET_LINK_FLAGS -w -lbsd -O0 -m64 -nostdlib -Wl,-melf_x86_64 )
set(TARGET_CFLAGS
        -c
        -MMD
        -fcf-protection=none
        -mmanual-endbr
        -fno-pic
        -fPIE
        -fno-exceptions
        -ffunction-sections
        -fdata-sections
        -g3
        -ggdb
        -m64
        -O1)
file(GLOB TARGET_HEADERS "src/*.h")
file(GLOB TARGET_SOURCES "src/strlen2.asm")
file(GLOB TARGET_CSOURCES "src/write.c")
list (APPEND TARGET_SOURCES ${TARGET_CSOURCES})
add_executable(${EXECUTABLE})
target_sources(${EXECUTABLE} PRIVATE ${TARGET_HEADERS} ${TARGET_SOURCES})
target_link_options(${EXECUTABLE} PUBLIC ${TARGET_LINK_FLAGS})
set_target_properties(${EXECUTABLE} PROPERTIES
        LINKER_LANGUAGE C
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
target_compile_options(${EXECUTABLE}
        PRIVATE
        $<$<COMPILE_LANGUAGE:ASM_NASM>:
            ${TARGET_ASM_FLAGS}>
        $<$<COMPILE_LANGUAGE:C>:
            ${TARGET_CFLAGS}>)