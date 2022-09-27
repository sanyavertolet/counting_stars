/**
 * Header containing Matrix_row_coord class declaration and implementation.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_MATRIX_ROW_COORD_H
#define COUNTING_STARS_MATRIX_ROW_COORD_H

#include <utility>

#include "../StringInt/StringInt.h"

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
    Matrix_row_coord(StringInt index): row_index(std::move(index)) { }

    /**
     * row_index getter.
     *
     * @return row_index.
     */
    [[nodiscard]] StringInt get_row_index() const {
        return row_index;
    }
private:
    /**
     * index of a Matrix row.
     */
    StringInt row_index;
};


#endif //COUNTING_STARS_MATRIX_ROW_COORD_H
