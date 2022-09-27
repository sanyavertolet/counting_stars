/**
 * Header containing Rational_number class declaration.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_RATIONAL_NUMBER_H
#define COUNTING_STARS_RATIONAL_NUMBER_H

#include <string>
#include <cmath>
#include <cfloat>
#include <climits>

#include "../exceptions/exceptions.h"
#include "../StringInt/StringInt.h"

/**
 * Class that implements rational numbers over StringInt.
 */
class Rational_number {
public:
    /**
     * Default constructor
     */
    Rational_number();

    /**
     * Constructor from two StringInts - the most preferable one.
     *
     * @param sign sing of a number
     * @param value string consisting only of digits
     */
    Rational_number(StringInt num, StringInt denom);

    /**
     * @param num signed int that will be used as numerator.
     * @param denom unsigned int that will be used as denominator.
     */
    Rational_number(const signed& num, const unsigned& denom);

    /**
     * @param num signed long long int that will be used as numerator.
     * @param denom unsigned long long int that will be used as denominator.
     */
    Rational_number(const signed long long&, const unsigned long long&);

    /**
     * Constructor for casting from StringInt.
     *
     * @param num StringInt that will be used as numerator.
     */
    Rational_number(const StringInt& num);

    /**
     * Constructor for casting from signed int.
     *
     * @param num signed int that will be used as numerator.
     */
    Rational_number(const int& num); // NOLINT(google-explicit-constructor)

    /**
     * Constructor for casting from signed long long int.
     *
     * @param num signed long long int that will be used as numerator.
     */
    Rational_number(const signed long long&); // NOLINT(google-explicit-constructor)

    /**
     * Constructor for casting from long double.
     *
     * @param rational long double that will be parsed into numerator and denominator.
     */
    Rational_number(const long double& rational); // NOLINT(google-explicit-constructor)

    /**
     * Constructor for casting from double.
     *
     * @param rational double that will be parsed into numerator and denominator.
     */
    Rational_number(const double& rational); // NOLINT(google-explicit-constructor)

    /**
     * Constructor for casting from float.
     *
     * @param rational float that will be parsed into numerator and denominator.
     */
    Rational_number(const float& rational); // NOLINT(google-explicit-constructor)

    /**
     * Constructor for casting from std::string.
     *
     * @param rational std::string that will be parsed into numerator and denominator.
     */
    Rational_number(const std::string& rational); // NOLINT(google-explicit-constructor)

    /**
     * Operator for casting from long long.
     *
     * @param rational long long that will be parsed into numerator and denominator.
     */
    Rational_number& operator=(const long long& number);

    /**
     * Operator for casting from int.
     *
     * @param rational int that will be parsed into numerator and denominator.
     */
    Rational_number& operator=(const int& number);

    /**
     * Operator for casting from short.
     *
     * @param rational short that will be parsed into numerator and denominator.
     */
    Rational_number& operator=(const short& number);

    /**
     * Operator for casting from char.
     *
     * @param rational char that will be parsed into numerator and denominator.
     */
    Rational_number& operator=(const char& number);

    /**
     * Operator for casting from long double.
     *
     * @param rational long double that will be parsed into numerator and denominator.
     */
    Rational_number& operator=(const long double& number);

    /**
     * Operator for casting from double.
     *
     * @param rational double that will be parsed into numerator and denominator.
     */
    Rational_number& operator=(const double& number);

    /**
     * Operator for casting from float.
     *
     * @param rational float that will be parsed into numerator and denominator.
     */
    Rational_number& operator=(const float & number);

    /**
     * numerator setter.
     *
     * @param new_numerator StringInt that will be used as a new numerator of this Rational_number.
     */
    void set_numerator(const StringInt& new_numerator);

    /**
     * denominator setter.
     *
     * @param new_denominator StringInt that will be used as a new denominator of this Rational_number.
     * @throws IllegalSignException when new_denominator is negative.
     * @throws DivisionByZeroException when new_denominator equals to zero.
     */
    void set_denominator(const StringInt& new_denominator);

