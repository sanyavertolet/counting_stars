/**
 * File containing Matrix_row_coord class implementation.
 *
 * @author sanyavertolet
 */

#include "Matrix_row_coord.h"

Matrix_row_coord::Matrix_row_coord(): row_index(0) { }

Matrix_row_coord::Matrix_row_coord(StringInt index):
row_index(index >= 0 ? std::move(index) : throw IllegalStateException("Row index must not be negative.")) { }

StringInt Matrix_row_coord::get_row_index() const {
    return row_index;
}

bool Matrix_row_coord::has(const Pos& dot) const {
    return dot.get_i() == row_index;
}