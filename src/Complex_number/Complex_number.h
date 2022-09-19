/**
 * Header containing Complex_number class declaration.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_COMPLEX_NUMBER_H
#define COUNTING_STARS_COMPLEX_NUMBER_H

#include <string>
#include <iostream>
#include "../exceptions/exceptions.h"

template<typename TReal, typename TImaginary>
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
    Complex_number(const TReal& real): re(real), im(0.0) { }

    /**
     * Constructor from real and imaginary parts of complex number.
     *
     * @param real number of type TReal that will be used as real part of this Complex_number.
     * @param imaginary number of type TImaginary that will be used as imaginary part of this Complex_number.
     */
    Complex_number(const TReal& real, const TImaginary& imaginary): re(real), im(imaginary) { }

    /**
     * Copy operator.
     *
     * @tparam TRealRight type of real part of right operand.
     * @tparam TImaginaryRight type of imaginary part of right operand.
     * @param rhs right operand.
     * @return this Complex_number set with rhs.
     */
    template <typename TRealRight, typename TImaginaryRight>
    Complex_number& operator=(Complex_number<TRealRight, TImaginaryRight> &rhs);

    /**
     * re setter.
     *
     * @tparam TRealRight type of new real part of complex number.
     * @param new_re number of type TRealRight that will be set as new re.
     */
    template<typename TRealRight>
    void set_re(TRealRight new_re);

    /**
     * re setter.
     *
     * @tparam TImaginaryRight type of new imaginary part of complex number.
     * @param new_im number of type TImaginaryRight that will be set as new im.
     */
    template<typename TImaginaryRight>
    void set_im(TImaginaryRight new_im);

    /**
     * re getter.
     *
     * @return real part of this Complex_number.
     */
    TReal get_re() const;

    /**
     * im getter.
     *
     * @return imaginary part of this Complex_number.
     */
    TImaginary get_im() const;

    /**
     * Friend operator that prints Complex_number to std::ostream.
     *
     * @param os output stream.
     * @param x Complex_number to print.
     * @return os.
     */
    friend std::ostream& operator<< (std::ostream& os, Complex_number const& x);

    /**
     * Friend operator that reads Complex_number from std::istream.
     *
     * @param is input stream.
     * @param x Complex_number to read to.
     * @return is.
     */
    friend std::istream& operator>> (std::istream& is, Complex_number& x);

    /**
     * Eq operator.
     *
     * @tparam TRealLeft type of real part of left operand.
     * @tparam TImaginaryLeft type of imaginary part of left operand.
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
     * @tparam TRealLeft type of real part of left operand.
     * @tparam TImaginaryLeft type of imaginary part of left operand.
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
     * @tparam TRealLeft type of real part of left operand.
     * @tparam TImaginaryLeft type of imaginary part of left operand.
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
     * @tparam TRealLeft type of real part of left operand.
     * @tparam TImaginaryLeft type of imaginary part of left operand.
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
     * @tparam TRealLeft type of real part of left operand.
     * @tparam TImaginaryLeft type of imaginary part of left operand.
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
     * @tparam TRealLeft type of real part of left operand.
     * @tparam TImaginaryLeft type of imaginary part of left operand.
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
    auto& operator+= (const Complex_number<TRealRight, TImaginaryRight> &rhs);

    /**
     * Minus and assign operator.
     *
     * @tparam TRealRight type of real part of right operand.
     * @tparam TImaginaryRight type of imaginary part of right operand.
     * @param rhs right operand.
     * @return this Complex_number decreased by rhs.
     */
    template <typename TRealRight, typename TImaginaryRight>
    auto& operator-= (const Complex_number<TRealRight, TImaginaryRight> &rhs);

    /**
     * Multiply and assign operator.
     *
     * @tparam TRealRight type of real part of right operand.
     * @tparam TImaginaryRight type of imaginary part of right operand.
     * @param rhs right operand.
     * @return this Complex_number multiplied by rhs.
     */
    template <typename TRealRight, typename TImaginaryRight>
    auto& operator*= (const Complex_number<TRealRight, TImaginaryRight> &rhs);

    /**
     * Divide and assign operator.
     *
     * @tparam TRealRight type of real part of right operand.
     * @tparam TImaginaryRight type of imaginary part of right operand.
     * @param rhs right operand.
     * @return this Complex_number divided by rhs.
     */
    template <typename TRealRight, typename TImaginaryRight>
    auto & operator/= (const Complex_number<TRealRight, TImaginaryRight> &rhs);

    /**
     * Get conjugated complex number of this Complex_number.
     *
     * @return Conjugated number of this Complex_number.
     */
    Complex_number operator~() const;

    /**
     * std::string cast operator.
     *
     * @return string representation of this Complex_number.
     */
    explicit operator std::string() const;

    /**
     * Get modulus of this Complex_number.
     *
     * @return modulus of this Complex_number.
     */
    auto modulus() const;

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
auto operator+(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs);

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
auto operator-(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs);

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
auto operator*(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs);

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
auto operator/(Complex_number<TRealLeft, TImaginaryLeft> lhs, const Complex_number<TRealRight, TImaginaryRight> &rhs);

#endif //COUNTING_STARS_COMPLEX_NUMBER_H
