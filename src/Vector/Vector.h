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
#include <vector>
#include <set>

#include "../exceptions/exceptions.h"
#include "../StringInt/StringInt.h"
#include "../Rational_number/Rational_number.h"
#include "../Complex_number/Complex_number.h"

#include "../Matrix/Matrix_proxy.h"

/**
 * Template class that implements vector.
 *
 * If TValue is bool, data is stored as uint64_t value, otherwise it is stored as std::map<StringIng, TValue>.
 * If capacity is negative, vector is considered to be endless, otherwise it has maximum of capacity elements.
 *
 * @tparam TValue type of stored data.
 */
template<typename TValue>
class Vector {
public:
    using index_type = StringInt;
    using precision_type = decltype(abs(std::declval<TValue>()));
    /**
     * Default constructor.
     */
    Vector(): precision(0), capacity(-1), mass_transform(0), data({}) {}

    /**
     * Constructor for almost any case.
     *
     * @param required_capacity capacity of vector.
     * @param required_precision precision of contained elements, default is default_precision.
     * @param default_value value that should be set as default value for each element.
     */
    explicit Vector(
            index_type required_capacity,
            double default_value = 0,
            precision_type required_precision = 0
                    ): capacity(std::move(required_capacity)), mass_transform(default_value), precision(required_precision), data({}) { }

    /**
     * Constructor from file.
     *
     * @param file_path path to file to parse vector.
     * @param required_precision precision of contained elements, default is default_precision.
     * @param default_value value that should be set as default value for each element.
     */
    Vector(const char* file_path, precision_type required_precision = 0, TValue default_value = 0):
            mass_transform(default_value), precision(required_precision) {
        std::ifstream infile(file_path);
        infile >> *this;
    }

    explicit Vector(const Matrix_proxy<TValue>& proxy): mass_transform(0), precision(proxy.get_precision()) {
        capacity = std::max(proxy.get_capacity().get_i(), proxy.get_capacity().get_j());
        data = proxy.get_values_as_map();
    }

    /**
     * Copy constructor.
     *
     * @param rhs instance to copy.
     */
    Vector(const Vector& rhs): capacity(rhs.capacity), mass_transform(rhs.mass_transform), precision(rhs.precision), data(rhs.data) { }

