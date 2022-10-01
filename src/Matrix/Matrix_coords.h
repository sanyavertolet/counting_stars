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
        return brhs;
    }

    /**
     * Check if dot is inside Matrix_coords.
     *
     * @param dot Pos with coordinates.
     * @return true if dot is in Matrix_coords, false otherwise.
     */
    [[nodiscard]] bool has(const Pos& dot) const {
        bool is_top_ok = tlhs.get_i() <= dot.get_i();
        bool is_left_ok = tlhs.get_j() <= dot.get_j();
        bool is_bottom_ok = dot.get_i() <= brhs.get_i() || brhs.get_i() == -1;
        bool is_right_ok = dot.get_j() <= brhs.get_j() || brhs.get_j() == -1;
        return is_top_ok && is_bottom_ok && is_left_ok && is_right_ok;
    }

    explicit operator std::string() const {
        return "[" + to_string(tlhs) + " - " + to_string(brhs) + "]";
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

std::string to_string(const Matrix_coords& coords) {
    return std::string(coords);
}

#endif //COUNTING_STARS_MATRIX_COORDS_H
