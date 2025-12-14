#include <sili/sili.h>
#include <sili/ostream.h>
#include <sili/fmt.h>

#include <iostream>

int main() {
    // m1 is of type Matrix<3, 2, double>
    auto m1 = sili::Matrix{{{1., 0.},
                            {0., 1.},
                            {3., 4.}}};

    // m2 is of type Matrix<2, 3, double>
    auto m2 = sili::Matrix{{{1., 0., 3.},
                            {0., 1., 4.}}};

    // m3 is of type Matrix<3, 3, double>
    auto m3 = m1 * m2;

    // m4 is of type Matrix<2, 2, double>
    auto m4 = m2 * m1;

    // print matrix
    fmt::print("m1:\n{}\n\n", m1);
    fmt::print("m2:\n{}\n\n", m2);
    fmt::print("m3:\n{}\n\n", m3);
    fmt::print("m4:\n{}\n\n", m4);

    // print matrix element by element
    for (size_t row = 0; row < rows(m1); ++row) {
        for (size_t col = 0; col < cols(m1); ++col) {
            std::cout << m1(row, col) << "\n";
        }
    }

    sili::for_constexpr<0, 10>([&]<auto K>() {
        static_assert(K < 10);
        std::cout << "x:" << K << "\n";
    });
}

