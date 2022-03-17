#pragma once

#include "concepts.h"

#include <array>

namespace SiLi {

/*! Represents a matrix
 *
 * Fulfills the _concept::Matrix concept.
 *
  * If _rows or _cols is 1 it fulfills _concept::Vector.
 *
 * \caption Template Parameters
 * \param _rows number of rows of the matrix, must be larger or equal to zero
 * \param _cols number of columns of the matrix, must be larger or equal to zero
 * \param T     type of the elements
 *
 * \caption Methods
 * \param data() returns pointer to the underlying data structure
 * \param m(row,col) access element at ``row`` and ``col``
 */
template<size_t _rows, size_t _cols, typename T> requires (_rows >= 0 and _cols >= 0)
class Matrix<_rows, _cols, T> {
    std::array<T, _cols*_rows> vals;

public:
    using value_t = T;

    static constexpr size_t  Rows       = _rows;
    static constexpr size_t  Cols       = _cols;
    static constexpr size_t  Stride     = _cols;
    static constexpr bool Transposed = false;

    constexpr Matrix() : vals{} {}

    template <typename ...S>
    constexpr Matrix(S... _values)
        : vals{std::forward<S>(_values)...}
    {}

    constexpr Matrix(T const (&values)[Rows][Cols]) {
        for (size_t row{0}; row < Rows; ++row) {
            for (size_t col{0}; col < Cols; ++col) {
                this->operator()(row, col) = values[row][col];
            }
        }
    }
    template <_concept::Matrix V>
    constexpr Matrix(V const& view) requires (V::Rows == Rows and V::Cols == Cols) {
        *this = view;
    }

    constexpr auto data() -> T* {
        return vals.data();
    }
    constexpr auto data() const -> T const* {
        return vals.data();
    }


    explicit constexpr operator T() requires (Rows == 1 and Cols == 1) {
        return get(*this, 0, 0);
    }
    explicit constexpr operator T const() const requires (Rows == 1 and Cols == 1) {
        return get(*this, 0, 0);
    }


    constexpr auto operator()(size_t row, size_t col) -> T& {
        return get(*this, row, col);
    }
    constexpr auto operator()(size_t row, size_t col) const -> T const& {
        return get(*this, row, col);
    }

    constexpr auto operator()(size_t i) -> T& requires ((Cols == 1 or Rows == 1) and Cols >= 1 and Rows >= 1) {
        return get(*this, i);
    }
    constexpr auto operator()(size_t i) const -> T const& requires ((Cols == 1 or Rows == 1) and Cols >= 1 and Rows >= 1) {
        return get(*this, i);
    }
    constexpr auto operator[](size_t i) -> T& requires ((Cols == 1 or Rows == 1) and Cols >= 1 and Rows >= 1) {
        return get(*this, i);
    }
    constexpr auto operator[](size_t i) const -> T const& requires ((Cols == 1 or Rows == 1) and Cols >= 1 and Rows >= 1) {
        return get(*this, i);
    }

    template <size_t row, size_t col>
    constexpr auto at() -> T& {
        return get<row, col>(*this);
    }
    template <size_t row, size_t col>
    constexpr auto at() const -> T const& {
        return get<row, col>(*this);
    }

    template <size_t entry>
    constexpr auto at() -> T& requires (Cols == 1 or Rows == 1) {
        return get<entry>(*this);
    }
    template <size_t entry>
    constexpr auto at() const -> T const& requires (Cols == 1 or Rows == 1) {
        return get<entry>(*this);
    }



    constexpr auto view() {
        return View<_rows, _cols, _cols, T, false>{data()};
    }
    constexpr auto view() const {
        return View<_rows, _cols, _cols, T const, false>{data()};
    }

    constexpr auto operator=(T const& s) -> Matrix& {
        for_each_constexpr<Matrix>([&]<size_t row, size_t col>() constexpr {
            at<row, col>() = s;
        });
        return *this;
    }

    template <_concept::Matrix V>
    constexpr auto operator=(V const& v) -> Matrix& requires (Rows == V::Rows and Cols == V::Cols) {
        for_each_constexpr<Matrix>([&]<size_t row, size_t col>() constexpr {
            at<row, col>() = v.template at<row, col>();
        });
        return *this;
    }
};

template <size_t rows, size_t cols, typename T>
Matrix(T const (&)[rows][cols]) -> Matrix<rows, cols, T>;

template <size_t rows, size_t cols, size_t stride, typename T, bool _transposed>
Matrix(View<rows, cols, stride, T, _transposed> const&) -> Matrix<rows, cols, std::remove_const_t<T>>;

template<size_t rows, typename T>
using Vector = Matrix<rows, 1, T>;

}
