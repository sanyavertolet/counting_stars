/**
 * File containing Matrix_coords class implementation.
 *
 * @author sanyavertolet
 */

#include "Matrix_coords.h"

Pos Matrix_coords::get_tlhs() const {
    return tlhs;
}

Pos Matrix_coords::get_brhs() const {
    return brhs;
}

bool Matrix_coords::has(const Pos& dot) const {
    bool is_top_ok = tlhs.get_i() <= dot.get_i();
    bool is_left_ok = tlhs.get_j() <= dot.get_j();
    bool is_bottom_ok = dot.get_i() <= brhs.get_i() || brhs.get_i() == -1;
    bool is_right_ok = dot.get_j() <= brhs.get_j() || brhs.get_j() == -1;
    return is_top_ok && is_bottom_ok && is_left_ok && is_right_ok;
}

std::string to_string(const Matrix_coords& coords) {
    return "[" + to_string(coords.get_tlhs()) + " - " + to_string(coords.get_brhs()) + "]";
}