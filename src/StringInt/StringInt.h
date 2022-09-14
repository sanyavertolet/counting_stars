//
// Created by sanyavertolet on 09.09.2022.
//

#ifndef COUNTING_STARS_STRINGINT_H
#define COUNTING_STARS_STRINGINT_H

#include <string>
#include <map>
#include <iostream>

class StringInt {
public:
    StringInt();
    StringInt(char sign, std::string);
    StringInt(const std::string&); // NOLINT(google-explicit-constructor)
    StringInt(const int&); // NOLINT(google-explicit-constructor)
    StringInt(const unsigned&); // NOLINT(google-explicit-constructor)
    StringInt(const long long&); // NOLINT(google-explicit-constructor)
    StringInt(const unsigned long long&); // NOLINT(google-explicit-constructor)

    void set_sign(char);
    void set_val(const std::string&);

    [[nodiscard]] char get_sign() const;
    [[nodiscard]] std::string get_val() const;

    StringInt operator-() const;
    StringInt& operator++();
    StringInt& operator--();
    StringInt operator++(int); // NOLINT(cert-dcl21-cpp)
    StringInt operator--(int); // NOLINT(cert-dcl21-cpp)

    friend std::ostream& operator<< (std::ostream& os, StringInt const& x);
    friend std::istream& operator>> (std::istream& is, StringInt& x);

    friend bool operator==(const StringInt& lhs, const StringInt& rhs);
    friend bool operator!=(const StringInt& lhs, const StringInt& rhs);
    friend bool operator<(const StringInt& lhs, const StringInt& rhs);
    friend bool operator>(const StringInt& lhs, const StringInt& rhs);
    friend bool operator<=(const StringInt& lhs, const StringInt& rhs);
    friend bool operator>=(const StringInt& lhs, const StringInt& rhs);

    StringInt& operator+=(const StringInt&);
    StringInt& operator-=(const StringInt&);
    StringInt& operator*=(const StringInt&);
    StringInt& operator/=(const StringInt&);

    bool operator!() const;
    explicit operator bool() const;
    explicit operator std::string() const;

    friend StringInt gcd(StringInt, StringInt);

private:
    char sign;
    std::string val;
    enum class Comparator_result {
        LESS = -1,
        EQUAL = 0,
        GREATER = 1,
    };
    static Comparator_result compare_as_numbers(const std::string&, const std::string&);
    void remove_leading_zeros();
    static char plus(char, char, int&);
    static char minus(char, char, int&);
    static char multiply(char, char, int&);
    static std::string multiply(std::string number, char multiplier);
    static std::string plus(const std::string&, const std::string&);
    static std::string minus(std::string, std::string);
    static std::string multiply(std::string one, const std::string &another);
    static std::pair<std::string, std::string> division_step(const std::string& current_number, const std::string& divisor);
    static std::string divide_as_integers(std::string one, const std::string& another);
};

StringInt abs(StringInt);
StringInt gcd(StringInt, StringInt);

StringInt operator+(StringInt lhs, const StringInt&);
StringInt operator-(StringInt lhs, const StringInt&);
StringInt operator*(StringInt lhs, const StringInt&);
StringInt operator/(StringInt lhs, const StringInt&);


#endif //COUNTING_STARS_STRINGINT_H
