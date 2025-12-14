#pragma once

#include "concepts.h"

#include <fmt/format.h>

template <sili::_concept::Matrix V>
struct fmt::formatter<V> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(V const& v, FormatContext& ctx) const {
        for (size_t row {0}; row < sili::rows_v<V>; ++row) {
            for (size_t col {0}; col < sili::cols_v<V>; ++col) {
                fmt::format_to(ctx.out(), "{} ", v(row, col));
            }
            fmt::format_to(ctx.out(), "\n");
        }
        return ctx.out();
    }
};
