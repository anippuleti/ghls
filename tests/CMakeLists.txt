include(FetchContent)

FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(catch2)

add_executable(test_greeter test_greeter.cpp)
target_link_libraries(test_greeter PRIVATE ghls Catch2::Catch2WithMain)

include(CTest)
add_test(NAME greeter_test COMMAND test_greeter)
