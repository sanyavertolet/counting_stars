/**
 * Header containing Matrix class declaration.
 *
 * @author sanyavertolet
 */

#ifndef COUNTING_STARS_MATRIX_H
#define COUNTING_STARS_MATRIX_H

#include <unordered_map>
#include <set>
#include <utility>
#include <sstream>

#include "../exceptions/exceptions.h"
#include "../StringInt/StringInt.h"
#include "../Vector/Vector.h"

#include "Coords/Matrix_coords.h"
#include "Coords/Matrix_column_coord.h"
#include "Coords/Matrix_row_coord.h"

#include "Matrix_proxy.h"

#include "../Pos/Pos.h"


/**
 * Class that defined sparse Matrix.
 *
 * @tparam TValue type of stored data.
 * @param dim Pos of maximum row and column number.
 * @param precision value defining a zero - everything that is less this value is considered to be zero.
 */
template<typename TValue>
class Matrix {
public:
    /**
     * Default constructor.
     */
    Matrix() : dim(1000, 1000), mass_transform(0), data({}), precision(0) { }

    /**
     * Constructor for all the cases.
     *
     * @param max_position Pos of maximum row and column number.
     * @param default_val value that is considered to be assigned to all the stored values by default.
     * @param required_precision value defining a zero - everything that is less this value is considered to be zero.
     */
    explicit Matrix(Pos max_position, TValue default_val = 0, TValue required_precision = 0) :
    dim(std::move(max_position)), mass_transform(default_val), precision(required_precision), data({}) { }

    /**
     * Copy constructor.
     *
     * @param rhs instance to copy.
     */
    Matrix(Matrix& rhs) : dim(rhs.dim), precision(rhs.precision), mass_transform(rhs.mass_transform), data(rhs.data) { }

    /**
     * Move constructor.
     *
     * @param rhs instance to move.
     */
    Matrix(Matrix&& rhs) noexcept :
    dim(std::move(rhs.dim)), precision(std::move(rhs.precision)), mass_transform(std::move(rhs.mass_transform)), data(std::move(rhs.data)) {
        rhs.dim = Pos();
        rhs.precision = TValue();
        mass_transform = TValue();
        data = {};
    }

    explicit Matrix(const char* file_path): precision(0), mass_transform(0), data({}) {
        // todo: depends on Matrix parser.
        throw FileNotFoundException(file_path);
    }

    /**
     * Matrix destructor.
     * It is necessary to mark matrix as deleted in all proxies that point to this matrix while deleting the matrix.
     */
    ~Matrix() {
        for (auto proxy: proxies) {
            proxy->unlink();
        }
    }

    /**
     * Copy operator.
     *
     * @param rhs instance to copy.
     * @return this Matrix filled with rhs fields.
     */
    Matrix& operator=(const Matrix& rhs) {
        Matrix tmp(rhs);
        std::swap(dim, tmp.dim);
        std::swap(precision, tmp.precision);
        std::swap(mass_transform, tmp.mass_transform);
        std::swap(data, tmp.data);
        return *this;
    }

    /**
     * Move operator.
     *
     * @param rhs instance to move.
     * @return this Matrix filled with rhs fields.
     */
    Matrix& operator=(Matrix&& rhs) noexcept {
        dim = std::move(rhs.dim);
        rhs.dim = Pos();
        precision = std::move(rhs.precision);
        rhs.precision = TValue();
        mass_transform = std::move(rhs.mass_transform);
        rhs.mass_transform = TValue();
        data = std::move(rhs.data);
        rhs.data = {};
    }

    /**
     * Move operator.
     *
     * @param rhs instance to move.
     * @return this Matrix filled with rhs fields.
     */
    Matrix& operator=(std::unordered_map<Pos, TValue>&& rhs) noexcept {
        data = std::move(rhs);
        rhs = {};
    }