    /**
     * numerator getter.
     *
     * @return numerator of this Rational_number.
     */
    StringInt get_numerator();

    /**
     * denominator getter.
     *
     * @return denominator of this Rational_number.
     */
    StringInt get_denominator();

    /**
     * @return this Rational_number with opposite sign.
     */
    Rational_number operator-() const;

    /**
     * Prefix increment.
     *
     * @return this Rational_number increased by one.
     */
    Rational_number& operator++();

    /**
     * Prefix decrement.
     *
     * @return this Rational_number decreased by one.
     */
    Rational_number& operator--();

    /**
     * Postfix increment.
     *
     * @return this Rational_number increased by one.
     */
    Rational_number operator++(int); // NOLINT(cert-dcl21-cpp)

    /**
     * Postfix decrement.
     *
     * @return this Rational_number decreased by one.
     */
    Rational_number operator--(int); // NOLINT(cert-dcl21-cpp)

    /**
     * Friend operator that prints Rational_number to std::ostream.
     *
     * @param os output stream.
     * @param x Rational_number to print.
     * @return os.
     */
    friend std::ostream& operator<<(std::ostream& os, Rational_number const& x);

    /**
     * Friend operator that reads Rational_number from std::istream.
     *
     * @param is input stream.
     * @param x Rational_number to read to.
     * @return is.
     */
    friend std::istream& operator>>(std::istream& is, Rational_number& x);

    /**
     * Friend equals operator.
     *
     * @param lhs left Rational_number operand.
     * @param rhs right Rational_number operand.
     * @return true if Rational_numbers are equal, false otherwise.
     */
    friend bool operator==(const Rational_number& lhs, const Rational_number& rhs);

    /**
     * Friend not-equals operator.
     *
     * @param lhs left Rational_number operand.
     * @param rhs right Rational_number operand.
     * @return true if Rational_numbers are not equal, false otherwise.
     */
    friend bool operator!=(const Rational_number& lhs, const Rational_number& rhs);

    /**
     * Friend less operator.
     *
     * @param lhs left Rational_number operand.
     * @param rhs right Rational_number operand.
     * @return true if lhs is less than rhs, false otherwise.
     */
    friend bool operator<(const Rational_number& lhs, const Rational_number& rhs);

    /**
     * Friend greater operator.
     *
     * @param lhs left Rational_number operand.
     * @param rhs right Rational_number operand.
     * @return true if lhs is greater than rhs, false otherwise.
     */
    friend bool operator>(const Rational_number& lhs, const Rational_number& rhs);

    /**
     * Friend leq operator.
     *
     * @param lhs left Rational_number operand.
     * @param rhs right Rational_number operand.
     * @return true if lhs is less than rhs or equal to it, false otherwise.
     */
    friend bool operator<=(const Rational_number& lhs, const Rational_number& rhs);

    /**
     * Friend geq operator.
     *
     * @param lhs left Rational_number operand.
     * @param rhs right Rational_number operand.
     * @return true if lhs is greater than rhs or equal to it, false otherwise.
     */
    friend bool operator>=(const Rational_number& lhs, const Rational_number& rhs);

    /**
     * Assigning plus operator.
     *
     * @param rhs right Rational_number operand.
     * @return this Rational_number, increased by rhs.
     */
    Rational_number& operator+=(const Rational_number& rhs);

    /**
     * Assigning minus operator.
     *
     * @param rhs right Rational_number operand.
     * @return this Rational_number, decreased by rhs.
     */
    Rational_number& operator-=(const Rational_number& rhs);

    /**
     * Assigning multiply operator.
     *
     * @param rhs right Rational_number operand.
     * @return this Rational_number, multiplied by rhs.
     */
    Rational_number& operator*=(const Rational_number& rhs);

    /**
     * Assigning division operator.
     *
     * @param rhs right Rational_number operand.
     * @return this Rational_number, divided by rhs.
     */
    Rational_number& operator/=(const Rational_number& rhs);

    /**
     * Boolean negation operator.
     *
     * @return true if this Rational_number is equal to 0, false otherwise.
     */
    bool operator!() const;

