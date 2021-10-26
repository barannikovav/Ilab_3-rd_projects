cmake_minimum_required(VERSION 3.13)

project(2Q_Cache VERSION 1.0 LANGUAGES CXX)



set(CMAKE_CXX_STANDARD 17)

set(SOURCE_EXE ${CMAKE_SOURCE_DIR}/Source/2Q_Cache_source.cpp)

set(SOURCE_LIB ${CMAKE_SOURCE_DIR}/Headers)

set(IDEAL_EXE ${CMAKE_SOURCE_DIR}/Ideal_cache/ideal_cache.cpp)

add_compile_options(
    -Werror

    -O3

    -Wall 
    -Wextra 
     
    -Wnarrowing 
    -Wconversion 
    -Wwrite-strings 
    -Wcast-qual 
    -Wundef    
    -Wreturn-type
)

add_executable(main.exe)
add_executable(main_test.exe)
add_executable(ideal.exe)

target_compile_definitions(main_test.exe PRIVATE TEST=1)
target_sources(main.exe PRIVATE ${SOURCE_EXE})
target_sources(main_test.exe PRIVATE ${SOURCE_EXE})
target_sources(ideal.exe PRIVATE ${IDEAL_EXE})

target_include_directories(main.exe PRIVATE ${SOURCE_LIB})
target_include_directories(main_test.exe PRIVATE ${SOURCE_LIB})





