cmake_minimum_required(VERSION 3.12)
project(ProjetoLP_AED C)

file(GLOB SOURCES
        main.c
        data/*.txt
        *.c
        libs_src/*.c
        libs_src/union_find/*.c
        libs_src/strings/*.c
        Fase1/*.c
        Fase2/*.c
        )

set(CMAKE_C_STANDARD 99)

add_executable(ProjetoLP_AED main.c ${SOURCES} Fase1/fase1.c Fase1/fase1.h Fase2/fase2.c Fase2/fase2.h)