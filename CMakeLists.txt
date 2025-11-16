cmake_minimum_required(VERSION 3.14)
project(ghls VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

# Add infra/engine directory
add_subdirectory(${CMAKE_SOURCE_DIR}/infra/engine)

option(BUILD_TESTS "Build unit tests" ON)
if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
