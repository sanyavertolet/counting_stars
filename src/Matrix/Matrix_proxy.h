/**
 * Header containing Matrix_proxy class declaration and implementation.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_MATRIX_PROXY_H
#define COUNTING_STARS_MATRIX_PROXY_H

#include "../Pos/Pos.h"

#include "Coords/Matrix_coords.h"
#include "Coords/Matrix_column_coord.h"
#include "Coords/Matrix_row_coord.h"

template<typename TValue>
class Matrix;

enum class Matrix_proxy_type {
    ROW,
    COLUMN,
    RECTANGLE,
};

template<typename TMatrixValue>
class Matrix_proxy {
public:
    /**
     * Constructor for row slice.
     *
     * @param m matrix to point to.
     * @param coords Matrix_row_coord.
     */
    Matrix_proxy(Matrix<TMatrixValue>* m, const Matrix_row_coord& coords):
            type(Matrix_proxy_type::ROW), matrix(m), from(coords.get_row_index(), 0), to(coords.get_row_index(), m->get_dim().get_j()) {
        matrix->add_proxy(this);
    }

    /**
     * Constructor for column slice.
     *
     * @param m matrix to point to.
     * @param coords Matrix_column_coord.
     */
    Matrix_proxy(Matrix<TMatrixValue>* m, const Matrix_column_coord& coords):
            type(Matrix_proxy_type::COLUMN), matrix(m), from(0, coords.get_column_index()), to(m->get_dim().get_i(), coords.get_column_index()) {
        matrix->add_proxy(this);
    }

    /**
     * Constructor for rectangle slice.
     *
     * @param m matrix to point to.
     * @param coords Matrix_coords.
     */
    Matrix_proxy(Matrix<TMatrixValue>* m, const Matrix_coords& coords):
            type(Matrix_proxy_type::RECTANGLE), matrix(m), from(coords.get_tlhs()), to(coords.get_brhs()) {
        matrix->add_proxy(this);
        if (from.get_i() == -1) {
            from.set_i(0);
        }
        if (from.get_j() == -1) {
            from.set_j(0);
        }
        if (to.get_i() == -1) {
            to.set_i(m->get_dim().get_i() - 1);
        }
        if (to.get_j() == -1) {
            to.set_j(m->get_dim().get_j() - 1);
        }
    }

    /**
     * Unlink proxy from matrix.
     */
    void unlink() {
        matrix = nullptr;
    }

    /**
     * dim getter.
     *
     * @return dim of a given slice.
     */
    Pos get_dim() const {
        if (matrix == nullptr) {
            throw NullPointerException();
        }
        return {abs(to.get_i() - from.get_i() + 1), abs(to.get_j() - from.get_j() + 1)};
    }

    std::map<StringInt, TMatrixValue> get_values_as_map() const {
        if (matrix == nullptr) {
            throw NullPointerException();
        }
        switch (type) {
            case Matrix_proxy_type::ROW:
                return matrix->get_row_values(from.get_i());
            case Matrix_proxy_type::COLUMN:
                return matrix->get_column_values(from.get_j());
            case Matrix_proxy_type::RECTANGLE:
                throw IllegalStateException("Cannot get rectangle slice values as std::map");
        }
    }

    /**
     * @return precision of matrix.
     */
    TMatrixValue get_precision() const {
        if (matrix == nullptr) {
            throw NullPointerException();
        }
        return matrix->get_precision();
    }

    /**
     * Access operator for a row/column slice.
     *
     * @param index index of required element.
     * @return element of this Matrix_proxy on position index.
     */
    TMatrixValue& operator()(const StringInt& idx) {
        if (matrix == nullptr) {
            throw NullPointerException();
        }
        switch (type) {
            case Matrix_proxy_type::ROW:
                return matrix->operator()({from.get_i(), idx});
            case Matrix_proxy_type::COLUMN:
                return matrix->operator()({idx, from.get_j()});
            case Matrix_proxy_type::RECTANGLE:
                throw IllegalStateException("Cannot get element of a rectangle slice by single coordinate.");
        }
    }

    /**
     * Access operator for rectangle slice from one Pos.
     *
     * @param index index of required element.
     * @return element of this Matrix_proxy on position index.
     */
    TMatrixValue& operator()(const Pos& pos) {
        if (matrix == nullptr) {
            throw NullPointerException();
        }
        if (type == Matrix_proxy_type::RECTANGLE) {
            return matrix->operator()({pos.get_i() + from.get_i(), pos.get_j() + from.get_j()});
        } else {
            throw IllegalStateException("Cannot get element of a row/column slice by two coordinates.");
        }
    }

    /**
     * Access operator for rectangle slice from two StringInt.
     *
     * @param index index of required element.
     * @return element of this Matrix_proxy on position index.
     */
    TMatrixValue& operator()(const StringInt& i, const StringInt& j) {
        return operator()({i, j});
    }

#ifdef __COUNTING_STARS_DEBUG___

    void print_content() {
        std::cerr << "from{" << to_string(from) << "} <---|---> to {" << to_string(to) << "}" << std::endl;
        for (auto [key, value]: matrix->get_sub_matrix_values(Matrix_coords(from, to))) {
            std::cerr << "[" << to_string(key) << "] = " << value << std::endl;
        }
    }

#endif //__COUNTING_STARS_DEBUG___

    /**
     * Vector cast operator from row/column slice.
     *
     * @return slice converted to Vector.
     */
//    operator Vector<TMatrixValue>() {
//        if (matrix == nullptr) {
//            throw NullPointerException();
//        }
//        Vector<TMatrixValue> result(get_dim(), matrix->get_mass_transform(), matrix->get_precision());
//        if (type == Matrix_proxy_type::RECTANGLE) {
//            throw IllegalStateException("Cannot cast rectangle slice to Vector.");
//        } else if (type == Matrix_proxy_type::ROW) {
//            result = matrix->get_row_values();
//        } else {
//            result = matrix->get_column_values();
//        }
//        return result;
//    }

    /**
     * Matrix cast operator.
     *
     * @return slice converted to Matrix.
     */
    operator Matrix<TMatrixValue>() {
        if (matrix == nullptr) {
            throw NullPointerException();
        }
        Matrix<TMatrixValue> result(get_dim(), matrix->get_mass_transform(), matrix->get_precision());
        result = matrix->get_sub_matrix_values(Matrix_coords(from, to));
        return result;
    }

    Matrix_proxy_type get_slice_type() {
        return type;
    }

    /**
     * Proxy destructor.
     * It is needed to remove the proxy from Matrix#proxies in order to escape segfault.
     */
    ~Matrix_proxy() {
        if (matrix != nullptr) {
            matrix->remove_proxy(this);
        }
    }
private:
    /**
     * Matrix pointer.
     */
    Matrix<TMatrixValue>* matrix;

    /**
     * Top-left Pos of a slice.
     */
    Pos from;

    /**
     * Bottom-left Pos of a slice.
     */
    Pos to;

    /**
     * Type of a slice.
     */
    Matrix_proxy_type type;
};

#endif //COUNTING_STARS_MATRIX_PROXY_H
