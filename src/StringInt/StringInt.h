/**
 * Header containing StringInt class declaration.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_STRINGINT_H
#define COUNTING_STARS_STRINGINT_H

#include <string>
#include <map>
#include <iostream>

#include "../exceptions/exceptions.h"

/**
 * Class that implements integer interface with std::string representation.
 */
class StringInt {
public:
    /**
     * Default constructor
     */
    StringInt();

    /**
     * Constructor from string and char - the most preferable one.
     *
     * @param sign sing of a number
     * @param value string consisting only of digits
     */
    StringInt(char sign, std::string value);

    /**
     * Constructor for casting from std::string.
     *
     * @param number string that will be parsed into sign and absolute value of StringInt.
     */
    StringInt(const std::string& number); // NOLINT(google-explicit-constructor)

    /**
     * Constructor for casting from int.
     *
     * @param number signed integer number that will be parsed into sign and value of StringInt.
     */
    StringInt(const int& number); // NOLINT(google-explicit-constructor)

    /**
     * Constructor for casting from unsigned.
     *
     * @param number unsigned integer that will be used as value of StringInt.
     */
    StringInt(const unsigned& number); // NOLINT(google-explicit-constructor)

    /**
     * Constructor for casting from long long.
     *
     * @param number signed long long integer number that will be parsed into sign and value of StringInt.
     */
    StringInt(const long long&); // NOLINT(google-explicit-constructor)

    /**
     * Constructor for casting from unsigned long long.
     *
     * @param number unsigned long long integer number that will be parsed into value of StringIng.
     */
    StringInt(const unsigned long long&); // NOLINT(google-explicit-constructor)

    /**
     * sign setter.
     *
     * @param new_sign character that will be set as new sign.
     * @throws IllegalSignException
     */
    void set_sign(char new_sign);

    /**
     * sign setter.
     *
     * @param new_val string that will be set as new val .
     * @throws IllegalDigitException
     */
    void set_val(const std::string& new_val);

    /**
     * sign getter.
     *
     * @return sign of this StringIng
     */
    [[nodiscard]] char get_sign() const;

    /**
     * val getter.
     *
     * @return val of this StringIng
     */
    [[nodiscard]] std::string get_val() const;

    /**
     * @return this StringInt with opposite sign.
     */
    StringInt operator-() const;

    /**
     * Prefix increment.
     *
     * @return this StringInt increased by one.
     */
    StringInt& operator++();

    /**
     * Prefix decrement.
     *
     * @return this StringInt decreased by one.
     */
    StringInt& operator--();

    /**
     * Postfix increment.
     *
     * @return this StringInt increased by one.
     */
    StringInt operator++(int); // NOLINT(cert-dcl21-cpp)

    /**
     * Postfix decrement.
     *
     * @return this StringInt decreased by one.
     */
    StringInt operator--(int); // NOLINT(cert-dcl21-cpp)

    /**
     * Friend operator that prints StringInt to std::ostream.
     *
     * @param os output stream.
     * @param x StringInt to print.
     * @return os.
     */
    friend std::ostream& operator<< (std::ostream& os, StringInt const& x);

    /**
     * Friend operator that reads StringInt from std::istream.
     *
     * @param is input stream.
     * @param x StringInt to read to.
     * @return is.
     */
    friend std::istream& operator>> (std::istream& is, StringInt& x);

    /**
     * Friend equals operator.
     *
     * @param lhs left StringInt operand.
     * @param rhs right StringInt operand.
     * @return true if StringInts are equal, false otherwise.
     */
    friend bool operator==(const StringInt& lhs, const StringInt& rhs);

    /**
     * Friend not-equals operator.
     *
     * @param lhs left StringInt operand.
     * @param rhs right StringInt operand.
     * @return true if StringInts are not equal, false otherwise.
     */
    friend bool operator!=(const StringInt& lhs, const StringInt& rhs);

    /**
     * Friend less operator.
     *
     * @param lhs left StringInt operand.
     * @param rhs right StringInt operand.
     * @return true if lhs is less than rhs, false otherwise.
     */
    friend bool operator<(const StringInt& lhs, const StringInt& rhs);

    /**
     * Friend greater operator.
     *
     * @param lhs left StringInt operand.
     * @param rhs right StringInt operand.
     * @return true if lhs is greater than rhs, false otherwise.
     */
    friend bool operator>(const StringInt& lhs, const StringInt& rhs);

    /**
     * Friend leq operator.
     *
     * @param lhs left StringInt operand.
     * @param rhs right StringInt operand.
     * @return true if lhs is less than rhs or equal to it, false otherwise.
     */
    friend bool operator<=(const StringInt& lhs, const StringInt& rhs);

    /**
     * Friend geq operator.
     *
     * @param lhs left StringInt operand.
     * @param rhs right StringInt operand.
     * @return true if lhs is greater than rhs or equal to it, false otherwise.
     */
    friend bool operator>=(const StringInt& lhs, const StringInt& rhs);

    /**
     * Assigning plus operator.
     *
     * @param rhs right StringInt operand.
     * @return this StringInt, increased by rhs.
     */
    StringInt& operator+=(const StringInt& rhs);

    /**
     * Assigning minus operator.
     *
     * @param rhs right StringInt operand.
     * @return this StringInt, decreased by rhs.
     */
    StringInt& operator-=(const StringInt& rhs);

    /**
     * Assigning multiply operator.
     *
     * @param rhs right StringInt operand.
     * @return this StringInt, multiplied by rhs.
     */
    StringInt& operator*=(const StringInt& rhs);

