/**
 * File containing Vector class implementation.
 *
 * @author sanyavertolet
 */

#include "../Complex_number/Complex_number.h"
#include "Vector.h"

template<typename TValueLeft, typename TValueRight>
bool operator==(const Vector<TValueLeft> &lhs, const Vector<TValueRight> &rhs) {
    auto predicate = [](auto lhs, auto rhs) {
        return decltype(lhs + rhs)(lhs) == decltype(lhs + rhs)(rhs);
    };
    return lhs.capacity == rhs.capacity && lhs.get_size() == rhs.get_size() && lhs.mass_transform == rhs.mass_transform && std::equal(lhs.data.begin(), lhs.data.end(), rhs.data.begin(), predicate);
}

template<typename TValue>
static typename Vector<TValue>::precision_type default_precision = 0;

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

#ifdef __DEV__
template<typename TValue>
Vector<TValue> parse_from_ifstream(std::ifstream &is) {
    std::string input = "#";
    while(!input.empty() && input.front() == '#') {
        std::getline(is, input);
    }
    std::string type_of_file = input.substr(0, input.find(' '));
    input.erase(0, input.find(' '));
    std::string t_value = input.substr(0, input.find(' '));
    input.erase(0, input.find(' '));
    if (t_value == "rational") {
        Vector<Rational_number> result;
        StringInt index;
        Rational_number number;
        while(is >> index >> number) {
            result(index) = number;
        }
        return result;
    } else if (t_value == "complex") {
        throw std::runtime_error("Not implemented yet");
        //todo: what type of complex does word `complex` mean?!
        Vector<Complex_number<Rational_number, Rational_number>> result;
        return result;
    } else if (t_value == "bit") {
        Vector<bool> result;
        int index;
        bool number;
        while(is >> index >> number) {
            result(index) |= number;
        }
        return result;
    } else {
        throw std::runtime_error("Not implemented yet");
    }
}
#endif
