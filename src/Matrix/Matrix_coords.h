/**
 * Header containing Matrix_coords class declaration and implementation.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_MATRIX_COORDS_H
#define COUNTING_STARS_MATRIX_COORDS_H

#include <utility>

#include "Pos.h"

/**
 * Class that allows to access Matrix with rectangle slice.
 */
class Matrix_coords {
public:
    /**
     * Default constructor.
     */
    Matrix_coords(): tlhs({-1, -1}), brhs({-1, -1}) { }

    /**
     * Constructor from two Pos.
     * @param tl top-left Pos.
     * @param br bottom-right Pos.
     */
    Matrix_coords(Pos tl, Pos br): tlhs(std::move(tl)), brhs(std::move(br)) { }

    /**
     * Constructor from four StringInt.
     *
     * @param t top index.
     * @param l left index.
     * @param b bottom index.
     * @param r right index.
     */
    Matrix_coords(const StringInt& t, const StringInt& l, const StringInt& b, const StringInt& r):
            tlhs({t, l}), brhs({b, r}) {
    }

    /**
     * tlhs getter.
     *
     * @return tlhs.
     */
    [[nodiscard]] Pos get_tlhs() const {
        return tlhs;
    }

    /**
     * brhs getter.
     *
     * @return brhs.
     */
    [[nodiscard]] Pos get_brhs() const {
        return tlhs;
    }

    /**
     * Check if dot is inside Matrix_coords.
     *
     * @param dot Pos with coordinates.
     * @return true if dot is in Matrix_coords, false otherwise.
     */
    [[nodiscard]] bool has(const Pos& dot) const {
        return tlhs.get_i() <= dot.get_i() < brhs.get_i() && tlhs.get_j() <= dot.get_j() < brhs.get_j();
    }
private:
    /**
     * top-left Pos of a slice rectangle.
     */
    Pos tlhs;

    /**
     * bottom-right Pos of a slice rectangle.
     */
    Pos brhs;
};


#endif //COUNTING_STARS_MATRIX_COORDS_H