    /**
     * Change matrix dimension.
     *
     * @param new_dim
     * @param swallow_exception
     * @throws OutOfRangeException if new matrix dimension leads to possible data loss.
     */
    void set_dim(const Pos& new_dim, bool swallow_exception = false) {
        if (!swallow_exception && new_dim.get_i() < dim.get_i() || new_dim.get_j() < dim.get_j()) {
            throw OutOfRangeException("New dim is smaller by at least one coordinate.\n\tOld: " + to_string(dim) + "\n\tNew: " + to_string(new_dim));
        }
        dim = new_dim;
    }

    [[nodiscard]] Pos get_dim() const {
        return dim;
    }

    void set_precision(TValue new_precision) {
        if (new_precision < 0) {
            throw IllegalSignException("precision should not be negative.");
        }
        precision = new_precision;
    }

    TValue get_precision() const {
        return precision;
    }

    TValue get_mass_transform() const {
        return mass_transform;
    }

    [[nodiscard]] StringInt get_size() const {
        return data.size();
    }

    /**
     * Friend operator that prints Matrix to std::ostream.
     *
     * @param os output stream.
     * @param x Matrix to print.
     * @return os.
     */
    friend std::ostream& operator<<(std::ostream& os, Matrix const& x) {
        os << to_string(x);
        return os;
    }

    /**
     * Friend operator that reads Matrix from std::istream.
     *
     * @param is input stream.
     * @param x Matrix to read to.
     * @return is.
     */
    friend std::istream& operator>>(std::istream& is, Matrix& x);

    /**
     * Eq operator.
     *
     * @tparam TValueLeft type of data of left operand.
     * @tparam TValueRight type of data of right operand.
     * @param lhs left operand.
     * @param rhs right operand.
     * @return true of lhs and rhs are equal, false otherwise.
     */
    template<typename TValueLeft, typename TValueRight>
    friend bool operator==(const Matrix<TValueLeft> &lhs, const Matrix<TValueRight> &rhs) {
        if (lhs.dim != rhs.dim || lhs.get_size() != rhs.get_size() || lhs.mass_transform != rhs.mass_transform) {
            return false;
        }
        auto predicate = [](auto lhs, auto rhs) {
            return decltype(lhs + rhs)(lhs) == decltype(lhs + rhs)(rhs);
        };
        return std::equal(lhs.data.begin(), lhs.data.end(), rhs.data.begin(), predicate);
    }

    /**
     * Neq operator.
     *
     * @tparam TValueLeft type of data of left operand.
     * @tparam TValueRight type of data of right operand.
     * @param lhs left operand.
     * @param rhs right operand.
     * @return true of lhs and rhs are not equal, false otherwise.
     */
    template<typename TValueLeft, typename TValueRight>
    friend bool operator!=(const Matrix<TValueLeft> &lhs, const Matrix<TValueRight> &rhs) {
        return !(lhs == rhs);
    }

    /**
     * Unary minus operator.
     *
     * @return Matrix with items with inverted signs.
     */
    Matrix operator-() {
        delete_zero_elements();
        Matrix<TValue> result(*this);
        for(auto& [key, value]: result.data) {
            value = -value;
        }
        mass_transform = -mass_transform;
        return result;
    }

    /**
     * Transposition operator.
     *
     * @return transposed Matrix.
     */
    Matrix operator~() {
        Matrix transposed(~dim);
        for(auto [key, value] : data) {
            transposed.data.insert(~key, value);
        }
        return transposed;
    }

    /**
     * Access operator.
     *
     * @param pos Pos index of required element.
     * @return element of this Matrix on position pos.
     */
    TValue& operator()(Pos pos) {
        delete_zero_elements();
        if (!(pos < dim)) {
            throw OutOfRangeException("OutOfRangeException");
        }
        if (data.find(pos) == data.end()) {
            data[pos] = mass_transform;
        }
        if (data[pos] <= precision) {
            data[pos] = 0;
        }
        return data[pos];
    }

    /**
     * Access operator.
     *
     * @param i index of a row.
     * @param j index of a column.
     * @return element of this Matrix on position {i, j}.
     */
    TValue& operator()(const StringInt& i, const StringInt& j) {
        return operator()({i, j});
    }

