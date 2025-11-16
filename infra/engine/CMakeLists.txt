# CMakeLists.txt for infra/engine



add_library(engine STATIC
	src/simTime.cpp
)


target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add main executable
add_executable(simTime_main src/main.cpp)
target_link_libraries(simTime_main PRIVATE engine)



# Add Catch2 test for SimTime
enable_testing()

add_executable(test_simTime tests/test_simTime.cpp)
target_link_libraries(test_simTime PRIVATE engine Catch2::Catch2WithMain)
target_include_directories(test_simTime PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
add_test(NAME test_simTime COMMAND test_simTime)
