/**
 * Header containing Pos class declaration.
 *
 * Pos describes position in matrix.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_POS_H
#define COUNTING_STARS_POS_H

#include <string>
#include <utility>
#include <functional>

#include "../StringInt/StringInt.h"
#include "../exceptions/exceptions.h"

class Pos;
std::string to_string(const Pos& pos);

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
    Pos();

    /**
     * Constructor from pair of coordinates.
     *
     * @param row index of a row.
     * @param col index of a column.
     */
    Pos(StringInt row, StringInt col);

    /**
     * [i] setter.
     *
     * @param new_i new row index.
     * @throws OutOfRangeException on negative index.
     */
    void set_i(const StringInt& new_i);

    /**
     * [j] setter.
     *
     * @param new_j new column index.
     * @throws OutOfRangeException on negative index.
     */
    void set_j(const StringInt& new_j);

    /**
     * [i] getter.
     * @return row index.
     */
    [[nodiscard]] StringInt get_i() const;

    /**
     * [j] getter.
     *
     * @return column index.
     */
    [[nodiscard]] StringInt get_j() const;

    /**
     * Transparent operator.
     *
     * @return Pos with swapped coordinates.
     */
    Pos operator~();

    /**
     * Eq operator.
     *
     * @param lhs left operand.
     * @param rhs right operand.
     * @return true if lhs and rhs are equal, false otherwise.
     */
    friend bool operator==(const Pos& lhs, const Pos& rhs);

    /**
     * Neq operator.
     *
     * @param lhs left operand.
     * @param rhs right operand.
     * @return true if lhs and rhs are not equal, false otherwise.
     */
    friend bool operator!=(const Pos& lhs, const Pos& rhs);

    /**
     * Less operator.
     *
     * @param lhs left operand.
     * @param rhs right operand.
     * @return true if lhs is less than rhs, false otherwise.
     */
    friend bool operator<(const Pos& lhs, const Pos& rhs);

    /**
     * Greater operator.
     *
     * @param lhs left operand.
     * @param rhs right operand.
     * @return true if lhs is greater than rhs, false otherwise.
     */
    friend bool operator>(const Pos& lhs, const Pos& rhs);

    /**
     * Leq operator.
     *
     * @param lhs left operand.
     * @param rhs right operand.
     * @return true if lhs is less than rhs or equal to it, false otherwise.
     */
    friend bool operator<=(const Pos& lhs, const Pos& rhs);

    /**
     * Geq operator.
     *
     * @param lhs left operand.
     * @param rhs right operand.
     * @return true if lhs is greater than rhs or equal to it, false otherwise.
     */
    friend bool operator>=(const Pos& lhs, const Pos& rhs);

    /**
     * Distance operator.
     *
     * @param rhs right operand.
     * @return Manhattan distance between two Pos.
     */
    StringInt operator-(const Pos& rhs) const;
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

bool operator==(const Pos& lhs, const Pos& rhs);

/**
 * Operator that prints Pos to std::ostream.
 *
 * @param os output stream.
 * @param x Pos to print.
 * @return os.
 */
std::ostream& operator<<(std::ostream& os, Pos const& pos);

/**
 * Operator that reads Pos from std::istream.
 *
 * @param is input stream.
 * @param x Pos to read to.
 * @return is.
 */
std::istream& operator>>(std::istream& is, Pos& pos);

namespace std {
    template <>
    struct hash<Pos> {
        std::size_t operator()(const Pos& pos) const;
    };
}

#endif //COUNTING_STARS_POS_H
