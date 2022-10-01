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
#include <set>

#include "../exceptions/exceptions.h"
#include "../StringInt/StringInt.h"
#include "../Rational_number/Rational_number.h"
#include "../Complex_number/Complex_number.h"

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
     */
    Vector(): precision(0), dim(-1), mass_transform(0), data({}) {}

    /**
     * Constructor for almost any case.
     *
     * @param required_precision precision of contained elements, default is default_precision.
     * @param required_dim dimension of vector, default -1.
     * @param default_value value that should be set as default value for each element.
     */
    explicit Vector(
            StringInt required_dim = -1,
            double default_value = 0,
            double required_precision = default_precision
                    ): dim(std::move(required_dim)), mass_transform(default_value), precision(required_precision), data({}) { }

    /**
     * Constructor from file.
     *
     * @param file_path path to file to parse vector.
     * @param required_precision precision of contained elements, default is default_precision.
     * @param default_value value that should be set as default value for each element.
     */
    Vector(const char* file_path, TValue required_precision = default_precision, TValue default_value = 0):
            mass_transform(default_value), precision(required_precision) {
        std::ifstream infile(file_path);
        if (infile.bad()) {
            throw FileNotFoundException(file_path);
        }
        //todo: implement
    }

    /**
     * Copy constructor.
     *
     * @param rhs instance to copy.
     */
    Vector(const Vector& rhs): dim(rhs.dim), mass_transform(rhs.mass_transform), precision(rhs.precision), data(rhs.data) { }

    /**
     * Move constructor.
     *
     * @param rhs instance to move.
     */
    Vector(Vector&& rhs) noexcept : dim(rhs.dim), mass_transform(rhs.mass_transform), precision(rhs.precision), data(rhs.data) {
        rhs.dim = StringInt();
        rhs.mass_transform = TValue();
        rhs.precision = TValue();
        rhs.data = {};
    }

    /**
     * Copy operator.
     *
     * @param rhs instance to copy.
     * @return this Vector filled with rhs fields.
     */
    Vector& operator=(const Vector& rhs) {
        Vector tmp(rhs);
        std::swap(dim, tmp.dim);
        std::swap(mass_transform, tmp.mass_transform);
        std::swap(precision, tmp.precision);
        std::swap(data, tmp.data);
        return *this;
    }

    /**
     * Move operator.
     *
     * @param rhs instance to move.
     * @return this Vector filled with rhs fields.
     */
    Vector& operator=(Vector&& rhs) noexcept {
        dim = std::move(rhs.dim);
        rhs.dim = StringInt();
        mass_transform = std::move(rhs.mass_transform);
        rhs.mass_transform = TValue();
        precision = std::move(rhs.precision);
        rhs.precision = TValue();
        data = std::move(rhs.data);
        rhs.data = {};
        return *this;
    }

    /**
     * Move data operator.
     *
     * @param rhs instance to copy.
     * @return this Vector with data filled with rhs.
     */
    Vector& operator=(std::map<StringInt, TValue>&& data_to_move) noexcept {
        data = std::move(data_to_move);
        data_to_move = {};
        return *this;
    }

    /**
     * precision setter.
     *
     * @param new_precision new double to be set as precision.
     */
    void set_precision(TValue new_precision) {
        precision = new_precision;
        delete_zero_elements();
    }

    /**
     * precision getter.
     *
     * @return current precision.
     */
    TValue get_precision() {
        return precision;
    }

    /**
     * Get number of not-null elements.
     *
     * @return number of not-null elements.
     */
    StringInt get_size() {
        delete_zero_elements();
        return StringInt(data.size());
    }

    /**
     * Get dimension of this Vector.
     *
     * @return dimension of this Vector.
     */
    StringInt get_dim() {
        return dim;
    }

    /**
     * Friend operator that prints Vector to std::ostream.
     *
     * @param os output stream.
     * @param x Vector to print.
     * @return os.
     */
    friend std::ostream& operator<<(std::ostream& os, Vector const& x) {
        os << to_string(x);
        return os;
    }

    /**
     * Friend operator that reads Vector from std::istream.
     *
     * @param is input stream.
     * @param x Vector to read to.
     * @return is.
     */
    friend std::istream& operator>>(std::istream& is, Vector<TValue>& x);

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
    Vector operator-() {
        delete_zero_elements();
        Vector<TValue> result(*this);
        for(auto& [key, value]: result.data) {
            value = -value;
        }
        mass_transform = -mass_transform;
        return result;
    }

    /**
     * Access operator.
     *
     * @param index index of required element.
     * @return element of this Vector on position index.
     */
    TValue& operator()(const StringInt& index) {
        delete_zero_elements();
        if (dim >= 0) {
            if (index >= dim) {
                throw OutOfRangeException("OutOfRangeException");
            }
        }
        if (data.find(index) == data.end()) {
            data[index] = mass_transform;
        }
        if (data[index] <= TValue(precision)) {
            data[index] = 0;
        }
        return data[index];
    }

    /**
     * Plus and assign operator.
     *
     * @tparam TValueRight type of data of right operand.
     * @param rhs right operand.
     * @return this Vector, increased by rhs.
     */
    template<typename TValueRight>
    auto& operator+=(const Vector<TValueRight> &rhs) {
        mass_transform += rhs.mass_transform;
        for (auto [key, value] : rhs.data) {
            if (data.find(key) == data.end()) {
                data[key] = mass_transform + value;
            } else {
                data[key] += value;
            }
        }
        delete_zero_elements();
        return *this;
    }

    /**
     * Minus and assign operator.
     *
     * @tparam TValueRight type of data of right operand.
     * @param rhs right operand.
     * @return this Vector, decreased by rhs.
     */
    template<typename TValueRight>
    auto& operator-=(const Vector<TValueRight> &rhs) {
        mass_transform -= rhs.mass_transform;
        for (auto [key, value] : rhs.data) {
            if (data.find(key) == data.end()) {
                data[key] = mass_transform - value;
            } else {
                data[key] -= value;
            }
        }
        delete_zero_elements();
        return *this;
    }

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
    friend std::string to_string(Vector vector) {
        std::stringstream ss;
        std::string type_name;
        ss << "vector " << get_type_name(TValue()) << " " << vector.dim << std::endl << std::endl;
        for (auto [key, value]: vector.data) {
            ss << (key + 1) << "\t" <<  value << std::endl;
        }
        return ss.str();
    }

