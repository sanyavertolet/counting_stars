/**
 * Header containing Complex_number class declaration and implementation (partially).
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_COMPLEX_NUMBER_H
#define COUNTING_STARS_COMPLEX_NUMBER_H

#include <string>
#include <iostream>
#include "../exceptions/exceptions.h"

/**
 * Template class that implements Complex_number.
 *
 * @tparam TReal real part type, which is double by default.
 * @tparam TImaginary imaginary part type, which is double by default.
 */
template<typename TReal = double, typename TImaginary = double>
class Complex_number {
public:
    /**
     * Default constructor.
     */
    Complex_number(): re(0.0), im(0.0) { }

    /**
     * Constructor from real part of complex number (imaginary part will be set to 0.0).
     *
     * @param real number of type TReal that will be used as real part of this Complex_number.
     */
    explicit Complex_number(const TReal& real): re(real), im(0.0) { }

    /**
     * Constructor from real and imaginary parts of complex number.
     *
     * @param real number of type TReal that will be used as real part of this Complex_number.
     * @param imaginary number of type TImaginary that will be used as imaginary part of this Complex_number.
     */
    explicit Complex_number(const TReal& real, const TImaginary& imaginary): re(real), im(imaginary) { }

    /**
     * Copy operator.
     *
     * @tparam TRealRight type of real part of right operand.
     * @tparam TImaginaryRight type of imaginary part of right operand.
     * @param rhs right operand.
     * @return this Complex_number set with rhs.
     */
    template <typename TRealRight, typename TImaginaryRight>
    Complex_number& operator=(Complex_number<TRealRight, TImaginaryRight> &rhs) {
        this->set_re(rhs.get_re());
        this->set_im(rhs.get_im());
        return *this;
    }

    /**
     * re setter.
     *
     * @tparam TRealRight type of new real part of complex number.
     * @param new_re number of type TRealRight that will be set as new re.
     */
    template<typename TRealRight>
    void set_re(TRealRight new_re) {
        try {
            re = TReal(new_re);
        } catch(std::exception& exception) {
            throw CastException(exception.what());
        }
    }

    /**
     * im setter.
     *
     * @tparam TImaginaryRight type of new imaginary part of complex number.
     * @param new_im number of type TImaginaryRight that will be set as new im.
     */
    template<typename TImaginaryRight>
    void set_im(TImaginaryRight new_im) {
        try {
            im = TImaginary(new_im);
        } catch (std::exception& exception) {
            throw CastException(exception.what());
        }
    }

    /**
     * re getter.
     *
     * @return real part of this Complex_number.
     */
    TReal get_re() const {
        return re;
    }

    /**
     * im getter.
     *
     * @return imaginary part of this Complex_number.
     */
    TImaginary get_im() const {
        return im;
    }

    /**
     * Friend operator that prints Complex_number to std::ostream.
     *
     * @param os output stream.
     * @param x Complex_number to print.
     * @return os.
     */
    friend std::ostream& operator<<(std::ostream& os, Complex_number const& x) {
        os << std::string(x);
        return os;
    }

    /**
     * Friend operator that reads Complex_number from std::istream.
     *
     * @param is input stream.
     * @param x Complex_number to read to.
     * @return is.
     */
    friend std::istream& operator>>(std::istream& is, Complex_number& x) {
        char ch;
        std::string input;
        is.get(ch);
        if (ch != '(') {
            is.setstate(std::ios::failbit);
            throw ParseException("Error while parsing Complex_number: unknown symbol instead of '(': " + std::string(1, ch));
        }
        TReal new_re;
        is >> new_re;
        x.template set_re(new_re);

        is.get(ch);
        if (ch != ',') {
            is.setstate(std::ios::failbit);
            throw ParseException("Error while parsing Complex_number: unknown symbol instead of ',': " + std::string(1, ch));
        }

        TImaginary new_im;
        is >> new_im;
        x.template set_im(new_im);

        is.get(ch);
        if (ch != ')') {
            is.setstate(std::ios::failbit);
            throw ParseException("Error while parsing Complex_number: unknown symbol instead of ')': " + std::string(1, ch));
        }

        return is;
    }

    /**
     * Eq operator.
     *
     * @tparam TRealRight type of real part of right operand.
     * @tparam TImaginaryRight type of imaginary part of right operand.
     * @param lhs left operand.
     * @param rhs right operand.
     * @return true if radius vectors of lhs and rhs are equal, false otherwise.
     */
    template <typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
    friend bool operator==(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs);

    /**
     * Neq operator.
     *
     * @tparam TRealRight type of real part of right operand.
     * @tparam TImaginaryRight type of imaginary part of right operand.
     * @param lhs left operand.
     * @param rhs right operand.
     * @return true if radius vectors of lhs and rhs are not equal, false otherwise.
     */
    template <typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
    friend bool operator!=(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs);

