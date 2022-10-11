/**
 * File containing Pos class implementation.
 *
 * Pos describes position in matrix.
 *
 * @author sanyavertolet
 */

#include "Pos.h"

Pos::Pos() : i(0), j(0) { }

Pos::Pos(StringInt row, StringInt col) :
i(row >= -1 ? std::move(row) : throw IllegalStateException("Row index should be positive or -1: " + std::string(row))),
j(col >= -1 ? std::move(col) : throw IllegalStateException("Column index should be positive or -1: " + std::string(col))) {}

void Pos::set_i(const StringInt& new_i) {
    if (new_i < 0) {
        throw IllegalStateException("Row index should be positive or -1: " + std::string(new_i));
    }
    i = new_i;
}

void Pos::set_j(const StringInt& new_j) {
    if (new_j < 0) {
        throw IllegalStateException("Column index should be positive or -1: " + std::string(new_j));
    }
    j = new_j;
}

StringInt Pos::get_i() const {
    return i;
}

StringInt Pos::get_j() const {
    return j;
}

Pos Pos::operator~() {
    return {j, i};
}

bool operator==(const Pos& lhs, const Pos& rhs) {
    return lhs.i == rhs.i && lhs.j == rhs.j;
}

bool operator!=(const Pos& lhs, const Pos& rhs) {
    return !(lhs == rhs);
}

bool operator<(const Pos& lhs, const Pos& rhs) {
    return lhs.i < rhs.i && lhs.j < rhs.j;
}

bool operator>(const Pos& lhs, const Pos& rhs) {
    return rhs < lhs;
}

bool operator<=(const Pos& lhs, const Pos& rhs) {
    return lhs < rhs || lhs == rhs;
}

bool operator>=(const Pos& lhs, const Pos& rhs) {
    return lhs > rhs || lhs == rhs;
}

StringInt Pos::operator-(const Pos& rhs) const {
    return abs(i - rhs.i) + abs(j - rhs.j);
}

std::string to_string(const Pos& pos) {
    return to_string(pos.get_i()) + " " + to_string(pos.get_j());
}

std::ostream& operator<<(std::ostream& os, const Pos& pos) {
    os << to_string(pos);
    return os;
}

std::istream& operator>>(std::istream& is, Pos& pos) {
    StringInt ii, jj;
    is >> ii >> jj;

    try {
        pos.set_i(ii);
    } catch (IllegalStateException& illegalStateException) {
        is.setstate(std::ios::failbit);
        return is;
    }

    try {
        pos.set_j(jj);
    } catch (IllegalStateException& illegalStateException) {
        is.setstate(std::ios::failbit);
    }

    return is;
}

std::size_t std::hash<Pos>::operator()(const Pos& pos) const {
    using std::size_t;
    using std::hash;
    return hash<StringInt>()(pos.get_i()) ^ (hash<StringInt>()(pos.get_j()) << 1);
}
