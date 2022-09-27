/**
 * Header containing Matrix_column_coord class declaration and implementation.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_MATRIX_COLUMN_COORD_H
#define COUNTING_STARS_MATRIX_COLUMN_COORD_H

#include <utility>

#include "../StringInt/StringInt.h"

/**
 * Class that allows to access Matrix with column slice.
 */
class Matrix_column_coord {
public:
    /**
     * Default constructor.
     */
    Matrix_column_coord(): column_index(0) { }

    /**
     * Constructor StringInt.
     *
     * @param index index of a column.
     */
    Matrix_column_coord(StringInt index): column_index(std::move(index)) { }

    /**
     * column_index getter.
     *
     * @return index of a Matrix column.
     */
    [[nodiscard]] StringInt get_column_index() const {
        return column_index;
    }
private:
    /**
     * index of a Matrix column.
     */
    StringInt column_index;
};


#endif //COUNTING_STARS_MATRIX_COLUMN_COORD_H
