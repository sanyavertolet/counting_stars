cmake_minimum_required(VERSION 3.22)
project(counting_stars)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(counting_stars main.cpp src/Rational_number/Rational_number.cpp src/Rational_number/Rational_number.h src/string_arithmetics/string_arithmetics.cpp src/string_arithmetics/string_arithmetics.h)

add_executable(Rational_number_constructor_test src/Rational_number/Rational_number.cpp src/Rational_number/Rational_number.h src/Rational_number/tests/Rational_number_constructor_test.cpp)
target_link_libraries(Rational_number_constructor_test gtest_main)
add_test(NAME Rational_number_constructor_test COMMAND Rational_number_constructor_test)

add_executable(Rational_number_operators_test src/Rational_number/Rational_number.cpp src/Rational_number/Rational_number.h src/Rational_number/tests/Rational_number_operators_test.cpp src/string_arithmetics/string_arithmetics.cpp src/string_arithmetics/string_arithmetics.h)
target_link_libraries(Rational_number_operators_test gtest_main)
add_test(NAME Rational_number_operators_test COMMAND Rational_number_operators_test)

add_executable(Rational_number_utils_test src/Rational_number/Rational_number.cpp src/Rational_number/Rational_number.h src/Rational_number/tests/Rational_number_utils_test.cpp)
target_link_libraries(Rational_number_utils_test gtest_main)
add_test(NAME Rational_number_utils_test COMMAND Rational_number_utils_test)


add_executable(string_arithmetics_test src/string_arithmetics/tests/string_arithmetics_test.cpp src/string_arithmetics/string_arithmetics.cpp src/string_arithmetics/string_arithmetics.h)
target_link_libraries(string_arithmetics_test gtest_main)
add_test(NAME string_arithmetics_test COMMAND string_arithmetics_test)