    /**
     * Move constructor.
     *
     * @param rhs instance to move.
     */
    Vector(Vector&& rhs) noexcept : capacity(rhs.capacity), mass_transform(rhs.mass_transform), precision(rhs.precision), data(rhs.data) {
        rhs.capacity = StringInt();
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
        std::swap(capacity, tmp.capacity);
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
        capacity = std::move(rhs.capacity);
        rhs.capacity = StringInt();
        mass_transform = std::move(rhs.mass_transform);
        rhs.mass_transform = TValue();
        precision = std::move(rhs.precision);
        rhs.precision = Vector::precision_type();
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
    Vector& operator=(std::map<index_type, TValue>&& data_to_move) noexcept {
        data = std::move(data_to_move);
        data_to_move = {};
        return *this;
    }

    /**
     * precision setter.
     *
     * @param new_precision new double to be set as precision.
     */
    void set_precision(precision_type new_precision) {
        precision = new_precision;
        delete_zero_elements();
    }

    /**
     * precision getter.
     *
     * @return current precision.
     */
    precision_type get_precision() {
        return precision;
    }

    /**
     * Get number of not-null elements.
     *
     * @return number of not-null elements.
     */
    index_type get_size() {
        delete_zero_elements();
        return index_type(data.size());
    }

    /**
     * Set capacity of a Vector.
     * Notice that this method could rubbish existing data.
     *
     * @param new_capacity
     */
    void set_capacity(index_type new_capacity) {
        capacity = std::move(new_capacity);
        data = {};
    }

    /**
     * Get capacity of this Vector.
     *
     * @return capacity of this Vector.
     */
    index_type get_capacity() {
        return capacity;
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
    friend std::istream& operator>>(std::istream& is, Vector<TValue>& x) {
        std::string structure_name;
        std::string type_name;
        is >> structure_name;
        if (structure_name != "vector") {
            is.setstate(std::ios::failbit);
//        throw ParseException(structure_name + " cannot be parsed to vector.");
        }
        is >> type_name;
        if (type_name != "complex" && type_name != "rational") {
            is.setstate(std::ios::failbit);
//        throw CastException(type_name + " cannot be stored to vector.");
        }
        Vector::index_type capacity_from_input;
        is >> capacity_from_input;
        x.set_capacity(capacity_from_input);
        Vector::index_type index;
        TValue value;
        while(is >> index >> value) {
            if (is.fail()) {
                return is;
            }
            x(index - 1) = value;
        }

        return is;
    }


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
        if (capacity >= 0) {
            if (index >= capacity) {
                throw OutOfRangeException("OutOfRangeException");
            }
        }
        if (data.find(index) == data.end()) {
            data[index] = mass_transform;
        }
        if (data[index] <= TValue(precision)) {
            data[index] = TValue(0);
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
        ss << "vector " << get_type_name(TValue()) << " " << vector.capacity << std::endl << std::endl;
        for (auto [key, value]: vector.data) {
            ss << (key + 1) << " " <<  value << std::endl;
        }
        return ss.str();
    }

private:
    /**
     * Number of maximum stored elements.
     * If capacity is negative, Vector is considered to be endless.
     */
    StringInt capacity;

    /**
     * Internal value to decrease memory usage.
     * If mass operation is applied to Vector, mass transform is changed in order not to store all [capacity] elements.
     */
    TValue mass_transform;

    /**
     * Precision of elements in this Vector.
     * If a number is less then precision, value is considered to be zero and should not be stored in data.
     */
    precision_type precision;

    /**
     * Data stored as ordered map.
     *
     * key - StringInt describing index of a number.
     * value - TValue that should be stored.
     */
    std::map<index_type, TValue> data;

    template<typename TComplexReal = double, typename TComplexImaginary = double>
    static std::string get_type_name(TValue) {
        std::string type_name;
        if (typeid(TValue) == typeid(Rational_number)) {
            type_name = "rational";
        } else if (typeid(TValue) == typeid(bool)) {
            type_name = "bit";
        } else if (typeid(TValue) == typeid(Complex_number<TComplexReal, TComplexImaginary>)) {
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
        std::set<index_type> to_delete;
        if (abs(mass_transform) <= precision) {
            mass_transform = TValue(0);
        }
        for (auto [key, value] : data) {
            if (abs(value) <= precision) {
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
 * In this case data is stored as std::vector of uint64_t.
 */
template<>
class Vector<bool> {
public:
    using index_type = unsigned long long;
    /**
     * Default constructor
     */
    Vector(): capacity(0), data({}) { }

    /**
     * Constructor that allows to set default value to data.
     *
     * @param is_zeroes flag to set default value for each element of Vector.
     */
    explicit Vector(index_type d): capacity() {
        set_capacity(d);
    }

    /**
     * Constructor from file.
     *
     * @param file_path name of a file to be parsed.
     */
    Vector(const char* file_path): capacity(0) {
        std::ifstream infile(file_path);
        if (!infile.good()) {
            throw FileNotFoundException(file_path);
        }
        infile >> *this;
        if (infile.bad()) {
            throw ParseException("Error while parsing vector.");
        }
    }

    /**
     * @return amount of elements in data.
     */
    [[nodiscard]] static index_type get_pages(index_type cap) {
        return std::ceil((long double)(cap) / double(bits_per_uint));
    }

    /**
     * @param index
     * @return index of required page
     */
    static index_type get_element_page(index_type index) {
        return std::floor((long double)(index) / double(bits_per_uint));
    }

    /**
     * Set capacity and delete all elements from Vector.
     *
     * @param new_capacity
     */
    void set_capacity(index_type new_capacity) {
        capacity = new_capacity;
        data = std::vector<uint64_t>();
        for (auto i = 0; i < get_pages(new_capacity); ++i) {
            data.push_back(0llu);
        }
    }

    /**
     * Get number of true elements.
     *
     * @return number of true elements.
     */
    [[nodiscard]] int get_size() const {
        int result = 0;
        std::vector<uint64_t> tmp = data;
        for (auto i = 0; i < get_pages(capacity); ++i) {
            while (tmp[i]) {
                result += int(tmp[i] & 1u);
                tmp[i] >>= 1;
            }
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
        for (int i = 0; i < get_pages(capacity); ++i) {
            result.data[i] ^= -1;
        }
        auto extra_cells = bits_per_uint - (capacity % bits_per_uint);
        result.data[get_pages(capacity) - 1] <<= extra_cells;
        result.data[get_pages(capacity) - 1] >>= extra_cells;
        return result;
    }

    /**
     * Element getter.
     *
     * @param index index of element.
     * @return value of element on position [index].
     */
    bool operator()(index_type index) const {
        if (index >= capacity) {
            throw OutOfRangeException("Index " + std::to_string(index) + " is out of range, ["
                                      + std::to_string(capacity) + "] is maximal possible index.");
        }
        return (data[get_element_page(index)] >> (index % bits_per_uint)) & 1llu;
    }

    /**
     * Element setter
     *
     * @param index index of element.
     * @param value value to be set.
     * @return value of element on position [index].
     */
    bool operator()(index_type index, bool value) {
        if (index >= capacity) {
            throw OutOfRangeException("Index " + std::to_string(index) + " is out of range ("
                                      + std::to_string(capacity) + " is maximum possible index).");
        }
        auto index_at_page = index % bits_per_uint;
        if (((data[get_element_page(index)] >> index_at_page) & 1) != value) {
            data[get_element_page(index)] ^= 1llu << index_at_page;
        }
        return value;
    }

    /**
     * Plus and assign operator - OR.
     *
     * @param rhs right operand.
     * @return this Vector OR [rhs].
     */
    Vector<bool>& operator+=(const Vector<bool> &rhs) {
        if (capacity != rhs.capacity) {
            throw IllegalCapacityException();
        }
        for (int i = 0; i < get_pages(capacity); ++i) {
            data[i] |= rhs.data[i];
        }
        return *this;
    }

    /**
     * Multiply and assign operator - AND.
     *
     * @param rhs right operand.
     * @return this Vector AND [rhs].
     */
    Vector<bool>& operator*=(const Vector<bool> &rhs) {
        if (capacity != rhs.capacity) {
            throw IllegalCapacityException();
        }
        for (int i = 0; i < get_pages(capacity); ++i) {
            data[i] = data[i] & rhs.data[i];
        }
        return *this;
    }

    /**
     * Plus operator - OR.
     *
     * @param lhs left operand.
     * @param rhs right operand.
     * @return [lhs] OR [rhs].
     */
    friend Vector<bool> operator+(Vector<bool> lhs, const Vector<bool> &rhs);

    /**
     * Multiply operator - AND.
     *
     * @param lhs left operand.
     * @param rhs right operand.
     * @return [lhs] AND [rhs].
     */
    friend Vector<bool> operator*(Vector<bool> lhs, const Vector<bool> &rhs);

    /**
     * std::to_string implementation for Vector
     *
     * @param vector vector to be converted to std::string.
     * @return std::string representation of [vector]
     */
    friend std::string to_string(Vector<bool> vector);

    /**
     * Maximum possible Vector length.
     */
    static constexpr index_type bits_per_uint = 64;
private:
    /**
     * Data is stored as vector of uint64_t where i-th bit is 1 if i-th value is true and 0 if value is false.
     */
    std::vector<uint64_t> data;

    /**
     * Vector capacity.
     */
    index_type capacity;
};

#endif //COUNTING_STARS_VECTOR_H
