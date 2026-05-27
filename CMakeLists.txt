cmake_minimum_required(VERSION 3.20)
project(CPlusPlus_Course_Serialization CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(01_invariant         01_invariant/main.cpp)
add_executable(02_use_cases         02_use_cases/main.cpp)
add_executable(03_text_vs_binary    03_text_vs_binary/main.cpp)
add_executable(04_raw_memory        04_raw_memory/main.cpp)
add_executable(06_visitor_exercice_shapes 06_visitor_exercice_shapes/main.cpp)

# Boost.Serialization is optional. If Boost is installed, build the demo.
find_package(Boost QUIET COMPONENTS serialization)
if(Boost_FOUND)
    add_executable(05_boost 05_boost/main.cpp)
    target_link_libraries(05_boost PRIVATE Boost::serialization)
    message(STATUS "Boost found - 05_boost will be built")
else()
    message(STATUS "Boost not found - skipping 05_boost (install libboost-serialization-dev or use vcpkg)")
endif()
