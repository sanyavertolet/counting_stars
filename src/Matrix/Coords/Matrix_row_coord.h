/**
 * Header containing Matrix_row_coord class declaration and implementation.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_MATRIX_ROW_COORD_H
#define COUNTING_STARS_MATRIX_ROW_COORD_H

#include <utility>

#include "../../StringInt/StringInt.h"
#include "../../Pos/Pos.h"

/**
 * Class that allows to access Matrix with row slice.
 */
class Matrix_row_coord {
public:
    /**
     * Default constructor.
     */
    Matrix_row_coord(): row_index(0) { }

    /**
     * Constructor from StringInt.
     *
     * @param index index of a row.
     */
    Matrix_row_coord(StringInt index):
    row_index(index >= 0 ? std::move(index) : throw IllegalStateException("Row index must not be negative.")) { }

    /**
     * row_index getter.
     *
     * @return row_index.
     */
    [[nodiscard]] StringInt get_row_index() const {
        return row_index;
    }

    /**
     * Check if dot is inside Matrix_row_coords.
     *
     * @param dot Pos with coordinates.
     * @return true if dot is in Matrix_row_coords, false otherwise.
     */
    [[nodiscard]] bool has(const Pos& dot) const {
        return dot.get_i() == row_index;
    }
private:
    /**
     * index of a Matrix row.
     */
    StringInt row_index;
};


#endif //COUNTING_STARS_MATRIX_ROW_COORD_H
