//
// Created by sanyavertolet on 06.09.2022.
//

#ifndef COUNTING_STARS_RATIONAL_NUMBER_H
#define COUNTING_STARS_RATIONAL_NUMBER_H

#include <string>
#include <cmath>

class Rational_number {
public:
    char sign;
    std::string numerator;
    std::string denominator;

    explicit Rational_number(char, std::string, std::string);
    explicit Rational_number(int);
    explicit Rational_number(signed, unsigned);
    explicit Rational_number(std::string);

    Rational_number operator-() const;
    Rational_number& operator++();
    Rational_number& operator--();
    //NOLINTNEXTLINE
    Rational_number operator++(int);
    //NOLINTNEXTLINE
    Rational_number operator--(int);

    Rational_number operator+(const Rational_number &) const;
    Rational_number operator-(const Rational_number &) const;
    Rational_number operator*(const Rational_number &) const;
    Rational_number operator/(const Rational_number &) const;

    Rational_number operator+=(Rational_number);
    Rational_number operator-=(Rational_number);
    Rational_number operator*=(const Rational_number&);
    Rational_number operator/=(Rational_number);

    Rational_number operator==(Rational_number);
    Rational_number operator!=(Rational_number);
    Rational_number operator<=(Rational_number);
    Rational_number operator>=(Rational_number);
    Rational_number operator<(Rational_number);
    Rational_number operator>(Rational_number);

//    friend Rational_number operator+(Rational_number, Rational_number);
//    friend Rational_number operator-(Rational_number, Rational_number);
//    friend Rational_number operator*(Rational_number, Rational_number);
//    friend Rational_number operator/(Rational_number, Rational_number);

    Rational_number make_canonical();
    Rational_number simplify() const;

    Rational_number& simplify();

    explicit operator std::string() const;

    void remove_leading_zeros();

    static Rational_number null() {
        return Rational_number('+', "0", "1");
    }

private:
    void validate();
};

std::string to_string(Rational_number&);

#endif //COUNTING_STARS_RATIONAL_NUMBER_H
