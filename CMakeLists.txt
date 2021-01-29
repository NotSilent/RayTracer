cmake_minimum_required(VERSION 3.17)
project(RayTracerChallenge)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /W4")

add_subdirectory(src)
add_executable(RayTracerChallenge main.cpp)

target_include_directories(RayTracerChallenge PRIVATE src)

target_link_libraries(RayTracerChallenge FMath)


add_subdirectory(tests)