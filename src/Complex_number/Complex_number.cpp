/**
 * File containing Complex_number class implementation.
 *
 * @author sanyavertolet
 */

#include "Complex_number.h"

template<typename TReal, typename TImaginary>
template<typename TRealRight, typename TImaginaryRight>
Complex_number<TReal, TImaginary> &Complex_number<TReal, TImaginary>::operator=(Complex_number<TRealRight, TImaginaryRight> &rhs) {
    this->set_re(rhs.re);
    this->set_im(rhs.im);
    return *this;
}

template<typename TReal, typename TImaginary>
template<typename TRealRight>
void Complex_number<TReal, TImaginary>::set_re(TRealRight new_re) {
    try {
        re = new_re;
    } catch(std::exception& exception) {
        throw CastException(exception.what());
    }
}

template<typename TReal, typename TImaginary>
template<typename TImaginaryRight>
void Complex_number<TReal, TImaginary>::set_im(TImaginaryRight new_im) {
    try {
        im = new_im;
    } catch (std::exception& exception) {
        throw CastException(exception.what());
    }
}

template <typename TReal, typename TImaginary>
TReal Complex_number<TReal, TImaginary>::get_re() const {
    return re;
}

template <typename TReal, typename TImaginary>
TImaginary Complex_number<TReal, TImaginary>::get_im() const {
    return im;
}

template <typename TReal, typename TImaginary>
std::ostream& operator<< (std::ostream& os, Complex_number<TReal, TImaginary> const& x) {
    os << std::string(x);
    return os;
}

template <typename TReal, typename TImaginary>
std::istream& operator>> (std::istream& is, Complex_number<TReal, TImaginary>& x) {
    char ch;
    std::string input;
    is.get(ch);
    if (ch != '(') {
        throw ParseException("Error while parsing Complex_number: unknown symbol instead of '(': " + std::string(1, ch));
    }
    TReal new_re;
    is >> new_re;
    x.template set_re(new_re);

    is.get(ch);
    if (ch != ',') {
        throw ParseException("Error while parsing Complex_number: unknown symbol instead of ',': " + std::string(1, ch));
    }

    TImaginary new_im;
    is >> new_im;
    x.template set_im(new_im);

    is.get(ch);
    if (ch != ')') {
        throw ParseException("Error while parsing Complex_number: unknown symbol instead of ')': " + std::string(1, ch));
    }

    return is;
}

template <typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
bool operator==(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs) {
    auto left_casted_modulus = lhs.modulus();
    auto right_casted_modulus = rhs.modulus();
    return decltype(left_casted_modulus + right_casted_modulus)(left_casted_modulus) == decltype(left_casted_modulus + right_casted_modulus)(right_casted_modulus);
}

template <typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
bool operator!=(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs) {
    return !(lhs == rhs);
}

template <typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
bool operator<(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs) {
    auto left_casted_modulus = lhs.modulus();
    auto right_casted_modulus = rhs.modulus();
    return decltype(left_casted_modulus + right_casted_modulus)(left_casted_modulus) < decltype(left_casted_modulus + right_casted_modulus)(right_casted_modulus);
}

template <typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
bool operator>(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs) {
    return rhs < lhs;
}

template <typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
bool operator<=(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs) {
    return !(lhs > rhs);
}

template <typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
bool operator>=(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs) {
    return !(lhs < rhs);
}

template <typename TReal, typename TImaginary>
Complex_number<TReal, TImaginary>::operator std::string() const {
    return "(" + std::string(re) + ", " + std::string(im) + ")";
}

template <typename TReal, typename TImaginary>
auto Complex_number<TReal, TImaginary>::modulus() const {
    return re * re + im * im;
}

template <typename TReal, typename TImaginary>
template <typename TRealRight, typename TImaginaryRight>
auto& Complex_number<TReal, TImaginary>::operator+=(const Complex_number<TRealRight, TImaginaryRight> &rhs) {
    set_re(decltype(get_re() + rhs.get_re())(get_re() + rhs.get_re()));
    set_im(decltype(get_im() + rhs.get_im())(get_im() + rhs.get_im()));
    return *this;
}

template <typename TReal, typename TImaginary>
template <typename TRealRight, typename TImaginaryRight>
auto& Complex_number<TReal, TImaginary>::operator-=(const Complex_number<TRealRight, TImaginaryRight> &rhs) {
    set_re(get_re() - rhs.get_re());
    set_im(get_im() - rhs.get_im());
    return *this;
}

template <typename TReal, typename TImaginary>
template <typename TRealRight, typename TImaginaryRight>
auto& Complex_number<TReal, TImaginary>::operator*=(const Complex_number<TRealRight, TImaginaryRight> &rhs) {
    set_re(get_re() * rhs.get_re() - get_im() * rhs.get_im());
    set_im(get_re() * rhs.get_im() + get_im() * rhs.get_re());
    return *this;
}

template <typename TReal, typename TImaginary>
template <typename TRealRight, typename TImaginaryRight>
auto& Complex_number<TReal, TImaginary>::operator/=(const Complex_number<TRealRight, TImaginaryRight> &rhs) {
    set_re((get_re() * rhs.get_re() + get_im() * rhs.get_im())/(rhs.get_re() * rhs.get_re() - rhs.get_im() * rhs.get_im()));
    set_im((get_im() * rhs.get_re() - get_re() * rhs.get_im())/(rhs.get_re() * rhs.get_re() - rhs.get_im() * rhs.get_im()));
    return *this;
}

template <typename TReal, typename TImaginary>
Complex_number<TReal, TImaginary> Complex_number<TReal, TImaginary>::operator~() const {
    Complex_number<TReal, TImaginary> result(*this);
    result.template set_im(result.get_im());
    return result;
}

template <typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
auto operator+(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs) {
    return (lhs += rhs);
}

template <typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
auto operator-(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs) {
    return (lhs -= rhs);
}

template <typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
auto operator*(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs) {
    return (lhs *= rhs);
}

template <typename TRealLeft, typename TImaginaryLeft, typename TRealRight, typename TImaginaryRight>
auto operator/(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs) {
    return (lhs /= rhs);
}
