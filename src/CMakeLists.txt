add_library(ghls STATIC greeter.cpp)
target_include_directories(ghls PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(ghls_app main.cpp)
target_link_libraries(ghls_app PRIVATE ghls)
