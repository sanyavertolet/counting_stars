/**
 * File containing Vector class implementation.
 *
 * @author sanyavertolet
 */

#include "Vector.h"

template<typename TValue>
void Vector<TValue>::set_precision(double new_precision) {
    precision = new_precision;
}

template<typename TValue>
double Vector<TValue>::get_precision() {
    return precision;
}

template<typename TValue>
int Vector<TValue>::get_size() {
    return data.size();
}

template<typename TValue>
StringInt Vector<TValue>::get_dim() {
    return dim;
}

template<typename TValueLeft, typename TValueRight>
bool operator==(const Vector<TValueLeft> &lhs, const Vector<TValueRight> &rhs) {
    auto predicate = [](auto lhs, auto rhs) {
        return decltype(lhs + rhs)(lhs) == decltype(lhs + rhs)(rhs);
    };
    return lhs.dim == rhs.dim && lhs.get_size() == rhs.get_size() && lhs.mass_transform == rhs.mass_transform && std::equal(lhs.data.begin(), lhs.data.end(), rhs.data.begin(), predicate);
}

template<typename TValueLeft, typename TValueRight>
bool operator!=(const Vector<TValueLeft> &lhs, const Vector<TValueRight> &rhs) {
    return !(lhs == rhs);
}

template<typename TValue>
Vector<TValue> Vector<TValue>::operator-() {
    Vector<TValue> result(*this);
    for(auto& [key, value]: result.data) {
        value = -value;
    }
    mass_transform = -mass_transform;
    return result;
}

template<typename TValue>
TValue& Vector<TValue>::operator()(const StringInt& index) {
    if (dim >= 0) {
        if (index >= dim) {
            //todo: implement OutOfRangeException
            throw std::runtime_error("OutOfRangeException");
        }
    }
    if (data.find(index) == data.end()) {
        data[index] = mass_transform;
    }
    auto result(data.at(index));
    if (Rational_number(precision) != Rational_number(0) && result + precision == precision) {
        return TValue(0);
    } else {
        return data.at(index);
    }
}

template<typename TValue>
template<typename TValueRight>
auto& Vector<TValue>::operator+=(const Vector<TValueRight> &rhs) {
    mass_transform += rhs.mass_transform;
    for (auto [key, value] : rhs.data) {
        if (data.find(key) == data.end()) {
            data[key] = mass_transform + value;
        } else {
            data[key] += value;
        }
    }
    return *this;
}

template<typename TValue>
template<typename TValueRight>
auto& Vector<TValue>::operator-=(const Vector<TValueRight> &rhs) {
    mass_transform -= rhs.mass_transform;
    for (auto [key, value] : rhs.data) {
        if (data.find(key) == data.end()) {
            data[key] = mass_transform - value;
        } else {
            data[key] -= value;
        }
    }
    return *this;
}

template<typename TValueLeft, typename TValueRight>
auto operator+(const Vector<TValueLeft> &lhs, const Vector<TValueRight> &rhs) {
    Vector<decltype(TValueLeft() + TValueRight())> result;
    result += lhs;
    result += rhs;
    return result;
}

template<typename TValueLeft, typename TValueRight>
auto operator-(const Vector<TValueLeft> &lhs, const Vector<TValueRight> &rhs) {
    Vector<decltype(TValueLeft() + TValueRight())> result;
    result += lhs;
    result -= rhs;
    return result;
}

template<typename TValueLeft, typename TValueRight>
auto operator+(Vector<TValueLeft> lhs, const TValueRight& rhs) {
    for (auto& [key, value] : lhs) {
        value += rhs;
    }
    lhs.mass_transform += rhs;
    return lhs;
}

template<typename TValueLeft, typename TValueRight>
auto operator-(Vector<TValueLeft> lhs, const TValueRight& rhs) {
    for (auto& [key, value] : lhs) {
        value -= rhs;
    }
    lhs.mass_transform -= rhs;
    return lhs;
}

template<typename TValueLeft, typename TValueRight>
auto operator*(Vector<TValueLeft> lhs, const TValueRight& rhs) {
    for (auto& [key, value] : lhs) {
        value *= rhs;
    }
    lhs.mass_transform *= rhs;
    return lhs;
}

template<typename TValueLeft, typename TValueRight>
auto operator/(Vector<TValueLeft> lhs, const TValueRight& rhs) {
    for (auto& [key, value] : lhs) {
        value /= rhs;
    }
    lhs.mass_transform /= rhs;
    return lhs;
}
