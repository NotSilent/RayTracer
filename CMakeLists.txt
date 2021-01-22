cmake_minimum_required(VERSION 3.17)
project(RayTracerChallenge)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(src)
add_executable(RayTracerChallenge main.cpp)

target_include_directories(RayTracerChallenge PRIVATE src)

target_link_libraries(RayTracerChallenge FMath)


add_subdirectory(tests)