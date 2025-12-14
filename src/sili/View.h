#pragma once

#include "concepts.h"

namespace sili {

/*! Represents a view onto a matrix
 *
 * Fulfills the _concept::Matrix concept.
 *
 * If _rows or _cols is 1 it fulfills the _concept::Vector concept.
 *
 * \caption Template Parameters
 * \param _rows number of rows of the view, must be larger or equal to zero
 * \param _cols number of columns of the view, must be larger or equal to zero
 * \param _stride length of the stride
 * \param T     type of the elements
 * \param _transposed indicates if index access of _rows and _cols should be inverted to simulate transpose access
 *
 * * \caption Methods
 * \param data() returns pointer to the underlying data structure
 * \param m(row,col) access element at ``row`` and ``col``

 */

template<size_t _rows, size_t _cols, size_t _stride, typename T, bool _transposed> requires (_rows >= 0 and _cols >= 0 and _stride >= 0)
class View<_rows, _cols, _stride, T, _transposed> {
    T& mData;
public:
    using value_t = T;
    static constexpr size_t Rows       = _rows;
    static constexpr size_t Cols       = _cols;
    static constexpr size_t Stride     = _stride;
    static constexpr bool   Transposed = _transposed;

    constexpr View(T* _data)
        : mData{*_data}
    {};

    constexpr View(Matrix<_rows, _cols, T> matrix)
        : mData{*matrix.data()}
    {};

    View(View& v)
        : mData{v.mData}
    {}

    View(View const& v) = delete;

    constexpr auto data() -> T* {
        return &mData;
    }

    constexpr auto data() const -> T const* {
        return &mData;
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


    constexpr auto operator=(T const& s) -> View& {
        for_each_constexpr<View>([&]<size_t row, size_t col>() constexpr {
            at<row, col>() = s;
        });
        return *this;
    }
    template <_concept::Matrix V>
    constexpr auto operator=(V const& v) -> View& requires (Rows == V::Rows and Cols == V::Cols) {
        for_each_constexpr<View>([&]<size_t row, size_t col>() constexpr {
            at<row, col>() = v.template at<row, col>();
        });
        return *this;
    }


};

template <size_t _rows, size_t _cols, typename T>
View(Matrix<_rows, _cols, T>&) -> View<_rows, _cols, _cols, T, false>;

template <size_t _rows, size_t _cols, typename T>
View(Matrix<_rows, _cols, T> const&) -> View<_rows, _cols, _cols, T const, false>;

}
