cmake_minimum_required(VERSION 3.8.2)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_EXTENSIONS OFF)
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
project(hw_i386 LANGUAGES C ASM_NASM)

file(GLOB TARGET_HEADERS "src/*.h")
file(GLOB TARGET_SOURCES "src/hw.asm")

set(TARGET_CFLAGS
        -c -w
        -ffunction-sections
        -fdata-sections)
set(TARGET_LINK_FLAGS -w -lbsd -O0 -m32 -nostdlib -Wl,--build-id -Wl,-melf_i386)
set(TARGET_ASM_NASM_FLAGS -Wall )
#set(CMAKE_ASM_NASM_FLAGS "${TARGET_ASM_NASM_FLAGS}")
set(CMAKE_ASM_NASM_FLAGS_DEBUG "${CMAKE_ASM_NASM_FLAGS_DEBUG} -gdwarf ")

# how-to-use-cmake-to-build-binaries-with-nasm
# https://stackoverflow.com/questions/56420035/
set(EXECUTABLE hw)
add_executable(${EXECUTABLE})
set_source_files_properties(${TARGET_SOURCES} PROPERTIES LANGUAGE ASM_NASM)
target_sources(${EXECUTABLE} PRIVATE ${TARGET_HEADERS} ${TARGET_SOURCES})
target_link_options(${EXECUTABLE} PRIVATE ${TARGET_LINK_FLAGS})
set_target_properties(${EXECUTABLE} PROPERTIES
        LINKER_LANGUAGE ASM
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
target_compile_options(${EXECUTABLE}
        PRIVATE
        $<$<COMPILE_LANGUAGE:ASM_NASM>:
            ${TARGET_ASM_NASM_FLAGS}>
        $<$<COMPILE_LANGUAGE:C>:
            ${TARGET_CFLAGS}>)


file(GLOB TARGET_HEADERS "src/*.h")
file(GLOB TARGET_SOURCES "src/syscall.c")
set(EXECUTABLE syscall_i386)
set(TARGET_LINK_FLAGS -w -lbsd -O0 -m32 -nostdlib -Wl,--build-id -Wl,-melf_i386)
#https://stackoverflow.com/questions/14666665
set(TARGET_CFLAGS
        -c
        -MMD -MD -MP -MF
        -fcf-protection=none
        -mmanual-endbr
        -fno-exceptions
        -ffunction-sections
        -fdata-sections
        -fomit-frame-pointer # Don't keep the frame pointer in a register for functions that don't need one.
        -g3
        -ggdb
        -m32
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
file(GLOB TARGET_SOURCES "src/write.c")
set(EXECUTABLE write_i386)
set(TARGET_LINK_FLAGS -w -lbsd -O0 -m32 -nostdlib -Wl,--build-id -Wl,-melf_i386)
set(TARGET_CFLAGS
        -c
        -MMD
        -fcf-protection=none
        -mmanual-endbr
        -fno-pic
        -fno-exceptions
        -ffunction-sections
        -fdata-sections
        -fno-common
        -fno-builtin
        -fomit-frame-pointer # Don't keep the frame pointer in a register for functions that don't need one.
        -g3
        -ggdb
        -m32
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