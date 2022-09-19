/**
 * Rational_number implementation.
 *
 * @author sanyavertolet
 */

#include "Rational_number.h"

// ================================== CONSTRUCTORS ===================================

Rational_number::Rational_number(): numerator(1), denominator(1) { }

Rational_number::Rational_number(const StringInt& num): numerator(num), denominator(1) { }

Rational_number::Rational_number(StringInt num, StringInt denom) {
    numerator = std::move(num);
    denominator = std::move(denom);
    if (numerator.get_sign() == denominator.get_sign()) {
        numerator.set_sign('+');
    } else {
        numerator.set_sign('-');
    }
    denominator.set_sign('+');
    validate();
}

Rational_number::Rational_number(const signed& num, const unsigned& denom): numerator(num), denominator(denom) {
    validate();
}

Rational_number::Rational_number(const int& number): numerator(number), denominator(1) { }

Rational_number::Rational_number(const std::string& rational) {
    auto number = rational;
    if (number.empty()) {
        throw std::runtime_error("Invalid input number: [" + number + "]");
    }
    char numerator_sign = '+';
    if (number[0] == '-' || number[0] == '+') {
        numerator_sign = number[0];
        number.erase(0, 1);
    }
    auto slash_pos = number.find('/');
    if (slash_pos == std::string::npos) {
        auto dot_pos = number.find('.');
        if (dot_pos == std::string::npos) {
            set_numerator(number);
            denominator = 1;
        } else {
            auto power = number.substr(dot_pos).size() - 1;
            number.erase(dot_pos, 1);
            set_numerator(number);
            set_denominator(1);
            for (int i = 0; i < power; ++i) {
                set_denominator(denominator.get_val() += "0");
            }
        }
    } else {
        if (slash_pos + 1 < number.length()) {
            auto denominator_from_string = number.substr(slash_pos + 1);
            if (denominator_from_string[0] == '-') {
                numerator_sign = numerator_sign == '+' ? '-' : '+';
                denominator_from_string.erase(denominator_from_string.begin());
            } else if (denominator_from_string[0] == '+') {
                denominator_from_string.erase(denominator_from_string.begin());
            }
            set_denominator(denominator_from_string);
        }
        set_numerator(number.substr(0, slash_pos));
        numerator.set_sign(numerator_sign);
    }
    if (numerator == 0) {
        set_denominator(1);
    }
    validate();
}

Rational_number::Rational_number(const signed long long& num): numerator(num), denominator(1) { }

Rational_number::Rational_number(const signed long long& num, const unsigned long long& denom): numerator(num), denominator(denom) {
    validate();
}

Rational_number::Rational_number(const long double &rational) {
    Rational_number required_number = Rational_number(std::to_string(rational));
    set_numerator(required_number.numerator);
    set_denominator(required_number.denominator);
}

Rational_number::Rational_number(const double &rational) {
    Rational_number required_number = Rational_number(std::to_string(rational));
    set_numerator(required_number.numerator);
    set_denominator(required_number.denominator);
}

Rational_number::Rational_number(const float &rational) {
    Rational_number required_number = Rational_number(std::to_string(rational));
    set_numerator(required_number.numerator);
    set_denominator(required_number.denominator);
}

// ================================== COPY OPERATORS ===================================

Rational_number& Rational_number::operator=(const long long& number) {
    Rational_number result(number);
    *this = result;
    return *this;
}

Rational_number& Rational_number::operator=(const int& number) {
    Rational_number result(number);
    *this = result;
    return *this;
}

Rational_number& Rational_number::operator=(const short& number) {
    Rational_number result(number);
    *this = result;
    return *this;
}

Rational_number& Rational_number::operator=(const char& number) {
    Rational_number result(number);
    *this = result;
    return *this;
}

Rational_number& Rational_number::operator=(const long double& number) {
    Rational_number result(number);
    *this = result;
    return *this;
}

Rational_number& Rational_number::operator=(const double& number) {
    Rational_number result(number);
    *this = result;
    return *this;
}

Rational_number& Rational_number::operator=(const float & number) {
    Rational_number result(number);
    *this = result;
    return *this;
}

// ================================== SETTERS ===================================