    /**
     * Slice read operator.
     *   todo: implement
     *
     * @param coords Matrix_coords.
     * @return slice of this Matrix on positions coords.
     * /
     * const Matrix& operator[](const Matrix_coords& coords) const { }
     */

    /**
     * Slice write operator.
     *
     * @param coords Matrix_coords.
     * @return slice of this Matrix on positions coords.
     */
    Matrix_proxy<TValue> operator[](const Matrix_coords& coords) {
        if (coords.has(dim)) {
            throw OutOfRangeException();
        }
        return Matrix_proxy<TValue>(this, coords);
    }

    /**
     * Slice operator.
     *
     * @param row Matrix_row_coords.
     * @return slice of this Matrix on positions row.
     */
    Matrix_proxy<TValue> operator[](const Matrix_row_coord& row) {
        if (row.get_row_index() < 0 || dim.get_j() <= row.get_row_index()) {
            throw OutOfRangeException();
        }
        return Matrix_proxy<TValue>(this, row);
    }

    /**
     * Slice operator.
     *
     * @param column Matrix_column_coord.
     * @return slice of this Matrix on positions column.
     */
    Matrix_proxy<TValue> operator[](const Matrix_column_coord& column) {
        if (column.get_column_index() < 0 || dim.get_i() <= column.get_column_index()) {
            throw OutOfRangeException();
        }
        return Matrix_proxy<TValue>(this, column);
    }

    /**
     * Plus and assign operator.
     *
     * @tparam TValueRight type of data of right operand.
     * @param rhs right operand.
     * @return this Matrix, increased by rhs.
     */
    template<typename TValueRight>
    auto& operator+=(const Matrix<TValueRight> &rhs) {
        *this = (*this + rhs);
        return *this;
    }

    /**
     * Minus and assign operator.
     *
     * @tparam TValueRight type of data of right operand.
     * @param rhs right operand.
     * @return this Matrix, decreased by rhs.
     */
    template<typename TValueRight>
    auto& operator-=(const Matrix<TValueRight> &rhs) {
        *this = (*this - rhs);
        return *this;
    }

    /**
     * Multiply and assign operator.
     *
     * @tparam TValueRight type of data of right operand.
     * @param rhs right operand.
     * @return this Matrix, multiplied by rhs.
     */
    template<typename TValueRight>
    auto& operator*=(Matrix<TValueRight> rhs) {
        *this = (*this * rhs);
        return *this;
    }

    /**
     * Plus operator.
     *
     * @tparam TValueLeft type of data of left operand.
     * @tparam TValueRight type of data of right operand.
     * @param lhs left operand.
     * @param rhs right operand.
     * @return sum of lhs and rhs.
     */
    template<typename TValueLeft, typename TValueRight>
    friend auto operator+(const Matrix<TValueLeft> &lhs, const Matrix<TValueRight> &rhs) {
        if (lhs.dim != rhs.dim) {
            throw IllegalDimException(lhs.dim, rhs.dim);
        }
        Matrix<decltype(TValueLeft() + TValueRight())> result(lhs.dim, lhs.mass_transform + rhs.mass_transform);
        for (auto &[key, value]: lhs.data) {
            result.data[key] = value;
        }
        for (auto &[key, value]: rhs.data) {
            if (result.data.find(key) != result.data.end()) {
                result.data[key] += value;
            } else {
                result.data[key] = value;
            }
        }
        return result;
    }

    /**
     * Minus operator.
     *
     * @tparam TValueLeft type of data of left operand.
     * @tparam TValueRight type of data of right operand.
     * @param lhs left operand.
     * @param rhs right operand.
     * @return lhs, decreased by rhs.
     */
    template<typename TValueLeft, typename TValueRight>
    friend auto operator-(const Matrix<TValueLeft> &lhs, const Matrix<TValueRight> &rhs) {
        if (lhs.dim != rhs.dim) {
            throw IllegalDimException(lhs.dim, rhs.dim);
        }
        Matrix<decltype(TValueLeft() + TValueRight())> result(lhs.dim, lhs.mass_transform - rhs.mass_transform);
        for (auto &[key, value]: lhs.data) {
            result.data[key] = value;
        }
        for (auto &[key, value]: rhs.data) {
            if (result.data.find(key) != result.data.end()) {
                result.data[key] -= value;
            } else {
                result.data[key] = -value;
            }
        }
        result.delete_zero_elements();
        return result;
    }

