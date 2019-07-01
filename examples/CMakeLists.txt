
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE HELLO_SRC HelloEcs/src/*.cpp)
file(GLOB_RECURSE HELLO_INC HelloEcs/include/*.hpp)

add_executable(HelloEcs ${HELLO_SRC} ${HELLO_INC})