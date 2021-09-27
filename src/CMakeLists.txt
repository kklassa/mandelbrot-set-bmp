cmake_minimum_required(VERSION 3.9)
project(mandelbrot-set-bmp)
enable_language(ASM_NASM)

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> <FLAGS> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")

set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS -m32)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS -m32)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

set_source_files_properties(mandelbrot.asm PROPERTIES COMPILE_FLAGS "-g -Fdwarf")

add_executable(
    main
    main.c
    mandelbrot.asm
)

target_link_libraries(main m)