    /**
     * Multiply operator.
     *
     * @tparam TValueLeft type of data of left operand.
     * @tparam TValueRight type of data of right operand.
     * @param lhs left operand.
     * @param rhs right operand.
     * @return lhs, multiplied by rhs.
     */
    template<typename TValueLeft, typename TValueRight>
    friend auto operator*(Matrix<TValueLeft> lhs, Matrix<TValueRight> rhs) {
        if (lhs.dim.get_j() != rhs.dim.get_i()) {
            throw IllegalDimException(lhs.dim, rhs.dim);
        }
        lhs.apply_mass_transform();
        rhs.apply_mass_transform();
        Matrix<decltype(TValueLeft() + TValueRight())> result({ lhs.dim.get_i(), rhs.dim.get_j() });
        for (StringInt i = 0; i < lhs.dim.get_i(); ++i) {
            for (StringInt j = 0; j < rhs.dim.get_j(); ++j) {
                decltype(TValueLeft() + TValueRight()) cell_result(0);
                for (StringInt k = 0; k < lhs.dim.get_j(); ++k) {
                    cell_result += lhs.data[{i, k}] * rhs.data[{k, j}];
                }
                result.data[{i, j}] = cell_result;
            }
        }
        result.delete_zero_elements();
        return result;
    }

    /**
     * Mass plus operator.
     *
     * @tparam TValueLeft type of data of left operand.
     * @tparam TValueRight type of rhs - primitive probably.
     * @param lhs left operand.
     * @param rhs right operand.
     * @return lhs where each element is increased by rhs.
     */
    template<typename TValueLeft, typename TValueRight>
    friend auto operator+(Matrix<TValueLeft> lhs, const TValueRight& rhs) {
        lhs.mass_transform += rhs;
        for (auto &[key, value] : lhs.data) {
            value += rhs;
        }
        lhs.delete_zero_elements();
        return lhs;
    }

    /**
     * Mass minus operator.
     *
     * @tparam TValueLeft type of data of left operand.
     * @tparam TValueRight type of rhs - primitive probably.
     * @param lhs left operand.
     * @param rhs right operand.
     * @return lhs where each element is decreased by rhs.
     */
    template<typename TValueLeft, typename TValueRight>
    friend auto operator-(Matrix<TValueLeft> lhs, const TValueRight& rhs) {
        lhs.mass_transform -= rhs;
        for (auto &[key, value] : lhs.data) {
            value -= rhs;
        }
        lhs.delete_zero_elements();
        return lhs;
    }

    /**
     * Mass multiply operator.
     *
     * @tparam TValueLeft type of data of left operand.
     * @tparam TValueRight type of rhs - primitive probably.
     * @param lhs left operand.
     * @param rhs right operand.
     * @return lhs where each element is multiplied by rhs.
     */
    template<typename TValueLeft, typename TValueRight>
    friend auto operator*(Matrix<TValueLeft> lhs, const TValueRight& rhs) {
        lhs.mass_transform *= rhs;
        for (auto &[key, value] : lhs.data) {
            value *= rhs;
        }
        lhs.delete_zero_elements();
        return lhs;
    }

    /**
     * Mass divide operator.
     *
     * @tparam TValueLeft type of data of left operand.
     * @tparam TValueRight type of rhs - primitive probably.
     * @param lhs left operand.
     * @param rhs right operand.
     * @return lhs where each element is divided by rhs.
     */
    template<typename TValueLeft, typename TValueRight>
    friend auto operator/(Matrix<TValueLeft> lhs, const TValueRight& rhs) {
        if (rhs == 0) {
            throw DivisionByZeroException();
        }
        lhs.mass_transform /= rhs;
        for (auto &[key, value] : lhs.data) {
            value /= rhs;
        }
        lhs.delete_zero_elements();
        return lhs;
    }

