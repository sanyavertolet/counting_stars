/**
 * File containing StringInt class implementation.
 *
 * @author sanyavertolet
 */

#include "StringInt.h"

#include <utility>

// ================================== CONSTRUCTORS ===================================

StringInt::StringInt(): sign('+'), val(std::to_string(0)) {}

StringInt::StringInt(const std::string& number) {
    if (number[0] == '+' || number[0] == '-') {
        sign = number[0];
        set_val(number.substr(1));
    } else if (isnumber(number[0])) {
        sign = '+';
        set_val(number);
    } else {
        throw IllegalSignException(std::string(1, number[0]));
    }
}

StringInt::StringInt(char s, std::string v): sign(s), val(std::move(v)) { }

StringInt::StringInt(const int& number): sign(number < 0 ? '-' : '+'), val(std::to_string(abs(number))) { }

StringInt::StringInt(const unsigned& number): sign('+'), val(std::to_string(number)) { }

StringInt::StringInt(const unsigned long& number): sign('+'), val(std::to_string(number)) { }

StringInt::StringInt(const long long& number): sign(number < 0 ? '-' : '+'), val(std::to_string(abs(number))) { }

StringInt::StringInt(const unsigned long long& number): sign('+'), val(std::to_string(number)) { }

StringInt::StringInt(const long double& number): sign(number < 0 ? '-' : '+'), val(std::to_string(static_cast<unsigned long long>(abs(number)))) { }

StringInt::StringInt(const double& number): sign(number < 0 ? '-' : '+'), val(std::to_string(static_cast<unsigned long long>(abs(number)))) { }

StringInt::StringInt(const float& number): sign(number < 0 ? '-' : '+'), val(std::to_string(static_cast<unsigned long long>(abs(number)))) { }

// ================================== COPY OPERATORS ===================================

StringInt& StringInt::operator=(const long long& number) {
    StringInt result(number);
    *this = result;
    return *this;
}

StringInt& StringInt::operator=(const int& number) {
    StringInt result(number);
    *this = result;
    return *this;
}

StringInt& StringInt::operator=(const short& number) {
    StringInt result(number);
    *this = result;
    return *this;
}

StringInt& StringInt::operator=(const char& number) {
    StringInt result(number);
    *this = result;
    return *this;
}

StringInt& StringInt::operator=(const long double& number) {
    StringInt result(number);
    *this = result;
    return *this;
}

StringInt& StringInt::operator=(const double& number) {
    StringInt result(number);
    *this = result;
    return *this;
}

StringInt& StringInt::operator=(const float& number) {
    StringInt result(number);
    *this = result;
    return *this;
}

// ================================== SETTERS ===================================

void StringInt::set_sign(char s) {
    if (s == '+' || s == '-') {
        sign = s;
    } else {
        throw IllegalSignException("Sign should be either '+' or '-', got '" + std::string(1, sign) + "'.");
    }
}

void StringInt::set_val(const std::string& v) {
    for (char i : v) {
        if (!isnumber(i)) {
            throw IllegalDigitException("Val should contain only digits, got '" + std::string(1, i) + "' symbol.");
        }
    }
    val = v;
}

// ================================== GETTERS ===================================

char StringInt::get_sign() const {
    return sign;
}

std::string StringInt::get_val() const {
    return val;
}

// ================================== INC/DEC ===================================

StringInt StringInt::operator-() const {
    return { sign == '-' ? '+' : '-', val };
}

StringInt& StringInt::operator++() {
   *this += 1;
    return *this;
}

StringInt& StringInt::operator--() {
    *this -= 1;
    return *this;
}

StringInt StringInt::operator++(int) {
    StringInt tmp(*this);
    operator++();
    return tmp;
}
StringInt StringInt::operator--(int) {
    StringInt tmp(*this);
    operator--();
    return tmp;
}

// ================================== STREAMS ===================================

std::ostream& operator<<(std::ostream& os, StringInt const& x) {
    os << std::string(x);
    return os;
}

std::istream& operator>>(std::istream& is, StringInt& x) {
    std::string number;
    is >> number;
    x = StringInt(number);
    return is;
}

// ================================== COMPARATORS ===================================

bool operator==(const StringInt& lhs, const StringInt& rhs) {
    return lhs.val == rhs.val && (lhs.val == "0" || lhs.sign == rhs.sign);
}

bool operator!=(const StringInt& lhs, const StringInt &rhs) {
    return !(lhs == rhs);
}

bool operator<(const StringInt& lhs, const StringInt &rhs) {
    if (lhs.sign == '-' && rhs.sign == '+') {
        return true;
    } else if (lhs.sign == '+' && rhs.sign == '-') {
        return false;
    }
    StringInt::Comparator_result abs_comparator_result = StringInt::compare_as_numbers(lhs.val, rhs.val);
    if (lhs.sign == '+' && rhs.sign == '+' && abs_comparator_result == StringInt::Comparator_result::LESS ||
        lhs.sign == '-' && rhs.sign == '-' && abs_comparator_result == StringInt::Comparator_result::GREATER) {
        return true;
    }
    return false;
}