    /**
     * Assigning division operator.
     *
     * @param rhs right StringInt operand.
     * @return this StringInt, divided by rhs.
     */
    StringInt& operator/=(const StringInt& rhs);

    /**
     * Boolean negation operator.
     *
     * @return true if this StringInt is equal to 0, false otherwise.
     */
    bool operator!() const;

    /**
     * Boolean cast operator.
     *
     * @return true if this StringInt is not equal to 0, false otherwise.
     */
    explicit operator bool() const;

    /**
     * std::string cast operator.
     *
     * @return string representation of this StringInt.
     */
    explicit operator std::string() const;


    /**
     * Friend function for calculating greatest common divider.
     *
     * @param lhs left StringInt operand.
     * @param rhs right StringInt operand.
     * @return greatest common divider of lhs and rhs.
     */
    friend StringInt gcd(StringInt lhs, StringInt rhs);

private:
    /**
     * Sign of this StringInt.
     */
    char sign;

    /**
     * Value of this StringInt.
     */
    std::string val;

    /**
     * Internal enum class used as return value of compare_as_numbers method.
     */
    enum class Comparator_result {
        /**
         * Left number is less that the right one.
         */
        LESS = -1,

        /**
         * Given numbers are equal.
         */
        EQUAL = 0,

        /**
         * Left number is greater that the right one.
         */
        GREATER = 1,
    };

    /**
     * Internal comparator between two strings interpreted as numbers.
     *
     * @param lhs left number of std::string.
     * @param rhs right number of std::string.
     * @return Comparator_result
     */
    static Comparator_result compare_as_numbers(const std::string& lhs, const std::string& rhs);

    /**
     * Method that removes all the leading zeros that appeared during any operator.
     */
    void remove_leading_zeros();

    /**
     * Internal function that implements bitwise char plus operator.
     *
     * @param lhs left digit.
     * @param rhs right digit.
     * @param overflow overflow of the sum of two digits.
     * @return sum of lhs and rhs as char.
     */
    static char plus(char lhs, char rhs, int& overflow);

    /**
     * Internal function that implements bitwise char minus operator.
     *
     * @param lhs left digit.
     * @param rhs right digit.
     * @param underflow underflow of decreasing lhs by rhs.
     * @return lhs decremented by rhs as char.
     */
    static char minus(char lhs, char rhs, int& underflow);

    /**
     * Internal function that implements bitwise char multiply operator.
     *
     * @param lhs left digit.
     * @param rhs right digit.
     * @param overflow overflow of the multiplication of two digits.
     * @return product of lhs and rhs as char.
     */
    static char multiply(char lhs, char rhs, int& overflow);

    /**
     * Internal function that implements bitwise string plus operator.
     *
     * @param lhs left number.
     * @param rhs right number.
     * @return sum of lhs and rhs as std::string.
     */
    static std::string plus(const std::string& lhs, const std::string& rhs);

    /**
     * Internal function that implements bitwise string minus operator.
     *
     * @param lhs left number.
     * @param rhs right number.
     * @return lhs decreased by rhs as std::string.
     */
    static std::string minus(std::string lhs, std::string rhs);

    /**
     * Internal function that implements a step of bitwise string multiply operator.
     *
     * @param lhs left number.
     * @param rhs right digit.
     * @return lhs multiplied by rhs std::string.
     */
    static std::string multiply(std::string lhs, char rhs);

    /**
     * Internal function that implements bitwise string multiply operator.
     *
     * @param lhs left number.
     * @param rhs right number.
     * @return product of lhs and rhs as std::string.
     */
    static std::string multiply(std::string lhs, const std::string &rhs);

    static std::pair<std::string, std::string> division_step(const std::string& current_number, const std::string& divisor);

    /**
     * Internal function that implements integer division operator.
     *
     * @param lhs left number.
     * @param rhs right number.
     * @return lhs divided by rhs as std::string.
     */
    static std::string divide_as_integers(std::string lhs, const std::string& rhs);

    /**
     * Internal function that removed leading zeros in string.
     *
     * @param val string that will be processed.
     * @return val with no leading zeroes.
     * @throws DivisionByZeroException
     */
    static void remove_leading_zeros(std::string& val);
};

/**
 * abs implementation for StringInt.
 *
 * @param number StringInt.
 * @return number with '+' sign.
 */
StringInt abs(StringInt number);

/**
 * Function that implements greatest common divider by euclidean algorithm.
 *
 * @param lhs left StringInt number.
 * @param rhs right StringInt number.
 * @return greatest common divider of lhs and rhs.
 */
StringInt gcd(StringInt lhs, StringInt rhs);

/**
 * @param lhs left StringInt number.
 * @param rhs right StringInt number.
 * @return sum or lhs and rhs.
 */
StringInt operator+(StringInt lhs, const StringInt& rhs);

/**
 * @param lhs left StringInt number.
 * @param rhs right StringInt number.
 * @return lhs decreased by rhs.
 */
StringInt operator-(StringInt lhs, const StringInt&);

/**
 * @param lhs left StringInt number.
 * @param rhs right StringInt number.
 * @return product or lhs and rhs.
 */
StringInt operator*(StringInt lhs, const StringInt&);

/**
 * @param lhs left StringInt number.
 * @param rhs right StringInt number.
 * @return lhs divided by rhs.
 */
StringInt operator/(StringInt lhs, const StringInt&);

#endif //COUNTING_STARS_STRINGINT_H