    /**
     * std::to_string implementation for Matrix.
     *
     * @param matrix Matrix to be converted to string.
     * @return std::string representation of matrix.
     */
    friend std::string to_string(Matrix matrix) {
        std::stringstream ss;
        std::string type_name;
        ss << "matrix " << typeid(TValue()).name() << " " << to_string(matrix.dim, false) << std::endl << std::endl;
        for (auto [key, value]: matrix.data) {
            ss << to_string(key, false) << "\t\t" <<  value << std::endl;
        }
        return ss.str();
    }

    /**
     * Get all the recorded values from row by its index.
     *
     * @param column_index index of a requested row.
     * @return r-value reference to subset of data map corresponding to requested row.
     */
    std::map<StringInt, TValue>&& get_row_values(const StringInt& row_index) const {
        std::map<StringInt, TValue> values;
        for (auto &[key, value] : data) {
            if (key.get_i() == row_index) {
                values.insert({key.get_j(), value});
            }
        }
        return std::move(values);
    }

    /**
     * Get all the recorded values from column by its index.
     *
     * @param column_index index of a requested column.
     * @return r-value reference to subset of data map corresponding to requested column.
     */
    std::map<StringInt, TValue>&& get_column_values(const StringInt& column_index) const {
        std::map<StringInt, TValue> values;
        for (auto &[key, value] : data) {
            if (key.get_j() == column_index) {
                values.insert({key.get_i(), value});
            }
        }
        return std::move(values);
    }

    /**
     * Get all the recorded values from sub-matrix.
     *
     * @param sub_matrix_coords coordinates of a sub-matrix.
     * @return r-value reference to subset of data map corresponding to requested coordinates.
     */
    std::map<Pos, const TValue&> get_sub_matrix_values(const Matrix_coords& sub_matrix_coords) const {
        std::map<Pos, const TValue&> values;
        for (auto &[key, value] : data) {
            if (sub_matrix_coords.has(key)) {
                values.insert({key, value});
            }
        }
        return values;
    }

    /**
     * Link proxy object with this Matrix.
     *
     * @param proxy Matrix_proxy pointer to add to proxies set.
     */
    void add_proxy(Matrix_proxy<TValue>* proxy) {
        proxies.insert(proxy);
    }

    /**
     * Unlink proxy object with this Matrix using erase-remove idiom.
     *
     * @param proxy Matrix_proxy pointer to remove from proxies set.
     */
    void remove_proxy(Matrix_proxy<TValue>* proxy) {
        proxies.erase(proxy);
    }
private:
    /**
     * Pos of maximum row and column number.
     */
    Pos dim;

    /**
     * Value defining a zero - everything that is less this value is considered to be zero.
     */
    TValue precision;

    /**
     * Internal value to decrease memory usage.
     * If mass operation is applied to Matrix, mass transform is changed in order not to store all [dim] elements.
     */
    TValue mass_transform;

    /**
     * Data stored as unordered map.
     *
     * key - Pos describing index of a stored value.
     * value - TValue that should be stored.
     */
    std::unordered_map<Pos, TValue> data;

    /**
     * All the proxies that are related to this matrix.
     */
   std::set<Matrix_proxy<TValue>*> proxies;

    /**
     * Internal method to perform lazy initialization of values by applying mass transform to them.
     */
    void apply_mass_transform() {
        for (StringInt i = 0; i < dim.get_i(); ++i) {
            for (StringInt j = 0; j < dim.get_j(); ++j) {
                if (data.find({i, j}) == data.end()) {
                    data[{i, j}] = mass_transform;
                }
            }
        }
        mass_transform = 0;
    }

    /**
     * Internal method to delete elements from [data] that are less than [precision].
     */
    void delete_zero_elements() {
        std::set<Pos> to_delete;
        if (mass_transform <= precision) {
            mass_transform = 0;
        }
        for (auto [key, value] : data) {
            if (value <= TValue(precision)) {
                to_delete.insert(key);
            }
        }
        for (auto key : to_delete) {
            data.erase(key);
        }
    }
};

#endif //COUNTING_STARS_MATRIX_H