bool operator>(const StringInt& lhs, const StringInt& rhs) {
    return rhs < lhs;
}

bool operator<=(const StringInt& lhs, const StringInt& rhs) {
    return !(lhs > rhs);
}

bool operator>=(const StringInt& lhs, const StringInt& rhs) {
    return rhs <= lhs;
}

// ================================== ASSIGNING BINARY OPERATORS ===================================

StringInt& StringInt::operator+=(const StringInt& other) {
    Comparator_result abs_com_result = compare_as_numbers(val, other.val);
    if (sign == other.sign) {
        val = plus(val, other.val);
    } else {
        val = minus(val, other.val);
        if (abs_com_result == Comparator_result::LESS) {
            sign = other.sign;
        }
    }
    remove_leading_zeros();
    return *this;
}

StringInt& StringInt::operator-=(const StringInt& other) {
    Comparator_result abs_com_result = compare_as_numbers(val, other.val);
    if (sign != other.sign) {
        val = plus(val, other.val);
    } else {
        val = minus(val, other.val);
        if (abs_com_result == Comparator_result::LESS) {
            sign = (other.sign == '+' ? '-' : '+');
        }
    }
    remove_leading_zeros();
    return *this;
}

StringInt& StringInt::operator*=(const StringInt& other) {
    if (sign == other.sign) {
        sign = '+';
    } else {
        sign = '-';
    }
    val = multiply(val, other.val);
    remove_leading_zeros();
    return *this;
}

StringInt& StringInt::operator/=(const StringInt& other) {
    if (sign == other.sign) {
        sign = '+';
    } else {
        sign = '-';
    }
    val = divide_as_integers(val, other.val);
    remove_leading_zeros();
    return *this;
}

// ================================== BINARY OPERATORS ===================================

StringInt operator+(StringInt lhs, const StringInt& rhs) {
    return (lhs += rhs);
}

StringInt operator-(StringInt lhs, const StringInt& rhs) {
    return (lhs -= rhs);
}

StringInt operator*(StringInt lhs, const StringInt& rhs) {
    return (lhs *= rhs);
}

StringInt operator/(StringInt lhs, const StringInt& rhs) {
    return (lhs /= rhs);
}

// ================================== BOOLEAN OPERATORS ===================================

bool StringInt::operator!() const {
    return !(operator bool());
}

// ================================== CAST OPERATORS ===================================

StringInt::operator bool() const {
    return val != "0";
}

StringInt::operator long long() const {
    return downcast_to("long long", LONG_LONG_MIN, LONG_LONG_MAX);
}

StringInt::operator int() const {
    return int(downcast_to("int", INT_MIN, INT_MAX));
}

StringInt::operator short() const {
    return short(downcast_to("short", SHRT_MIN, SHRT_MAX));
}

StringInt::operator char() const {
    return char(downcast_to("char", CHAR_MIN, CHAR_MAX));
}

StringInt::operator long double() const {
    if (static_cast<long long>(LDBL_MAX) < *this || *this < static_cast<long long>(LDBL_MIN)) {
        throw OverflowException(operator std::string() + " overflows long long.");
    }
    return (long double)((long long)(*this));
}

long long StringInt::downcast_to(const std::string& type_name, long long minimal, long long maximal) const {
    if (*this < minimal || maximal < *this) {
        throw OverflowException(operator std::string() + "overflows " + type_name = ".");
    }
    long long value_as_num = 0;
    for (char digit : val) {
        value_as_num = value_as_num * 10 + digit;
    }
    return value_as_num;
}

StringInt::operator std::string() const {
    return (sign == '-' ? std::string(1, sign) : "") +  val;
}

// ================================== UTILITY METHODS ===================================

StringInt gcd(StringInt one, StringInt other) {
    one.sign = '+';
    other.sign = '+';
    while (one.val != "0" && other.val != "0") {
        if (StringInt::compare_as_numbers(one.val, other.val) == StringInt::Comparator_result::LESS) {
            std::swap(one, other);
        }
        one -= other;
    }
    if (one.val == "0") {
        return {'+', other.val};
    } else {
        return {'+', one.val};
    }
}

StringInt abs(StringInt number) {
    number.set_sign('+');
    return number;
}

// ================================== PRIVATE METHODS ===================================

void StringInt::remove_leading_zeros() {
    while(val.length() > 1 && val[0] == '0') {
        val.erase(val.begin());
    }
}

StringInt::Comparator_result StringInt::compare_as_numbers(const std::string &one, const std::string &another) {
    if (one.empty() || another.empty()) {
        throw std::runtime_error("Wrong strings: [" + one + "] and [" + another + "]");
    }
    if (one.length() > another.length()) {
        return Comparator_result::GREATER;
    } else if (another.length() > one.length()) {
        return Comparator_result::LESS;
    } else {
        for (int i = 0; i < one.length(); ++i) {
            if (one[i] > another[i]) {
                return Comparator_result::GREATER;
            } else if (another[i] > one[i]) {
                return Comparator_result::LESS;
            }
        }
        return Comparator_result::EQUAL;
    }
}

