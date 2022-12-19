cmake_minimum_required(VERSION 3.16)
project(lifetime)

set(CMAKE_CXX_STANDARD 20)

include_directories(..)

add_executable(lifetime main.cpp)
find_package(fmt)
target_link_libraries(lifetime fmt::fmt)
