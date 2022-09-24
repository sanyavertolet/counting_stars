/**
 * Header containing Vector class declaration.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_VECTOR_H
#define COUNTING_STARS_VECTOR_H

#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>

#include "../exceptions/exceptions.h"
#include "../Complex_number/Complex_number.h"
#include "../StringInt/StringInt.h"
#include "../Rational_number/Rational_number.h"

/**
 * Template class that implements vector.
 *
 * If TValue is bool, data is stored as uint64_t value, otherwise it is stored as std::map<StringIng, TValue>.
 * If dim is negative, vector is considered to be endless, otherwise it has maximum of dim elements.
 *
 * @tparam TValue type of stored data.
 */
template<typename TValue>
class Vector {
public:
    /**
     * Default constructor.
     *
     * @param required_precision precision of contained elements, default is default_precision.
     * @param required_dim dimension of vector, default -1.
     * @param default_value value that should be set as default value for each element.
     */
    Vector(
            StringInt  required_dim = -1,
            double default_value = 0,
            double required_precision = default_precision
                    ): precision(required_precision), dim(std::move(required_dim)), mass_transform(default_value), data({}) { }

    /**
     * Constructor from file.
     *
     * @param file_path path to file to parse vector.
     * @param required_precision precision of contained elements, default is default_precision.
     * @param default_value value that should be set as default value for each element.
     */
    Vector(
            const char* file_path,
            double required_precision = default_precision,
            TValue default_value = 0
                    ): precision(required_precision) {
        std::ifstream infile(file_path);
        if (infile.bad()) {
//            throw FileNotFoundException();
            throw std::runtime_error("FileNotFoundException: " + std::string(file_path));
        }
        //todo: implement
    }

    /**
     * precision setter.
     *
     * @param new_precision new double to be set as precision.
     */
    void set_precision(double new_precision);

    /**
     * precision getter.
     *
     * @return current precision.
     */
    double get_precision();

    /**
     * Get number of not-null elements.
     *
     * @return number of not-null elements.
     */
    StringInt get_size();

    /**
     * Get dimension of this Vector.
     *
     * @return dimension of this Vector.
     */
    StringInt get_dim();

    /**
     * Friend operator that prints this Vector to std::ostream.
     *
     * @param os output stream.
     * @param x Vector to print.
     * @return os.
     */
    friend std::ostream& operator<< (std::ostream& os, Vector<TValue> const& x);

    /**
     * Friend operator that reads Vector from std::istream.
     *
     * @param is input stream.
     * @param x Vector to read to.
     * @return is.
     */
    friend std::istream& operator>> (std::istream& is, Vector<TValue>& x);

    /**
     * Eq operator.
     *
     * @tparam TValueLeft type of data of left operand.
     * @tparam TValueRight type of data of right operand.
     * @param lhs left operand.
     * @param rhs right operand.
     * @return true of lhs and rhs are equal, false otherwise.
     */
    template<typename TValueLeft, typename TValueRight>
    friend bool operator==(const Vector<TValueLeft> &lhs, const Vector<TValueRight> &rhs);

    /**
     * Neq operator.
     *
     * @tparam TValueLeft type of data of left operand.
     * @tparam TValueRight type of data of right operand.
     * @param lhs left operand.
     * @param rhs right operand.
     * @return true of lhs and rhs are not equal, false otherwise.
     */
    template<typename TValueLeft, typename TValueRight>
    friend bool operator!=(const Vector<TValueLeft> &lhs, const Vector<TValueRight> &rhs);

    /**
     * Unary minus operator.
     *
     * @return Vector with items with inverted signs.
     */
    Vector operator-();

    /**
     * Access operator.
     *
     * @param index index of required element.
     * @return element of this Vector on position index.
     */
    TValue& operator()(const StringInt& index);

    /**
     * Plus and assign operator.
     *
     * @tparam TValueRight type of data of right operand.
     * @param rhs right operand.
     * @return this Vector, increased by rhs.
     */
    template<typename TValueRight>
    auto& operator+=(const Vector<TValueRight> &rhs);

