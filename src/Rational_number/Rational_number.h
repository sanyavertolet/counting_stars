//
// Created by sanyavertolet on 06.09.2022.
//

#ifndef COUNTING_STARS_RATIONAL_NUMBER_H
#define COUNTING_STARS_RATIONAL_NUMBER_H

#include <string>
#include <cmath>

#include "../StringInt/StringInt.h"

class Rational_number {
public:
    Rational_number(StringInt, StringInt);
    Rational_number(const signed&); // NOLINT(google-explicit-constructor)
    Rational_number(const signed&, const unsigned&);
    Rational_number(const signed long long&); // NOLINT(google-explicit-constructor)
    Rational_number(const signed long long&, const unsigned long long&);
    Rational_number(std::string); // NOLINT(google-explicit-constructor)

    void set_numerator(const StringInt&);
    void set_denominator(const StringInt&);

    StringInt get_numerator();
    StringInt get_denominator();

    Rational_number operator-() const;
    Rational_number& operator++();
    Rational_number& operator--();
    Rational_number operator++(int); // NOLINT(cert-dcl21-cpp)
    Rational_number operator--(int); // NOLINT(cert-dcl21-cpp)

    friend std::ostream& operator<< (std::ostream& os, Rational_number const& x);
    friend std::istream& operator>> (std::istream& is, Rational_number& x);

    friend inline bool operator<(const Rational_number&, const Rational_number&);
    friend inline bool operator>(const Rational_number&, const Rational_number&);
    friend inline bool operator==(const Rational_number&, const Rational_number&);
    friend inline bool operator!=(const Rational_number&, const Rational_number&);
    friend inline bool operator<=(const Rational_number&, const Rational_number&);
    friend inline bool operator>=(const Rational_number&, const Rational_number&);

    Rational_number& operator+=(const Rational_number&);
    Rational_number& operator-=(const Rational_number&);
    Rational_number& operator*=(const Rational_number&);
    Rational_number& operator/=(const Rational_number&);

    bool operator!() const;
    explicit operator bool() const;
    explicit operator std::string() const;

    Rational_number& make_canonical();

private:
    StringInt numerator;
    StringInt denominator;
    void validate() const;
};

inline Rational_number operator+(Rational_number, const Rational_number&);
inline Rational_number operator-(Rational_number, const Rational_number&);
inline Rational_number operator*(Rational_number, const Rational_number&);
inline Rational_number operator/(Rational_number, const Rational_number&);

#endif //COUNTING_STARS_RATIONAL_NUMBER_H
