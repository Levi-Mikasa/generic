cmake_minimum_required(VERSION 3.15)
project(test C)
set(CMAKE_BUILD_TYPE Debug)
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)
add_executable(TESTES 
    test/test_treeds/Binary_Tree.c
    
    
    ${CMAKE_SOURCE_DIR}/src/generic_containerbase.c
    ${CMAKE_SOURCE_DIR}/src/generic_dslist.c
    ${CMAKE_SOURCE_DIR}/src/generic_dsvector.c
    ${CMAKE_SOURCE_DIR}/src/generic_dstree.c
)
