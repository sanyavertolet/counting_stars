/**
 * File containing Matrix_column_coord class implementation.
 *
 * @author sanyavertolet
 */

#include "Matrix_column_coord.h"

Matrix_column_coord::Matrix_column_coord(): column_index(0) { }

Matrix_column_coord::Matrix_column_coord(StringInt index):
column_index(index >= 0 ? std::move(index) : throw IllegalStateException("index must not be negative")) { }

StringInt Matrix_column_coord::get_column_index() const {
    return column_index;
}

bool Matrix_column_coord::has(const Pos& dot) const {
    return dot.get_j() == column_index;
}