    /**
     * Less operator.
     *
     * @tparam TRealRight type of real part of right operand.
     * @tparam TImaginaryRight type of imaginary part of right operand.
     * @param lhs left operand.
     * @param rhs right operand.
     * @return true if radius vector of lhs is less than radius vector of rhs, false otherwise.
     */
    template <typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
    friend bool operator<(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs);

    /**
     * Greater operator.
     *
     * @tparam TRealRight type of real part of right operand.
     * @tparam TImaginaryRight type of imaginary part of right operand.
     * @param lhs left operand.
     * @param rhs right operand.
     * @return true if radius vector of lhs is greater than radius vector of rhs, false otherwise.
     */
    template <typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
    friend bool operator>(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs);

    /**
     * Leq operator.
     *
     * @tparam TRealRight type of real part of right operand.
     * @tparam TImaginaryRight type of imaginary part of right operand.
     * @param lhs left operand.
     * @param rhs right operand.
     * @return true if radius vector of lhs is less or equal than radius vector of rhs, false otherwise.
     */
    template <typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
    friend bool operator<=(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs);

    /**
     * Geq operator.
     *
     * @tparam TRealRight type of real part of right operand.
     * @tparam TImaginaryRight type of imaginary part of right operand.
     * @param lhs left operand.
     * @param rhs right operand.
     * @return true if radius vector of lhs is greater or equal than radius vector of rhs, false otherwise.
     */
    template <typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
    friend bool operator>=(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs);

    /**
     * Plus and assign operator.
     *
     * @tparam TRealRight type of real part of right operand.
     * @tparam TImaginaryRight type of imaginary part of right operand.
     * @param rhs right operand.
     * @return this Complex_number increased by rhs.
     */
    template <typename TRealRight, typename TImaginaryRight>
    auto& operator+=(const Complex_number<TRealRight, TImaginaryRight> &rhs) {
        set_re(decltype(get_re() + rhs.get_re())(get_re() + rhs.get_re()));
        set_im(decltype(get_im() + rhs.get_im())(get_im() + rhs.get_im()));
        return *this;
    }

    /**
     * Minus and assign operator.
     *
     * @tparam TRealRight type of real part of right operand.
     * @tparam TImaginaryRight type of imaginary part of right operand.
     * @param rhs right operand.
     * @return this Complex_number decreased by rhs.
     */
    template <typename TRealRight, typename TImaginaryRight>
    auto& operator-=(const Complex_number<TRealRight, TImaginaryRight> &rhs) {
        set_re(get_re() - rhs.get_re());
        set_im(get_im() - rhs.get_im());
        return *this;
    }

    /**
     * Multiply and assign operator.
     *
     * @tparam TRealRight type of real part of right operand.
     * @tparam TImaginaryRight type of imaginary part of right operand.
     * @param rhs right operand.
     * @return this Complex_number multiplied by rhs.
     */
    template <typename TRealRight, typename TImaginaryRight>
    auto& operator*=(const Complex_number<TRealRight, TImaginaryRight> &rhs) {
        set_re(get_re() * rhs.get_re() - get_im() * rhs.get_im());
        set_im(get_re() * rhs.get_im() + get_im() * rhs.get_re());
        return *this;
    }

    /**
     * Divide and assign operator.
     *
     * @tparam TRealRight type of real part of right operand.
     * @tparam TImaginaryRight type of imaginary part of right operand.
     * @param rhs right operand.
     * @return this Complex_number divided by rhs.
     */
    template <typename TRealRight, typename TImaginaryRight>
    auto & operator/=(const Complex_number<TRealRight, TImaginaryRight> &rhs) {
        set_re(TReal((get_re() * rhs.get_re() + get_im() * rhs.get_im())/(rhs.get_re() * rhs.get_re() - rhs.get_im() * rhs.get_im())));
        set_im(TImaginary((get_im() * rhs.get_re() - get_re() * rhs.get_im())/(rhs.get_re() * rhs.get_re() - rhs.get_im() * rhs.get_im())));
        return *this;
    }

    /**
     * Get conjugated complex number of this Complex_number.
     *
     * @return Conjugated number of this Complex_number.
     */
    Complex_number operator~() const {
        Complex_number<TReal, TImaginary> result(*this);
        result.template set_im(result.get_im());
        return result;
    }

    /**
     * std::string cast operator.
     *
     * @return string representation of this Complex_number.
     */
    explicit operator std::string() const {
        return "(" + std::string(re) + ", " + std::string(im) + ")";
    }

