#pragma once

#include "concepts.h"

#include <ostream>

template <SiLi::_concept::Matrix V>
auto operator<<(std::ostream& os, V const& v) -> auto& {
    for (int row {0}; row < SiLi::rows_v<V>; ++row) {
        for (int col {0}; col < SiLi::cols_v<V>; ++col) {
            os << v(row, col) << " ";
        }
        os << "\n";
    }
    return os;
}
