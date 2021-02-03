# Add catch as an interface library
set(CATCH_INCLUDE_DIR .)
add_library(Catch INTERFACE)

# Add test executable
add_executable(Tests main.test.cpp
        TestShape.cpp TestShape.h
        Tuple.tests.cpp
        Color.tests.cpp
        Canvas.tests.cpp
        Matrix.tests.cpp
        Ray.tests.cpp
        Light.tests.cpp
        World.tests.cpp
        Camera.tests.cpp Pattern.tests.cpp)

target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})
target_link_libraries(Tests Catch)

target_include_directories(Common PUBLIC ../src)
target_link_libraries(Tests Common)