    /**
     * Boolean cast operator.
     *
     * @return true if this Rational_number is not equal to 0, false otherwise.
     */
    explicit operator bool() const;

    /**
     * long double cast operator.
     *
     * @return this Rational_number casted to long double.
     * @throws OverflowException
     */
    operator long double() const;

    /**
     * double cast operator.
     *
     * @return this Rational_number casted to double.
     * @throws OverflowException
     */
    operator double() const;

    /**
     * float cast operator.
     *
     * @return this Rational_number casted to float.
     * @throws OverflowException
     */
    operator float() const;

    /**
     * long long cast operator.
     *
     * @return this Rational_number casted to long long.
     * @throws OutOfIntegerDivisionException, OverflowException
     */
    operator long long() const;

    /**
     * int cast operator.
     *
     * @return this Rational_number casted to int.
     * @throws OutOfIntegerDivisionException, OverflowException
     */
    operator int() const;

    /**
     * short cast operator.
     *
     * @return this Rational_number casted to short.
     * @throws OutOfIntegerDivisionException, OverflowException
     */
    operator short() const;

    /**
     * char cast operator.
     *
     * @return this Rational_number casted to char.
     * @throws OutOfIntegerDivisionException, OverflowException
     */
    operator char() const;

    /**
     * std::string cast operator.
     *
     * @return string representation of this Rational_number.
     */
    explicit operator std::string() const;

    /**
     * Get floor of this Rational_number.
     *
     * @return Floor of this Rational_number as StringInt.
     */
    [[nodiscard]] StringInt floor() const;

    /**
     * Get round of this Rational_number.
     *
     * @return Round of this Rational_number as StringInt.
     */
    [[nodiscard]] StringInt round() const;

    /**
     * Simplify this Rational_number.
     *
     * @return this simplified Rational_number.
     */
    Rational_number& make_canonical();

private:
    /**
     * numerator of this Rational_number
     */
    StringInt numerator;

    /**
     * denominator of this Rational_number.
     */
    StringInt denominator;

    /**
     * Internal method to perform casts to integer types.
     *
     * @param type_name name of required type - used for exception message.
     * @param min minimal possible value of required type
     * @param max maximal possible value of required type
     * @param ignore_exceptions flag that defined whether OutOfIntegerDivisionException should be thrown or not.
     * @return this Rational_number casted to required type
     * @throws OutOfIntegerDivisionException, OverflowException
     */
    [[nodiscard]]
    StringInt cast_to_integer(
            const std::string& type_name,
            const StringInt& min,
            const StringInt& max,
            bool ignore_exceptions = false,
            bool ignore_overflows = false
                    ) const;

    /**
     * Internal method to perform casts to floating point types.
     *
     * @param type_name name of required type - used for exception message.
     * @param min minimal possible value of required type
     * @param max maximal possible value of required type
     * @return this Rational_number casted to required type
     * @throws OutOfIntegerDivisionException, OverflowException
     */
    [[nodiscard]]
    long double cast_to_floating(const std::string& type_name, const long double& min, const long double& max) const;

    /**
     * Internal validation method.
     * @throws DivisionByZeroException
     */
    void validate() const;
};

/**
 * @param lhs left Rational_number number.
 * @param rhs right Rational_number number.
 * @return sum of lhs and rhs.
 */
Rational_number operator+(Rational_number lhs, const Rational_number& rhs);

/**
 * @param lhs left Rational_number number.
 * @param rhs right Rational_number number.
 * @return lhs decreased by rhs.
 */
Rational_number operator-(Rational_number lhs, const Rational_number& rhs);

/**
 * @param lhs left Rational_number number.
 * @param rhs right Rational_number number.
 * @return product of lhs and rhs.
 */
Rational_number operator*(Rational_number lhs, const Rational_number& rhs);

/**
 * @param lhs left Rational_number number.
 * @param rhs right Rational_number number.
 * @return lhs divided by rhs.
 */
Rational_number operator/(Rational_number lhs, const Rational_number& rhs);

#endif //COUNTING_STARS_RATIONAL_NUMBER_H
