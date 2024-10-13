# SPDX-FileCopyrightText: 2023 Gottlieb+Freitag <info@gottliebtfreitag.de>
# SPDX-License-Identifier: CC0-1.0

cmake_minimum_required (VERSION 3.25)

project(sili LANGUAGES CXX
             DESCRIPTION "SiLi -- A simple and basic linear algebra library")


add_library(sili INTERFACE)
add_library(sili::sili ALIAS sili)
target_include_directories(sili INTERFACE
    src
)
target_compile_features(sili INTERFACE cxx_std_20)


include(cmake/CPM.cmake)

if (PROJECT_IS_TOP_LEVEL)
    CPMAddPackage("gh:fmtlib/fmt#11.0.2@11.0.2")
    CPMAddPackage("gh:catchorg/Catch@3.7.0")
#    CPMAddPackage("gh:SGSSGene/nanobench@4.3.11-2")

    enable_testing()

    # exampleSiLi
    add_executable(exampleSiLi
        src/exampleSiLi/example.cpp
    )
    target_link_libraries(exampleSiLi PUBLIC
        sili::sili
        fmt::fmt
    )

    # testSiLi
    add_executable(testSiLi
        src/testSiLi/docs.cpp
        src/testSiLi/testMatrix.cpp
    )
    target_link_libraries(testSiLi PUBLIC
        sili::sili
        Catch2::Catch2WithMain
    )

    # benchmarkSiLi
    add_executable(benchmarkSiLi
        src/benchmarkSiLi/benchmark.cpp
    )
    target_link_libraries(benchmarkSiLi PUBLIC
        sili::sili
        Catch2::Catch2WithMain
        armadillo
    )
endif()