    /**
     * Minus and assign operator.
     *
     * @tparam TValueRight type of data of right operand.
     * @param rhs right operand.
     * @return this Vector, decreased by rhs.
     */
    template<typename TValueRight>
    auto& operator-=(const Vector<TValueRight> &rhs);

    /**
     * Plus operator.
     *
     * @tparam TValueLeft type of data of left operand.
     * @tparam TValueRight type of data of right operand.
     * @param lhs left operand.
     * @param rhs right operand.
     * @return sum of lhs and rhs.
     */
    template<typename TValueLeft, typename TValueRight>
    friend auto operator+(const Vector<TValueLeft> &lhs, const Vector<TValueRight> &rhs);

    /**
     * Minus operator.
     *
     * @tparam TValueLeft type of data of left operand.
     * @tparam TValueRight type of data of right operand.
     * @param lhs left operand.
     * @param rhs right operand.
     * @return lhs, decreased by rhs.
     */
    template<typename TValueLeft, typename TValueRight>
    friend auto operator-(const Vector<TValueLeft> &lhs, const Vector<TValueRight> &rhs);

    /**
     * Mass plus operator.
     *
     * @tparam TValueLeft type of data of left operand.
     * @tparam TValueRight type of rhs - primitive probably.
     * @param lhs left operand.
     * @param rhs right operand.
     * @return lhs where each element is increased by rhs.
     */
    template<typename TValueLeft, typename TValueRight>
    friend auto operator+(Vector<TValueLeft> lhs, const TValueRight& rhs);

    /**
     * Mass minus operator.
     *
     * @tparam TValueLeft type of data of left operand.
     * @tparam TValueRight type of rhs - primitive probably.
     * @param lhs left operand.
     * @param rhs right operand.
     * @return lhs where each element is decreased by rhs.
     */
    template<typename TValueLeft, typename TValueRight>
    friend auto operator-(Vector<TValueLeft> lhs, const TValueRight& rhs);

    /**
     * Mass multiply operator.
     *
     * @tparam TValueLeft type of data of left operand.
     * @tparam TValueRight type of rhs - primitive probably.
     * @param lhs left operand.
     * @param rhs right operand.
     * @return lhs where each element is multiplied by rhs.
     */
    template<typename TValueLeft, typename TValueRight>
    friend auto operator*(Vector<TValueLeft> lhs, const TValueRight& rhs);

    /**
     * Mass divide operator.
     *
     * @tparam TValueLeft type of data of left operand.
     * @tparam TValueRight type of rhs - primitive probably.
     * @param lhs left operand.
     * @param rhs right operand.
     * @return lhs where each element is divided by rhs.
     */
    template<typename TValueLeft, typename TValueRight>
    friend auto operator/(Vector<TValueLeft> lhs, const TValueRight& rhs);

    /**
     * std::to_string implementation for Vector.
     *
     * @param vector Vector to be converted to string.
     * @return std::string representation of vector.
     */
    friend std::string to_string(Vector<TValue> vector);

private:
    /**
     * Precision of elements in this Vector.
     * If a number is less then precision, value is considered to be zero.
     */
    double precision;

    /**
     * Number of maximum stored elements.
     * If dim is negative, Vector is considered to be endless.
     */
    StringInt dim;

    /**
     * Internal value to decrease memory usage.
     * If mass operation is applied to Vector, mass transform is changed in order not to store all [dim] elements.
     */
    TValue mass_transform;

    /**
     * Data is stored as ordered map.
     *
     * key is StringInt - index of a number
     * value - TValue that should be stored.
     */
    std::map<StringInt, TValue> data;

    /**
     * Constant that defines default precision.
     */
    static constexpr double default_precision = 0.0000000001;
};