void Rational_number::set_numerator(const StringInt& new_numerator) {
    numerator = new_numerator;
}

void Rational_number::set_denominator(const StringInt& new_denominator) {
    if (new_denominator == 0) {
        throw DivisionByZeroException("Denominator cannot be null.");
    } else if (new_denominator.get_sign() != '+') {
        throw IllegalSignException("Denominator must be unsigned.");
    } else {
        denominator = new_denominator;
    }
}

// ================================== GETTERS ===================================

StringInt Rational_number::get_numerator() {
    return numerator;
}
StringInt Rational_number::get_denominator() {
    return denominator;
}

// ================================== INC/DEC ===================================

Rational_number Rational_number::operator-() const {
    return { -numerator, denominator };
}

Rational_number& Rational_number::operator++() {
    *this += 1;
    return this->make_canonical();
}

//NOLINTNEXTLINE
Rational_number Rational_number::operator++(int) {
    Rational_number tmp(*this);
    operator++();
    make_canonical();
    return tmp;
}

Rational_number& Rational_number::operator--() {
    *this -= 1;
    return this->make_canonical();
}

//NOLINTNEXTLINE
Rational_number Rational_number::operator--(int) {
    Rational_number tmp(*this);
    operator--();
    make_canonical();
    return tmp;
}

// ================================== STREAMS ===================================

std::ostream& operator<< (std::ostream& os, Rational_number const& x) {
    os << std::string(x);
    return os;
}

std::istream& operator>> (std::istream& is, Rational_number& x) {
    std::string rational_number_string;
    is >> rational_number_string;
    x = Rational_number(rational_number_string);
    return is;
}

// ================================== COMPARATORS ===================================

bool operator<(const Rational_number& lhs, const Rational_number& rhs) {
    return lhs.numerator * rhs.denominator < rhs.numerator * lhs.denominator;
}

bool operator>(const Rational_number& lhs, const Rational_number& rhs) {
    return rhs < lhs;
}

bool operator==(const Rational_number& lhs, const Rational_number& rhs) {
    Rational_number simplified_lhs = lhs;
    simplified_lhs.make_canonical();
    Rational_number simplified_rhs = rhs;
    simplified_rhs.make_canonical();
    return simplified_lhs.numerator == simplified_rhs.numerator && simplified_lhs.denominator == simplified_rhs.denominator;
}

bool operator!=(const Rational_number& lhs, const Rational_number& rhs) {
    return !(lhs == rhs);
}

bool operator<=(const Rational_number& lhs, const Rational_number& rhs) {
    return !(lhs > rhs);
}

bool operator>=(const Rational_number& lhs, const Rational_number& rhs) {
    return rhs <= lhs;
}

// ================================== ASSIGNING BINARY OPERATORS ===================================

Rational_number& Rational_number::operator+=(const Rational_number &rhs) {
    auto greatest_common_divider = gcd(denominator, rhs.denominator);
    auto left_multiplier = rhs.denominator / greatest_common_divider;
    auto right_multiplier = denominator / greatest_common_divider;
    auto left_extended_numerator = numerator * left_multiplier;
    auto right_extended_numerator = rhs.numerator * right_multiplier;
    numerator = left_extended_numerator + right_extended_numerator;
    denominator *= left_multiplier;
    return this->make_canonical();
}

Rational_number& Rational_number::operator-=(const Rational_number &rhs) {
    auto greatest_common_divider = gcd(denominator, rhs.denominator);
    auto left_multiplier = rhs.denominator / greatest_common_divider;
    auto right_multiplier = denominator / greatest_common_divider;
    auto left_extended_numerator = numerator * left_multiplier;
    auto right_extended_numerator = rhs.numerator * right_multiplier;
    numerator = left_extended_numerator - right_extended_numerator;
    denominator *= left_multiplier;
    return this->make_canonical();
}

Rational_number& Rational_number::operator*=(const Rational_number &rhs) {
    numerator *= rhs.numerator;
    denominator *= rhs.denominator;
    return this->make_canonical();
}

