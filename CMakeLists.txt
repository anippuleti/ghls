cmake_minimum_required(VERSION 3.14)
project(ghls VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Make Catch2 available globally
include(FetchContent)
FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v3.5.2 # You can update to latest stable if needed
)
FetchContent_MakeAvailable(Catch2)

# Only add infra/engine subdirectory
add_subdirectory(${CMAKE_SOURCE_DIR}/infra/engine)
