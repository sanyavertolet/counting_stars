/**
 * Header containing Matrix_coords class declaration.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_MATRIX_COORDS_H
#define COUNTING_STARS_MATRIX_COORDS_H

#include <utility>

#include "../../Pos/Pos.h"

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
     * Constructor from one Pos.
     * @param pos single Pos.
     */
    explicit Matrix_coords(const Pos& pos): tlhs(pos), brhs(pos) { }

    /**
     * Constructor from two Pos.
     * @param tl top-left Pos.
     * @param br bottom-right Pos.
     */
    explicit Matrix_coords(Pos tl, Pos br): tlhs(std::move(tl)), brhs(std::move(br)) { }

    /**
     * Constructor from two StringInt.
     * @param i row index.
     * @param j column index.
     */
    explicit Matrix_coords(const StringInt& i, const StringInt& j): tlhs({i, j}), brhs({i, j}) { }

    /**
     * Constructor from four StringInt.
     *
     * @param t top index.
     * @param l left index.
     * @param b bottom index.
     * @param r right index.
     */
    Matrix_coords(const StringInt& t, const StringInt& l, const StringInt& b, const StringInt& r):
            tlhs({t, l}), brhs({b, r}) { }

    /**
     * tlhs getter.
     *
     * @return tlhs.
     */
    [[nodiscard]] Pos get_tlhs() const;

    /**
     * brhs getter.
     *
     * @return brhs.
     */
    [[nodiscard]] Pos get_brhs() const;

    /**
     * Check if dot is inside Matrix_coords.
     *
     * @param dot Pos with coordinates.
     * @return true if dot is in Matrix_coords, false otherwise.
     */
    [[nodiscard]] bool has(const Pos& dot) const;
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

/**
 * Cast Matrix_coords to std::string.
 * @param coords Matrix_coords.
 * @return string representation of coords.
 */
std::string to_string(const Matrix_coords& coords);

#endif //COUNTING_STARS_MATRIX_COORDS_H
