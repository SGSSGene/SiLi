# SPDX-FileCopyrightText: 2023 Gottlieb+Freitag <info@gottliebtfreitag.de>
# SPDX-License-Identifier: CC0-1.0

cmake_minimum_required (VERSION 3.25)

project(sili LANGUAGES CXX
             DESCRIPTION "SiLi -- A simple and basic linear algebra library")
include(cmake/CPM.cmake)
CPMAddPackage("gh:SGSSGene/cpmpack@1.1.2")
loadCPMPack("${CMAKE_CURRENT_SOURCE_DIR}/cpmpack.json")
enable_testing()
