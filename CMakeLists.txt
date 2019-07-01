
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(ECS_ROOT "${CMAKE_CURRENT_LIST_DIR}")


#build library here if needed


include_directories("${ECS_ROOT}/include")

add_subdirectory(examples)