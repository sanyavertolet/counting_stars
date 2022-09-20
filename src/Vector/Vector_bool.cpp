/**
 * File containing Vector class implementation.
 *
 * @author sanyavertolet
 */

#include "Vector.h"

int Vector<bool>::get_size() const {
    int result = 0;
    uint64_t tmp = data;
    while (tmp) {
        result += int(tmp & 1);
        tmp >>= 1;
    }
    return result;
}

std::ostream& operator<< (std::ostream& os, Vector<bool> const& x) {
    os << to_string(x);
    return os;
}

std::istream& operator>> (std::istream& is, Vector<bool>& x) {
    throw std::runtime_error("Not implemented yet.");
    return is;
}

bool operator==(const Vector<bool> &lhs, const Vector<bool> &rhs) {
    return lhs.data == rhs.data;
}

bool operator!=(const Vector<bool> &lhs, const Vector<bool> &rhs) {
    return !(lhs == rhs);
}

Vector<bool> Vector<bool>::operator~() {
    Vector<bool> result = *this;
    result.data ^= -1;
    return result;
}

bool Vector<bool>::operator()(int index) const {
    if (index >= max_index) {
        throw OutOfRangeException("Index " + std::to_string(index) + " is out of range, ["
                                  + std::to_string(max_index) + "] is maximal possible index.");
    }
    return (data & (1 << index)) >> index;
}

bool Vector<bool>::operator()(int index, bool value) {
    if (index >= max_index) {
        throw OutOfRangeException("Index " + std::to_string(index) + " is out of range ("
        + std::to_string(max_index) + " is maximum possible index).");
    }
    data ^= 1 << index;
    return value;
}

Vector<bool>& Vector<bool>::operator+=(const Vector<bool> &rhs) {
    data |= rhs.data;
    return *this;
}

Vector<bool>& Vector<bool>::operator*=(const Vector<bool> &rhs) {
    data &= rhs.data;
    return *this;
}

Vector<bool> operator+(const Vector<bool> &lhs, const Vector<bool> &rhs) {
    return lhs.data | rhs.data;
}

Vector<bool> operator*(const Vector<bool> &lhs, const Vector<bool> &rhs) {
    return lhs.data & rhs.data;
}

std::string to_string(Vector<bool> vector) {
    std::stringstream ss;
    std::string type_name;
    ss << "vector bit " << vector.max_index << std::endl << std::endl;
    for (int i = 0; i < vector.max_index; ++i) {
        unsigned long long value = (vector.data >> i) & 1;
        if (value) {
            ss << i + 1 << " " << value << std::endl;
        }
    }
    return ss.str();
}
