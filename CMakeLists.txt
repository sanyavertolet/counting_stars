cmake_minimum_required(VERSION 3.22)
project(counting_stars)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(exceptions src/exceptions/exceptions.h src/exceptions/IllegalSignException/IllegalSignException.h src/exceptions/IllegalDigitException/IllegalDigitException.h src/exceptions/DivisionByZeroException/DivisionByZeroException.h src/exceptions/ParseException/ParseException.h src/exceptions/CastException/CastException.h src/exceptions/OutOfRangeException/OutOfRangeException.h src/exceptions/OutOfIntegerDivisionException/OutOfIntegerDivisionException.h src/exceptions/OverflowException/OverflowException.h src/exceptions/ParseException/ParseException.h src/exceptions/FileNotFoundException/FileNotFoundException.h src/exceptions/FileNotFoundException/FileNotFoundException.cpp src/exceptions/NullPointerException/NullPointerException.h src/exceptions/NullPointerException/NullPointerException.cpp src/exceptions/IllegalCapacityException/IllegalCapacityException.h src/exceptions/IllegalCapacityException/IllegalCapacityException.cpp)

set(StringInt src/StringInt/StringInt.h src/StringInt/StringInt.cpp)
set(Rational_number src/Rational_number/Rational_number.h src/Rational_number/Rational_number.cpp)
set(Complex_number src/Complex_number/Complex_number.h)
set(Vector src/Vector/Vector.h src/Vector/Vector.cpp src/Vector/Vector.bool.cpp)
set(Pos src/Pos/Pos.h src/Pos/Pos.cpp)
set(Matrix src/Matrix/Matrix.h src/Matrix/Coords/Matrix_coords.h src/Matrix/Coords/Matrix_row_coord.h src/Matrix/Coords/Matrix_column_coord.h src/Matrix/Matrix_proxy.h src/Matrix/Coords/Matrix_coords.cpp src/Matrix/Coords/Matrix_row_coord.cpp src/Matrix/Coords/Matrix_column_coord.cpp)

add_library(counting_stars ${StringInt} ${Rational_number} ${Complex_number} ${Vector} ${Pos} ${Matrix} ${exceptions})

add_executable(tests test/StringInt/StringInt_constructor_test.cpp test/StringInt/StringInt_operators_test.cpp test/StringInt/StringInt_cast_test.cpp test/Rational_number/Rational_number_constructor_test.cpp test/Rational_number/Rational_number_operators_test.cpp test/Complex_number/Complex_number_constructor_test.cpp test/Complex_number/Complex_number_operators_test.cpp test/Vector/Vector_test.cpp test/Matrix/Coords/Matrix_coords_test.cpp test/Matrix/Coords/Matrix_row_coord_test.cpp test/Matrix/Coords/Matrix_column_coord_test.cpp test/Pos/Pos_test.cpp test/Matrix/Matrix_test.cpp)
target_link_libraries(tests counting_stars)
target_link_libraries(tests gtest_main)
add_test(NAME tests COMMAND tests)

add_executable(StringInt_test test/StringInt/StringInt_constructor_test.cpp test/StringInt/StringInt_operators_test.cpp test/StringInt/StringInt_cast_test.cpp)
target_link_libraries(StringInt_test counting_stars)
target_link_libraries(StringInt_test gtest_main)
add_test(NAME StringInt_test COMMAND StringInt_test)

add_executable(Rational_number_test test/Rational_number/Rational_number_constructor_test.cpp test/Rational_number/Rational_number_operators_test.cpp)
target_link_libraries(Rational_number_test counting_stars)
target_link_libraries(Rational_number_test gtest_main)
add_test(NAME Rational_number_test COMMAND Rational_number_test)

add_executable(Complex_number_test test/Complex_number/Complex_number_constructor_test.cpp test/Complex_number/Complex_number_operators_test.cpp)
target_link_libraries(Complex_number_test counting_stars)
target_link_libraries(Complex_number_test gtest_main)
add_test(NAME Complex_number_test COMMAND Complex_number_test)

add_executable(Vector_test test/Vector/Vector_test.cpp)
target_link_libraries(Vector_test counting_stars)
target_link_libraries(Vector_test gtest_main)
add_test(NAME Vector_test COMMAND Vector_test)

add_executable(Pos_test test/Pos/Pos_test.cpp)
target_link_libraries(Pos_test counting_stars)
target_link_libraries(Pos_test gtest_main)
add_test(NAME Pos_test COMMAND Pos_test)

add_executable(Coords_test test/Matrix/Coords/Matrix_coords_test.cpp test/Matrix/Coords/Matrix_row_coord_test.cpp test/Matrix/Coords/Matrix_column_coord_test.cpp)
target_link_libraries(Coords_test counting_stars)
target_link_libraries(Coords_test gtest_main)
add_test(NAME Coords_test COMMAND Coords_test)

add_executable(Matrix_test test/Matrix/Matrix_test.cpp)
target_link_libraries(Matrix_test counting_stars)
target_link_libraries(Matrix_test gtest_main)
add_test(NAME Matrix_test COMMAND Matrix_test)
