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

set(exceptions src/exceptions/exceptions.h src/exceptions/IllegalSignException/IllegalSignException.h src/exceptions/IllegalDigitException/IllegalDigitException.h src/exceptions/DivisionByZeroException/DivisionByZeroException.h src/exceptions/ParseException/ParseException.h src/exceptions/CastException/CastException.h src/exceptions/OutOfRangeException/OutOfRangeException.h src/exceptions/OutOfIntegerDivision/OutOfIntegerDivisionException.h src/exceptions/OverflowException/OverflowException.h src/exceptions/ParseException/ParseException.h src/exceptions/FileNotFoundException/FileNotFoundException.h src/exceptions/FileNotFoundException/FileNotFoundException.cpp)

add_executable(counting_stars ${exceptions} src/StringInt/StringInt.cpp src/StringInt/StringInt.h src/Rational_number/Rational_number.cpp src/Rational_number/Rational_number.h src/Complex_number/Complex_number.h src/Vector/Vector.cpp src/Vector/Vector.bool.cpp src/Vector/Vector.h src/Pos/Pos.h src/Matrix/Coords/Matrix_coords.h)

add_executable(Rational_number_constructor_test src/StringInt/StringInt.cpp src/StringInt/StringInt.h src/Rational_number/Rational_number.cpp src/Rational_number/Rational_number.h test/Rational_number/Rational_number_constructor_test.cpp)
target_link_libraries(Rational_number_constructor_test gtest_main)
add_test(NAME Rational_number_constructor_test COMMAND Rational_number_constructor_test)

add_executable(Rational_number_operators_test src/Rational_number/Rational_number.cpp src/Rational_number/Rational_number.h test/Rational_number/Rational_number_operators_test.cpp src/StringInt/StringInt.cpp src/StringInt/StringInt.h)
target_link_libraries(Rational_number_operators_test gtest_main)
add_test(NAME Rational_number_operators_test COMMAND Rational_number_operators_test)


add_executable(StringInt_constructor_test src/StringInt/StringInt.cpp src/StringInt/StringInt.h test/StringInt/StringInt_constructor_test.cpp ${exceptions})
target_link_libraries(StringInt_constructor_test gtest_main)
add_test(NAME StringInt_constructor_test COMMAND StringInt_constructor_test)

add_executable(StringInt_operators_test src/StringInt/StringInt.cpp src/StringInt/StringInt.h test/StringInt/StringInt_operators_test.cpp ${exceptions})
target_link_libraries(StringInt_operators_test gtest_main)
add_test(NAME StringInt_operators_test COMMAND StringInt_operators_test)

add_executable(StringInt_cast_test src/StringInt/StringInt.cpp src/StringInt/StringInt.h test/StringInt/StringInt_cast_test.cpp)
target_link_libraries(StringInt_cast_test gtest_main)
add_test(NAME StringInt_cast_test COMMAND StringInt_cast_test)


add_executable(Complex_number_constructor_test src/Complex_number/Complex_number.h src/Rational_number/Rational_number.cpp src/Rational_number/Rational_number.h src/StringInt/StringInt.cpp src/StringInt/StringInt.h test/Complex_number/Complex_number_constructor_test.cpp)
target_link_libraries(Complex_number_constructor_test gtest_main)
add_test(NAME Complex_number_constructor_test COMMAND Complex_number_constructor_test)

add_executable(Complex_number_operators_test src/Complex_number/Complex_number.h src/Rational_number/Rational_number.cpp src/Rational_number/Rational_number.h src/StringInt/StringInt.cpp src/StringInt/StringInt.h test/Complex_number/Complex_number_operators_test.cpp)
target_link_libraries(Complex_number_operators_test gtest_main)
add_test(NAME Complex_number_operators_test COMMAND Complex_number_operators_test)


add_executable(Vector_test src/Vector/Vector.h src/Vector/Vector.cpp src/Vector/Vector.bool.cpp src/Complex_number/Complex_number.h src/Rational_number/Rational_number.cpp src/Rational_number/Rational_number.h src/StringInt/StringInt.cpp src/StringInt/StringInt.h test/Vector/Vector_test.cpp ${exceptions})
target_link_libraries(Vector_test gtest_main)
add_test(NAME Vector_test COMMAND Vector_test)


add_executable(Pos_test src/Pos/Pos.h src/Pos/Pos.cpp test/Pos/Pos_test.cpp src/StringInt/StringInt.h src/StringInt/StringInt.cpp ${exceptions})
target_link_libraries(Pos_test gtest_main)
add_test(NAME Pos_test COMMAND Pos_test)


add_executable(Matrix_coords_test src/Pos/Pos.h src/Matrix/Coords/Matrix_coords.h src/StringInt/StringInt.h src/StringInt/StringInt.cpp ${exceptions} test/Matrix/Coords/Matrix_coords_test.cpp)
target_link_libraries(Matrix_coords_test gtest_main)
add_test(NAME Matrix_coords_test COMMAND Matrix_coords_test)


add_executable(Matrix_column_coord_test src/Pos/Pos.h src/Matrix/Coords/Matrix_column_coord.h src/StringInt/StringInt.h src/StringInt/StringInt.cpp ${exceptions} test/Matrix/Coords/Matrix_column_coord_test.cpp)
target_link_libraries(Matrix_column_coord_test gtest_main)
add_test(NAME Matrix_column_coord_test COMMAND Matrix_column_coord_test)


add_executable(Matrix_row_coord_test src/Pos/Pos.h src/Matrix/Coords/Matrix_row_coord.h src/StringInt/StringInt.h src/StringInt/StringInt.cpp ${exceptions} test/Matrix/Coords/Matrix_row_coord_test.cpp)
target_link_libraries(Matrix_row_coord_test gtest_main)
add_test(NAME Matrix_row_coord_test COMMAND Matrix_row_coord_test)