Rational_number& Rational_number::operator/=(const Rational_number &rhs) {
    if (rhs.numerator == 0) {
        throw DivisionByZeroException();
    }
    numerator.set_sign(numerator.get_sign() == rhs.numerator.get_sign() ? '+' : '-');
    numerator *= rhs.denominator;
    denominator = abs(denominator * rhs.numerator);
    return this->make_canonical();
}

// ================================== BINARY OPERATORS ===================================

Rational_number operator+(Rational_number lhs, const Rational_number& rhs) {
    return lhs += rhs;
}

Rational_number operator-(Rational_number lhs, const Rational_number& rhs) {
    return lhs -= rhs;
}

Rational_number operator*(Rational_number lhs, const Rational_number& rhs) {
    return lhs *= rhs;
}

Rational_number operator/(Rational_number lhs, const Rational_number& rhs) {
    return lhs /= rhs;
}

// ================================== BOOLEAN OPERATORS ===================================

bool Rational_number::operator!() const {
    return !(operator bool());
}

// ================================== CASTS ===================================

Rational_number::operator bool() const {
    return numerator != 0;
}

Rational_number::operator long double() const {
    return cast_to_floating("long double", LDBL_MIN, LDBL_MAX);
}

Rational_number::operator double() const {
    return double(cast_to_floating("double", DBL_MIN, DBL_MAX));
}

Rational_number::operator float() const {
    return float(cast_to_floating("float", FLT_MIN, FLT_MAX));
}

Rational_number::operator long long() const {
    return (long long)(cast_to_integer("long long", LONG_LONG_MIN, LONG_LONG_MAX));
}

Rational_number::operator int() const {
    return int(cast_to_integer("int", INT_MIN, INT_MAX));
}

Rational_number::operator short() const {
    return short(cast_to_integer("short", SHRT_MIN, SHRT_MAX));
}

Rational_number::operator char() const {
    return char(cast_to_integer("char", CHAR_MIN, CHAR_MAX));
}

Rational_number::operator std::string() const {
    return std::string(numerator) + "/" + denominator.get_val();
}

// ================================== UTILITY METHODS ===================================

StringInt Rational_number::floor() const {
    return cast_to_integer("", 0, 0, true, true);
}

StringInt Rational_number::round() const {
    Rational_number extended_number = (*this * Rational_number(10));
    StringInt result = cast_to_integer("", 0, 0, true, true);
    if ((extended_number - *this).cast_to_integer("", 0, 0, true, true).get_val()[0] < 5) {
        return result;
    } else {
        return result + 1;
    }
}

Rational_number& Rational_number::make_canonical() {
    if (numerator == 0) {
        numerator.set_sign('+');
        denominator = 1;
    } else {
        StringInt greatest_common_divider = gcd(numerator, denominator);
        numerator /= greatest_common_divider;
        denominator /= greatest_common_divider;
    }
    return *this;
}

// ================================== PRIVATE METHODS ===================================

StringInt Rational_number::cast_to_integer(const std::string& type_name, const StringInt& min, const StringInt& max, bool ignore_div_exception, bool ignore_overflows) const {
    if (!ignore_overflows && (Rational_number(max) < *this || *this < Rational_number(min))) {
        throw OverflowException(operator std::string() + " overflows " + type_name + ".");
    }
    auto division_result = numerator / denominator;
    if (!ignore_div_exception && *this != division_result * denominator) {
        throw OutOfIntegerDivisionException(operator std::string() + " cannot be mapped to integers without precision loss.");
    }
    return division_result;
}

long double Rational_number::cast_to_floating(const std::string& type_name, const long double& min, const long double& max) const {
    if (Rational_number(max) < *this || *this < Rational_number(min)) {
        throw OverflowException(operator std::string() + " overflows " + type_name + ".");
    }
    Rational_number extended_number = *this;
    StringInt power_of_10 = 1;
    for (int i = 0; i < LDBL_DECIMAL_DIG; ++i) {
        extended_number *= Rational_number(10);
        power_of_10 *= 10;
    }
    StringInt integer_result = numerator / denominator;
    return (long double)(integer_result) / (long double)(power_of_10);
}

void Rational_number::validate() const {
    if (denominator == StringInt(0)) {
        throw DivisionByZeroException("Denominator of rational number should not be null: " + std::string(numerator) + "/" + std::string(denominator));
    }
}