    /**
     * Get modulus of this Complex_number.
     *
     * @return modulus of this Complex_number.
     */
    auto modulus() const {
        return re * re + im * im;
    }

private:
    /**
     * Real part of complex number.
     */
    TReal re;

    /**
     * Imaginary part of complex number.
     */
    TImaginary im;
};

/**
 * Plus operator.
 *
 * @tparam TRealLeft type of real part of left operand.
 * @tparam TImaginaryLeft type of imaginary part of left operand.
 * @tparam TRealRight type of real part of right operand.
 * @tparam TImaginaryRight type of imaginary part of right operand.
 * @param lhs left operand.
 * @param rhs right operand.
 * @return sum of lhs and rhs.
 */
template <typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
auto operator+(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs) {
    auto new_re = lhs.get_re() + rhs.get_re();
    auto new_im = lhs.get_im() + rhs.get_im();
    return Complex_number<decltype(new_re), decltype(new_im)>(new_re, new_im);
}

/**
 * Minus operator.
 *
 * @tparam TRealLeft type of real part of left operand.
 * @tparam TImaginaryLeft type of imaginary part of left operand.
 * @tparam TRealRight type of real part of right operand.
 * @tparam TImaginaryRight type of imaginary part of right operand.
 * @param lhs left operand.
 * @param rhs right operand.
 * @return lhs decreased by rhs.
 */
template <typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
auto operator-(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs) {
    auto new_re = lhs.get_re() - rhs.get_re();
    auto new_im = lhs.get_im() - rhs.get_im();
    return Complex_number<decltype(new_re), decltype(new_im)>(new_re, new_im);
}

/**
 * Multiply operator.
 *
 * @tparam TRealLeft type of real part of left operand.
 * @tparam TImaginaryLeft type of imaginary part of left operand.
 * @tparam TRealRight type of real part of right operand.
 * @tparam TImaginaryRight type of imaginary part of right operand.
 * @param lhs left operand.
 * @param rhs right operand.
 * @return product of lhs and rhs.
 */
template <typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
auto operator*(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs) {
    auto new_re = lhs.get_re() * rhs.get_re() - lhs.get_im() * rhs.get_im();
    auto new_im = lhs.get_re() * rhs.get_im() + lhs.get_im() * rhs.get_re();
    return Complex_number<decltype(new_re), decltype(new_im)>(new_re, new_im);
}

/**
 * Divide operator.
 *
 * @tparam TRealLeft type of real part of left operand.
 * @tparam TImaginaryLeft type of imaginary part of left operand.
 * @tparam TRealRight type of real part of right operand.
 * @tparam TImaginaryRight type of imaginary part of right operand.
 * @param lhs left operand.
 * @param rhs right operand.
 * @return lhs divided by rhs.
 */
template <typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
auto operator/(Complex_number<TRealLeft, TImaginaryLeft> lhs,const Complex_number<TRealRight, TImaginaryRight> &rhs) {
    auto new_re = (lhs.get_re() * rhs.get_re() + lhs.get_im() * rhs.get_im())/(rhs.get_re() * rhs.get_re() + rhs.get_im() * rhs.get_im());
    auto new_im = (lhs.get_im() * rhs.get_re() - lhs.get_re() * rhs.get_im())/(rhs.get_re() * rhs.get_re() + rhs.get_im() * rhs.get_im());
    return Complex_number<decltype(new_re), decltype(new_im)>(new_re, new_im);
}

template<typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
bool operator==(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs) {
    auto left_casted_modulus = lhs.modulus();
    auto right_casted_modulus = rhs.modulus();
    return decltype(left_casted_modulus + right_casted_modulus)(left_casted_modulus) == decltype(left_casted_modulus + right_casted_modulus)(right_casted_modulus);
}

template<typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
bool operator!=(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs) {
    return !(lhs == rhs);
}

template<typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
bool operator<(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs) {
    auto left_casted_modulus = lhs.modulus();
    auto right_casted_modulus = rhs.modulus();
    return decltype(left_casted_modulus + right_casted_modulus)(left_casted_modulus) < decltype(left_casted_modulus + right_casted_modulus)(right_casted_modulus);
}

template<typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
bool operator>(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs) {
    return rhs < lhs;
}

template<typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
bool operator<=(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs) {
    return !(lhs > rhs);
}

template<typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
bool operator>=(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs) {
    return !(lhs < rhs);
}

/**
 *
 * @tparam TRealLeft type of real part of a Complex_number.
 * @tparam TImaginaryLeft type of imaginary part of a Complex_number.
 * @param number
 * @return modulus of a number.
 */
template<typename TReal, typename TImaginary>
auto abs(Complex_number<TReal, TImaginary> number) {
    return number.modulus();
}

#endif //COUNTING_STARS_COMPLEX_NUMBER_H
