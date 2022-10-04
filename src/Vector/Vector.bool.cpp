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
    throw std::runtime_error("Not implemented yet.");
//    return is;
}

bool operator==(const Vector<bool> &lhs, const Vector<bool> &rhs) {
    return lhs.data == rhs.data;
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
    ss << "vector bit " << vector.dim << std::endl << std::endl;
    for (int i = 0; i < vector.dim; ++i) {
        unsigned long long value = (vector.data[Vector<bool>::get_element_page(i)] >> (i % Vector<bool>::bits_per_uint)) & 1;
        if (value) {
            ss << i + 1 << " " << value << std::endl;
        }
    }
    return ss.str();
}