char StringInt::plus(char one, char another, int &overflow) {
    auto tmp = (one - '0') + (another - '0') + overflow;
    overflow = tmp / 10;
    return char(tmp % 10 + '0');
}

char StringInt::minus(char one, char another, int &underflow) {
    auto tmp = one - another - underflow;
    if (tmp < 0) {
        underflow = 1;
    } else {
        underflow = 0;
    }
    return char((10 + tmp) % 10 + '0');
}

char StringInt::multiply(char one, char another, int &overflow) {
    auto tmp = (one - '0') * (another - '0') + overflow;
    overflow = tmp / 10;
    return char(tmp % 10 + '0');
}

std::string StringInt::multiply(std::string number, char multiplier) {
    if (multiplier == '0' || number == "0") {
        return "0";
    }
    std::string result;
    int overflow = 0;
    for (int i = 0; i < number.length(); ++i) {
        char new_digit = multiply(number[number.length() - i - 1], multiplier, overflow);
        result = std::string(1, new_digit).append(result);
    }
    if (overflow != 0) {
        result = std::string(1, char(overflow + '0')).append(result);
    }
    return result;
}

std::string StringInt::plus(const std::string& one, const std::string& another) {
    std::string result;
    auto max_length = std::max(one.length(), another.length());
    int overflow = 0;
    for (auto i = 0; i < max_length; ++i) {
        char one_digit;
        if (one.length() > i) {
            one_digit = one[one.length() - i - 1];
        } else {
            one_digit = '0';
        }
        char another_digit;
        if (another.length() > i) {
            another_digit = another[another.length() - i - 1];
        } else {
            another_digit = '0';
        }

        auto new_digit = plus(one_digit, another_digit, overflow);
        result = std::string(1, new_digit).append(result);
    }
    if (overflow != 0) {
        result = std::string(1, char(overflow + '0')).append(result);
    }
    remove_leading_zeros(result);
    return result;
}

std::string StringInt::minus(std::string one, std::string another) {
    if (one == another) {
        return "0";
    }
    std::string result;
    if (compare_as_numbers(one, another) == Comparator_result::LESS) {
        std::swap(one, another);
    }
    int underflow = 0;
    for (int i = 0; i < one.length(); ++i) {
        char one_digit = one[one.length() - i - 1];
        char another_digit;
        if (another.length() > i) {
            another_digit = another[another.length() - i - 1];
        } else {
            another_digit = '0';
        }
        auto new_digit = minus(one_digit, another_digit, underflow);
        result = std::string(1, new_digit).append(result);
    }
    remove_leading_zeros(result);
    return result;
}

std::string StringInt::multiply(std::string one, const std::string& another) {
    if (one == "0" || another == "0") {
        return "0";
    }
    std::string result = "0";
    std::string postfix_nulls;
    for (int i = 0; i < one.length(); ++i) {
        char multiplier = one[one.length() - i - 1];
        std::string temp_result = multiply(another, multiplier).append(postfix_nulls);
        result = plus(result, temp_result);
        postfix_nulls = postfix_nulls.append("0");
    }
    remove_leading_zeros(result);
    return result;
}

std::pair<std::string, std::string> StringInt::division_step(const std::string& current_number, const std::string& divisor) {
    std::string current_divisor = divisor;
    if (compare_as_numbers(current_number, divisor) == Comparator_result::LESS) {
        return { "0", "0" };
    }
    int i;
    for (i = 1; i < 10; ++i) {
        auto new_current_divisor = plus(current_divisor, divisor);
        if (compare_as_numbers(current_number, new_current_divisor) == Comparator_result::LESS) {
            return { { char(i + '0') }, current_divisor };
        } else {
            current_divisor = new_current_divisor;
        }
    }
    return { "0", "0" };
}

std::string StringInt::divide_as_integers(std::string one, const std::string& another) {
    if (another == "0") {
        throw DivisionByZeroException("Null division: [" + one + "/" + another + "]");
    }
    if (compare_as_numbers(one, another) == Comparator_result::LESS) {
        return "0";
    }

    std::string result;
    std::string current_number;
    while(!one.empty()) {
        if (current_number == "0") {
            current_number = std::string(1, one[0]);
        } else {
            current_number += std::string(1, one[0]);
        }
        one.erase(one.begin());
        auto [new_digit, calculated_number] = division_step(current_number, another);
        result += new_digit;
        current_number = minus(current_number, calculated_number);
    }
    return result;
}

void StringInt::remove_leading_zeros(std::string& number) {
    while (number.length() > 1 && number[0] == '0') {
        number.erase(number.begin());
    }
}
