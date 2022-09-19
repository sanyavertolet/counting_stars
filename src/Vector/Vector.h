/**
 * Header containing Vector class declaration.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_VECTOR_H
#define COUNTING_STARS_VECTOR_H

#include <map>
#include "../StringInt/StringInt.h"
#include "../Rational_number/Rational_number.h"

template<typename TValue>
class Vector {
public:
    Vector(): precision(default_precision), dim(-1), mass_transform(0), data({}) { }
    Vector(const StringInt& required_size, TValue default_value = 0): precision(default_precision), mass_transform(default_value) {
        if (required_size >= 0) {
            for (StringInt i = 0; i < required_size; ++i) {
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

private:
    double precision;
    StringInt dim;
    TValue mass_transform;
    std::map<StringInt, TValue> data;
    static constexpr double default_precision = 0.0000000001;
};



#endif //COUNTING_STARS_VECTOR_H
