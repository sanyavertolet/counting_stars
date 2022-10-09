/**
 * File containing Vector class implementation.
 *
 * @author sanyavertolet
 */

#include "../Complex_number/Complex_number.h"
#include "Vector.h"

template<typename TValue, typename TValueRight>
bool operator==(const Vector<TValue> &lhs, const Vector<TValueRight> &rhs) {
    auto predicate = [](auto lhs, auto rhs) {
        return decltype(lhs + rhs)(lhs) == decltype(lhs + rhs)(rhs);
    };
    return lhs.capacity == rhs.capacity && lhs.get_size() == rhs.get_size() && lhs.mass_transform == rhs.mass_transform && std::equal(lhs.data.begin(), lhs.data.end(), rhs.data.begin(), predicate);
}

template<typename TValueLeft, typename TValueRight>
bool operator!=(const Vector<TValueLeft> &lhs, const Vector<TValueRight> &rhs) {
    return !(lhs == rhs);
}

template<typename TValueLeft, typename TValueRight>
auto operator+(const Vector<TValueLeft> &lhs, const Vector<TValueRight> &rhs) {
    Vector<decltype(TValueLeft() + TValueRight())> result;
    for (auto [key, value] : lhs.data) {
        result[key] = value;
    }
    for (auto [key, value] : rhs.data) {
        if (lhs.data.find(key) == lhs.data.end()) {
            result[key] = value;
        } else {
            result[key] += value;
        }
    }
    result.mass_transform = lhs.mass_transform + rhs.mass_transform;
    result.set_precision((lhs.precision + rhs.precision) / 2);
    return result;
}

template<typename TValueLeft, typename TValueRight>
auto operator-(const Vector<TValueLeft> &lhs, const Vector<TValueRight> &rhs) {
    Vector<decltype(TValueLeft() + TValueRight())> result;
    for (auto [key, value] : lhs.data) {
        result[key] = value;
    }
    for (auto [key, value] : rhs.data) {
        if (lhs.data.find(key) == lhs.data.end()) {
            result[key] = -value;
        } else {
            result[key] -= value;
        }
    }
    result.mass_transform = lhs.mass_transform - rhs.mass_transform;
    result.set_precision((lhs.precision + rhs.precision) / 2);
    return result;
}

template<typename TValueLeft, typename TValueRight>
auto operator+(Vector<TValueLeft> lhs, const TValueRight& rhs) {
    for (auto& [key, value] : lhs) {
        value += rhs;
    }
    lhs.mass_transform += rhs;
    lhs.delete_zero_elements();
    return lhs;
}

template<typename TValueLeft, typename TValueRight>
auto operator-(Vector<TValueLeft> lhs, const TValueRight& rhs) {
    for (auto& [key, value] : lhs) {
        value -= rhs;
    }
    lhs.mass_transform -= rhs;
    lhs.delete_zero_elements();
    return lhs;
}

template<typename TValueLeft, typename TValueRight>
auto operator*(Vector<TValueLeft> lhs, const TValueRight& rhs) {
    for (auto& [key, value] : lhs) {
        value *= rhs;
    }
    lhs.mass_transform *= rhs;
    lhs.delete_zero_elements();
    return lhs;
}

template<typename TValueLeft, typename TValueRight>
auto operator/(Vector<TValueLeft> lhs, const TValueRight& rhs) {
    if (rhs == 0) {
        throw DivisionByZeroException("Denominator is null.");
    }
    for (auto& [key, value] : lhs) {
        value /= rhs;
    }
    lhs.mass_transform /= rhs;
    lhs.delete_zero_elements();
    return lhs;
}
