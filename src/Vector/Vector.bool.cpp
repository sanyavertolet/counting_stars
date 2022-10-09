/**
 * File containing Vector class implementation.
 *
 * @author sanyavertolet
 */

#include "Vector.h"

std::ostream& operator<<(std::ostream& os, Vector<bool> const& x) {
    os << to_string(x);
    return os;
}

std::istream& operator>>(std::istream& is, Vector<bool>& x) {
    std::string structure_name;
    std::string type_name;
    is >> structure_name;
    if (structure_name != "vector") {
        is.setstate(std::ios::failbit);
//        throw ParseException(structure_name + " cannot be parsed to vector.");
    }
    is >> type_name;
    if (type_name != "bit") {
        is.setstate(std::ios::failbit);
//        throw CastException(type_name + " cannot be cast to bit vector.");
    }
    Vector<bool>::index_type capacity;
    is >> capacity;
    x.set_capacity(capacity);
    Vector<bool>::index_type index;
    bool value;
    while(is >> index >> value) {
        if (is.fail()) {
            return is;
        }
        x(index - 1, value);
    }

    return is;
}

bool operator==(const Vector<bool> &lhs, const Vector<bool> &rhs) {
    auto is_capacity_ok = lhs.capacity == rhs.capacity;
    auto is_size_ok = lhs.get_size() == rhs.get_size();
    auto is_equal = std::equal(lhs.data.begin(), lhs.data.end(), rhs.data.begin());
    return is_capacity_ok && is_size_ok && is_equal;
}

bool operator!=(const Vector<bool> &lhs, const Vector<bool> &rhs) {
    return !(lhs == rhs);
}

Vector<bool> operator+(Vector<bool> lhs, const Vector<bool> &rhs) {
    return (lhs += rhs);
}

Vector<bool> operator*(Vector<bool> lhs, const Vector<bool> &rhs) {
    return (lhs *= rhs);
}

std::string to_string(Vector<bool> vector) {
    std::stringstream ss;
    std::string type_name;
    ss << "vector bit " << vector.capacity << std::endl << std::endl;
    for (int i = 0; i < vector.capacity; ++i) {
        unsigned long long value = (vector.data[Vector<bool>::get_element_page(i)] >> (i % Vector<bool>::bits_per_uint)) & 1;
        if (value) {
            ss << i + 1 << " " << value << std::endl;
        }
    }
    return ss.str();
}
