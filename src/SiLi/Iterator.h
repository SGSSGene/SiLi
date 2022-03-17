#pragma once

#include "concepts.h"

namespace SiLi {

template <_concept::Matrix V>
struct Iterator {
    V& v;
    size_t row{0};
    size_t col{0};
    auto operator++() -> auto& {
        col += 1;
        if (col >= cols_v<V>) {
            col = 0;
            row += 1;
        }
        return *this;
    }
    auto operator!=(Iterator const& _other) const -> bool {
        return row != _other.row or col != _other.col;
    }
    auto operator*() const -> auto& {
        return v(row, col);
    }

    auto operator->() const -> auto* {
        return &v(row, col);
    }
};

template <_concept::Matrix V>
auto begin(V&& v) {
    return Iterator<V>{std::forward<V>(v), 0, 0};
}
template <_concept::Matrix V>
auto end(V&& v) {
    return Iterator<V>{std::forward<V>(v), rows_v<V>, 0};
}

}
