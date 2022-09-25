/**
 * File containing Vector class implementation.
 *
 * @author sanyavertolet
 */

#include "Vector.h"

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

template<typename TValue>
std::string to_string(Vector<TValue> vector) {
    std::stringstream ss;
    std::string type_name;
    ss << "vector " << get_type_name(TValue()) << " " << vector.dim << std::endl << std::endl;
    for (auto [key, value]: vector.data) {
        ss << (key + 1) << value << std::endl;
    }
    return ss.str();
}

template<typename TValue, typename TComplexReal, typename TComplexImaginary>
std::string get_type_name(TValue type) {
    std::string type_name;
    if (typeid(TValue) == typeid(Rational_number)) {
        type_name = "rational";
    } else if (typeid(TValue) == typeid(bool)) {
        type_name = "bit";
    } else if (typeid(TValue) == typeid(Complex_number<TComplexReal, TComplexImaginary>)) {
        type_name = "complex";
    } else {
        type_name = typeid(TValue).name();
    }
    return type_name;
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
