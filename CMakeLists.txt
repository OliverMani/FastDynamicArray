cmake_minimum_required(VERSION 3.9)
project(FastDynamicArray)

set(SOURCES
    fastdynamicarray.c
)

set(HEADER_SET
    fastdybamicarray.h
)

add_library(FastDynamicArray SHARED fastdynamicarray.c)

# target_include_directories(FastDynamicArray PUBLIC include)