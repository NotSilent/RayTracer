cmake_minimum_required(VERSION 3.17)
project(RayTracer)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /W4")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} /std:c++latest /W4 /O2")

add_subdirectory(src)
add_executable(RayTracer main.cpp)

target_include_directories(RayTracer PRIVATE src)

target_link_libraries(RayTracer Common)


add_subdirectory(tests)