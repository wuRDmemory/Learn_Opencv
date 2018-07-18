cmake_minimum_required(VERSION 3.10)
project(ECC)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 11)

add_executable(ECC main.cpp)
target_link_libraries(ECC ${OpenCV_LIBS})