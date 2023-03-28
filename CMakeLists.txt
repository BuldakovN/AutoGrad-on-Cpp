cmake_minimum_required(VERSION 3.0.0)
project(NN VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(NN main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
add_library(Backward STATIC Backward.h Backward.cpp)
add_library(Value STATIC Value.h Value.cpp)
add_library(Vector STATIC Vector.h Vector.cpp)
add_library(Matrix STATIC Matrix.h Matrix.cpp)
#add_library(Layer STATIC Layer.h Layer.cpp)
target_link_libraries(NN Backward Value Vector Matrix)
include(CPack)