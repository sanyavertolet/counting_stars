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

template<typename TValue>
class Vector {
public:
    Vector(
            double required_precision = default_precision,
            StringInt  required_dim = -1
                    ): precision(required_precision), dim(std::move(required_dim)), mass_transform(0), data({}) { }
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
    Vector(
            const StringInt& required_dim,
            double required_precision = default_precision,
            TValue default_value = 0
                    ): precision(default_precision), mass_transform(default_value) {
        if (required_dim >= 0) {
            for (StringInt i = 0; i < required_dim; ++i) {
                data[i] = default_value;
            }
        } else {
            mass_transform = default_value;
        }
    }

    void set_precision(double new_precision);
    double get_precision();

    int get_size();
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

    template<typename TValueLeft, typename TValueRight>
    friend bool operator==(const Vector<TValueLeft> &lhs, const Vector<TValueRight> &rhs);

    template<typename TValueLeft, typename TValueRight>
    friend bool operator!=(const Vector<TValueLeft> &lhs, const Vector<TValueRight> &rhs);

    Vector operator-();

    TValue& operator()(const StringInt& index);

    template<typename TValueRight>
    auto& operator+=(const Vector<TValueRight> &rhs);

    template<typename TValueRight>
    auto& operator-=(const Vector<TValueRight> &rhs);

    template<typename TValueLeft, typename TValueRight>
    friend auto operator+(const Vector<TValueLeft> &lhs, const Vector<TValueRight> &rhs);

    template<typename TValueLeft, typename TValueRight>
    friend auto operator-(const Vector<TValueLeft> &lhs, const Vector<TValueRight> &rhs);

    template<typename TValueLeft, typename TValueRight>
    friend auto operator+(Vector<TValueLeft> lhs, const TValueRight& rhs);

    template<typename TValueLeft, typename TValueRight>
    friend auto operator-(Vector<TValueLeft> lhs, const TValueRight& rhs);

    template<typename TValueLeft, typename TValueRight>
    friend auto operator*(Vector<TValueLeft> lhs, const TValueRight& rhs);

    template<typename TValueLeft, typename TValueRight>
    friend auto operator/(Vector<TValueLeft> lhs, const TValueRight& rhs);

    friend std::string to_string(Vector<TValue> vector);

private:
    double precision;
    StringInt dim;
    TValue mass_transform;
    std::map<StringInt, TValue> data;
    static constexpr double default_precision = 0.0000000001;
};

template<typename TValue>
Vector<TValue> parse_from_ifstream(std::ifstream &is);

template<>
class Vector<bool> {
    Vector(bool is_zeroes = true): data(is_zeroes ? 0 : -1) { }
    Vector(const char* file_path) {
        std::ifstream infile(file_path);
        if (infile.bad()) {
//            throw FileNotFoundException();
            throw std::runtime_error("FileNotFoundException: " + std::string(file_path));
        }
        data = 0u;
        //todo: implement
    }

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

    friend bool operator==(const Vector<bool> &lhs, const Vector<bool> &rhs);

    friend bool operator!=(const Vector<bool> &lhs, const Vector<bool> &rhs);

    Vector<bool> operator~();

    bool operator()(int index) const;
    bool operator()(int index, bool value);

    Vector<bool>& operator+=(const Vector<bool> &rhs);

    Vector<bool>& operator*=(const Vector<bool> &rhs);

    friend Vector<bool> operator+(const Vector<bool> &lhs, const Vector<bool> &rhs);

    friend Vector<bool> operator*(const Vector<bool> &lhs, const Vector<bool> &rhs);

    friend std::string to_string(Vector<bool> vector);

private:
    uint64_t data;
    int max_index = 64;
};

#endif //COUNTING_STARS_VECTOR_H
