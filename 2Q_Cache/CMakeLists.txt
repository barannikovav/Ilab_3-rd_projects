cmake_minimum_required(VERSION 3.13)

project(2Q_Cache VERSION 1.0 LANGUAGES CXX)



set(CMAKE_CXX_STANDARD 17)

set(SOURCE_EXE ${CMAKE_SOURCE_DIR}/Source/2Q_Cache_source.cpp)

set(SOURCE_LIB ${CMAKE_SOURCE_DIR}/Headers)

add_compile_options(
    -Werror

    -ggdb

    -Wall 
    -Wextra 
     
    -Wnarrowing 
    -Wconversion 
    -Wwrite-strings 
    -Wcast-qual 
    -Wundef 
    -Wstrict-prototypes 
    -Wbad-function-cast  
    -Wreturn-type
)

add_executable(main)

target_sources(main PRIVATE ${SOURCE_EXE})

target_include_directories(main PRIVATE ${SOURCE_LIB})




