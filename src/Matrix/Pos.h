/**
 * Header containing Pos class declaration and implementation.
 *
 * Pos describes position in matrix.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_POS_H
#define COUNTING_STARS_POS_H

#include <string>
#include <utility>

#include "../StringInt/StringInt.h"
#include "../exceptions/exceptions.h"

/**
 * Class that defines position in Matrix.
 *
 * @tparam StringInt type of coordinates.
 * @property i index of a row.
 * @property j index of a column.
 */
class Pos {
public:
    /**
     * Default constructor.
     */
    Pos() : i(0), j(0) { }

    /**
     * Constructor from pair of coordinates.
     *
     * @param row index of a row.
     * @param col index of a column.
     */
    Pos(StringInt row, StringInt col) :
    i(row >= -1 ? std::move(row) : throw IllegalStateException("Row index should be positive or -1: " + std::string(row))),
    j(col >= -1 ? std::move(col) : throw IllegalStateException("Column index should be positive or -1: " + std::string(col))) {}

    /**
     * [i] setter.
     *
     * @param new_i new row index.
     * @throws OutOfRangeException on negative index.
     */
    void set_i(const StringInt& new_i) {
        if (new_i < 0) {
            throw IllegalStateException("Row index should be positive or -1: " + std::string(new_i));
        }
        i = new_i;
    }

    /**
     * [j] setter.
     *
     * @param new_j new column index.
     * @throws OutOfRangeException on negative index.
     */
    void set_j(const StringInt& new_j) {
        if (new_j < 0) {
            throw IllegalStateException("Column index should be positive or -1: " + std::string(new_j));
        }
        j = new_j;
    }

    /**
     * [i] getter.
     * @return row index.
     */
    [[nodiscard]] StringInt get_i() const {
        return i;
    }

    /**
     * [j] getter.
     *
     * @return column index.
     */
    [[nodiscard]] StringInt get_j() const {
        return j;
    }

    /**
     * Transparent operator.
     *
     * @return Pos with swapped coordinates.
     */
    Pos operator~() {
        return {j, i};
    }

    /**
     * Eq operator.
     *
     * @param lhs left operand.
     * @param rhs right operand.
     * @return true if lhs and rhs are equal, false otherwise.
     */
    friend bool operator==(const Pos& lhs, const Pos& rhs) {
        return lhs.i == rhs.i && lhs.j == rhs.j;
    }

    /**
     * Neq operator.
     *
     * @param lhs left operand.
     * @param rhs right operand.
     * @return true if lhs and rhs are not equal, false otherwise.
     */
    friend bool operator!=(const Pos& lhs, const Pos& rhs) {
        return !(lhs == rhs);
    }

    /**
     * Less operator.
     *
     * @param lhs left operand.
     * @param rhs right operand.
     * @return true if lhs is less than rhs, false otherwise.
     */
    friend bool operator<(const Pos& lhs, const Pos& rhs) {
        return lhs.i < rhs.i && lhs.j < rhs.j;
    }

    /**
     * Greater operator.
     *
     * @param lhs left operand.
     * @param rhs right operand.
     * @return true if lhs is greater than rhs, false otherwise.
     */
    friend bool operator>(const Pos& lhs, const Pos& rhs) {
        return rhs < lhs;
    }

    /**
     * Leq operator.
     *
     * @param lhs left operand.
     * @param rhs right operand.
     * @return true if lhs is less than rhs or equal to it, false otherwise.
     */
    friend bool operator<=(const Pos& lhs, const Pos& rhs) {
        return lhs < rhs || lhs == rhs;
    }

    /**
     * Geq operator.
     *
     * @param lhs left operand.
     * @param rhs right operand.
     * @return true if lhs is greater than rhs or equal to it, false otherwise.
     */
    friend bool operator>=(const Pos& lhs, const Pos& rhs) {
        return lhs > rhs || lhs == rhs;
    }

    /**
     * Distance operator.
     *
     * @param rhs right operand.
     * @return Manhattan distance between two Pos.
     */
    StringInt operator-(const Pos& rhs) const {
        return abs(i - rhs.i) + abs(j - rhs.j);
    }

    /**
     * std::string cast operator.
     *
     * @return string representation of this Pos.
     */
    operator std::string() const {
        return "(" + std::string(i) + ";" + std::string(j) + ")";
    }
private:
    /**
     * Index of a row.
     */
    StringInt i;

    /**
     * Index of a column.
     */
    StringInt j;
};


#endif //COUNTING_STARS_POS_H