private:
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
     * Precision of elements in this Vector.
     * If a number is less then precision, value is considered to be zero.
     */
    TValue precision;

    /**
     * Data stored as ordered map.
     *
     * key - StringInt describing index of a number.
     * value - TValue that should be stored.
     */
    std::map<StringInt, TValue> data;

    /**
     * Constant that defines default precision.
     */
    static constexpr double default_precision = 0.0000000001;

    template<typename TComplexReal = double, typename TComplexImaginary = double>
    static std::string get_type_name(TValue type) {
        std::string type_name;
        if (typeid(type) == typeid(Rational_number)) {
            type_name = "rational";
        } else if (typeid(type) == typeid(bool)) {
            type_name = "bit";
        } else if (typeid(type) == typeid(Complex_number<TComplexReal, TComplexImaginary>)) {
            type_name = "complex";
        } else {
            type_name = "<" + std::string(typeid(TValue).name()) + ">";
        }
        return type_name;
    }

    /**
     * Internal method to delete elements from [data] that are less than [precision].
     */
    void delete_zero_elements() {
        std::set<StringInt> to_delete;
        if (mass_transform <= TValue(precision)) {
            mass_transform = 0;
        }
        for (auto [key, value] : data) {
            if (value <= TValue(precision)) {
                to_delete.insert(key);
            }
        }
        for (auto key : to_delete) {
            data.erase(key);
        }
    }
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
public:
    /**
     * Default constructor
     */
    Vector(): data(0u) { }

    /**
     * Constructor that allows to set default value to data.
     *
     * @param is_zeroes flag to set default value for each element of Vector.
     */
    explicit Vector(bool is_zeroes): data(is_zeroes ? 0 : -1) { }

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
    [[nodiscard]] int get_size() const {
        int result = 0;
        uint64_t tmp = data;
        while (tmp) {
            result += int(tmp & 1u);
            tmp >>= 1;
        }
        return result;
    }

    /**
     * Friend operator that prints Vector to std::ostream.
     *
     * @param os output stream.
     * @param x Vector to print.
     * @return os.
     */
    friend std::ostream& operator<<(std::ostream& os, Vector<bool> const& x);

    /**
     * Friend operator that reads Vector from std::istream.
     *
     * @param is input stream.
     * @param x Vector to read to.
     * @return is.
     */
    friend std::istream& operator>>(std::istream& is, Vector<bool>& x);

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
    Vector<bool> operator~() {
        Vector<bool> result = *this;
        result.data ^= -1;
        return result;
    }

    /**
     * Element getter.
     *
     * @param index index of element.
     * @return value of element on position [index].
     */
    bool operator()(int index) const {
        if (index >= max_index) {
            throw OutOfRangeException("Index " + std::to_string(index) + " is out of range, ["
                                      + std::to_string(max_index) + "] is maximal possible index.");
        }
        return (data & (1 << index)) >> index;
    }

    /**
     * Element setter
     *
     * @param index index of element.
     * @param value value to be set.
     * @return value of element on position [index].
     */
    bool operator()(int index, bool value) {
        if (index >= max_index) {
            throw OutOfRangeException("Index " + std::to_string(index) + " is out of range ("
                                      + std::to_string(max_index) + " is maximum possible index).");
        }
        data ^= 1 << index;
        return value;
    }

    /**
     * Plus and assign operator - OR.
     *
     * @param rhs right operand.
     * @return this Vector OR [rhs].
     */
    Vector<bool>& operator+=(const Vector<bool> &rhs) {
        data |= rhs.data;
        return *this;
    }

    /**
     * Multiply and assign operator - AND.
     *
     * @param rhs right operand.
     * @return this Vector AND [rhs].
     */
    Vector<bool>& operator*=(const Vector<bool> &rhs) {
        data &= rhs.data;
        return *this;
    }

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
