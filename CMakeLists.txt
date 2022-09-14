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

add_executable(counting_stars main.cpp src/Rational_number/Rational_number.cpp src/Rational_number/Rational_number.h src/StringInt/StringInt.cpp src/StringInt/StringInt.h src/exceptions/IllegalSignException.h)

add_executable(Rational_number_constructor_test src/Rational_number/Rational_number.cpp src/Rational_number/Rational_number.h src/Rational_number/tests/Rational_number_constructor_test.cpp)
target_link_libraries(Rational_number_constructor_test gtest_main)
add_test(NAME Rational_number_constructor_test COMMAND Rational_number_constructor_test)

add_executable(Rational_number_operators_test src/Rational_number/Rational_number.cpp src/Rational_number/Rational_number.h src/Rational_number/tests/Rational_number_operators_test.cpp src/StringInt/StringInt.cpp src/StringInt/StringInt.h)
target_link_libraries(Rational_number_operators_test gtest_main)
add_test(NAME Rational_number_operators_test COMMAND Rational_number_operators_test)

add_executable(Rational_number_utils_test src/Rational_number/Rational_number.cpp src/Rational_number/Rational_number.h src/Rational_number/tests/Rational_number_utils_test.cpp)
target_link_libraries(Rational_number_utils_test gtest_main)
add_test(NAME Rational_number_utils_test COMMAND Rational_number_utils_test)


add_executable(StringInt_constructor_test src/StringInt/StringInt.cpp src/StringInt/StringInt.h src/StringInt/tests/StringInt_constructor_test.cpp src/exceptions/IllegalSignException.h)
target_link_libraries(StringInt_constructor_test gtest_main)
add_test(NAME StringInt_constructor_test COMMAND StringInt_constructor_test)

add_executable(StringInt_operators_test src/StringInt/StringInt.cpp src/StringInt/StringInt.h src/StringInt/tests/StringInt_operators_test.cpp src/exceptions/IllegalSignException.h)
target_link_libraries(StringInt_operators_test gtest_main)
add_test(NAME StringInt_operators_test COMMAND StringInt_operators_test)