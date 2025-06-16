cmake_minimum_required(VERSION 3.10)
project(robust_can_socket)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/Inc)

file(GLOB SOURCES
    ${CMAKE_SOURCE_DIR}/Src/*.cpp
)

add_executable(robust_can_socket ${SOURCES})

find_package(Threads REQUIRED)
target_link_libraries(robust_can_socket Threads::Threads)
