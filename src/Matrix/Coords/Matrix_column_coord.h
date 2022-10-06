/**
 * Header containing Matrix_column_coord class declaration.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_MATRIX_COLUMN_COORD_H
#define COUNTING_STARS_MATRIX_COLUMN_COORD_H

#include <utility>

#include "../../StringInt/StringInt.h"
#include "../../Pos/Pos.h"

/**
 * Class that allows to access Matrix with column slice.
 */
class Matrix_column_coord {
public:
    /**
     * Default constructor.
     */
    Matrix_column_coord();

    /**
     * Constructor StringInt.
     *
     * @param index index of a column.
     */
    explicit Matrix_column_coord(StringInt index);

    /**
     * column_index getter.
     *
     * @return index of a Matrix column.
     */
    [[nodiscard]] StringInt get_column_index() const;

    /**
     * Check if dot is inside Matrix_column_coords.
     *
     * @param dot Pos with coordinates.
     * @return true if dot is in Matrix_column_coords, false otherwise.
     */
    [[nodiscard]] bool has(const Pos& dot) const;
private:
    /**
     * index of a Matrix column.
     */
    StringInt column_index;
};


#endif //COUNTING_STARS_MATRIX_COLUMN_COORD_H