/**
 * Method to create Vector from input file stream (std::ifstream).
 *
 * @tparam TValue type of data for Vector.
 * @param is input file stream (std::ifstream).
 * @return Vector from std::ifstream.
 */
template<typename TValue>
Vector<TValue> parse_from_ifstream(std::ifstream &is);

/**
 * Vector implementation for bool.
 * In this case dim is considered to be 64 and the data is stored as uint64_t.
 */
template<>
class Vector<bool> {
    /**
     * Default constructor
     *
     * @param is_zeroes flag to set default value for each element of Vector.
     */
    Vector(bool is_zeroes = true): data(is_zeroes ? 0 : -1) { }

    /**
     * Constructor from file.
     *
     * @param file_path name of a file to be parsed.
     */
    Vector(const char* file_path) {
        std::ifstream infile(file_path);
        if (infile.bad()) {
//            throw FileNotFoundException();
            throw std::runtime_error("FileNotFoundException: " + std::string(file_path));
        }
        data = 0u;
        //todo: implement
    }

    /**
     * Get number of true elements.
     *
     * @return number of true elements.
     */
    [[nodiscard]] int get_size() const;

    /**
     * Friend operator that prints this Vector to std::ostream.
     *
     * @param os output stream.
     * @param x Vector to print.
     * @return os.
     */
    friend std::ostream& operator<< (std::ostream& os, Vector<bool> const& x);

    /**
     * Friend operator that reads Vector from std::istream.
     *
     * @param is input stream.
     * @param x Vector to read to.
     * @return is.
     */
    friend std::istream& operator>> (std::istream& is, Vector<bool>& x);

    /**
     * Eq operator.
     *
     * @param lhs left operand.
     * @param rhs right operand.
     * @return true if lhs and rhs are equal, false otherwise.
     */
    friend bool operator==(const Vector<bool> &lhs, const Vector<bool> &rhs);

    /**
     * Neq operator.
     *
     * @param lhs left operand.
     * @param rhs right operand.
     * @return true if lhs and rhs are not equal, false otherwise.
     */
    friend bool operator!=(const Vector<bool> &lhs, const Vector<bool> &rhs);

    /**
     * @return Vector that contains negative elements - false to true and backwards.
     */
    Vector<bool> operator~();

    /**
     * Element getter.
     *
     * @param index index of element.
     * @return value of element on position [index].
     */
    bool operator()(int index) const;

    /**
     * Element setter
     *
     * @param index index of element.
     * @param value value to be set.
     * @return value of element on position [index].
     */
    bool operator()(int index, bool value);

    /**
     * Plus and assign operator - OR.
     *
     * @param rhs right operand.
     * @return this Vector OR [rhs].
     */
    Vector<bool>& operator+=(const Vector<bool> &rhs);

    /**
     * Multiply and assign operator - AND.
     *
     * @param rhs right operand.
     * @return this Vector AND [rhs].
     */
    Vector<bool>& operator*=(const Vector<bool> &rhs);

    /**
     * Plus operator - OR.
     *
     * @param lhs left operand.
     * @param rhs right operand.
     * @return [lhs] OR [rhs].
     */
    friend Vector<bool> operator+(const Vector<bool> &lhs, const Vector<bool> &rhs);

    /**
     * Multiply operator - AND.
     *
     * @param lhs left operand.
     * @param rhs right operand.
     * @return [lhs] AND [rhs].
     */
    friend Vector<bool> operator*(const Vector<bool> &lhs, const Vector<bool> &rhs);

    /**
     * std::to_string implementation for Vector
     *
     * @param vector vector to be converted to std::string.
     * @return std::string representation of [vector]
     */
    friend std::string to_string(Vector<bool> vector);

private:
    /**
     * Data is stored as uint64_t where i-th bit is 1 if i-th value is true and 0 if value is false.
     */
    uint64_t data;

    /**
     * Maximum possible Vector length.
     */
    static constexpr int max_index = 64;
};

#endif //COUNTING_STARS_VECTOR_H
