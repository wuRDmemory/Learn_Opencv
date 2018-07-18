cmake_minimum_required(VERSION 3.10)
project(Homography)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

add_executable(Homography main.cpp)
target_link_libraries(Homography ${OpenCV_LIBS})