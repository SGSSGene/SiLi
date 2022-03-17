#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>

#include <SiLi/SiLi.h>
#include <armadillo>
#include <eigen3/Eigen/Dense>
#include <random>
#include <string>

TEST_CASE("1x1 Matrix determinant (double)", "[benchmark][determinant][double]") {
    SECTION("SiLi") {
        auto m1 = SiLi::Matrix{{{double{2.}}}};

        BENCHMARK("computing determinant of matrix") {
            auto z  = det(m1);
            return z;
        };
    }
    SECTION("armadillo") {
        auto m1 = arma::Mat<double>(1, 1);
        m1(0, 0) = double{2};

        BENCHMARK("computing determinant of matrix") {
            auto z  = det(m1);
            return z;
        };
    }
    SECTION("Eigen3") {
        using Matrix = Eigen::Matrix<double, 1, 1, 0, 1, 1>;
        auto m1 = Matrix{};
        m1(0, 0) = double{2};

        BENCHMARK("computing determinant of matrix") {
            auto z  = m1.determinant();
            return z;
        };
    }
}

TEST_CASE("2x2 Matrix determinant (double)", "[benchmark][determinant][double]") {
    SECTION("SiLi") {
        auto m1 = SiLi::Matrix{{{double{2}, double{3}},
                                 {double{4}, double{5}}}};

        BENCHMARK("computing determinant of matrix") {
            auto z = det(m1);
            return z;
        };
    }
    SECTION("armadillo") {
        auto m1 = arma::Mat<double>(2, 2);
        m1 = {{double{2}, double{3}},
              {double{4}, double{5}}};

        BENCHMARK("computing determinant of matrix") {
            auto z  = det(m1);
            return z;
        };
    }
    SECTION("Eigen3") {
        using Matrix = Eigen::Matrix<double, 2, 2, 0, 2, 2>;
        auto m1 = Matrix{};
        m1(0, 0) = double{2};
        m1(0, 1) = double{3};
        m1(1, 0) = double{4};
        m1(1, 1) = double{5};

        BENCHMARK("computing determinant of matrix") {
            auto z  = m1.determinant();
            return z;
        };
    }
}

TEST_CASE("3x3 Matrix determinant (double)", "[benchmark][determinant][double]") {
    SECTION("SiLi") {
        auto m1 = SiLi::Matrix{{{double{  2}, double{  3}, double{  4}},
                                 {double{  4}, double{  5}, double{  5}},
                                 {double{100}, double{200}, double{300}}}};


        BENCHMARK("computing determinant of matrix") {
            auto z  = det(m1);
            return z;
        };
    }
    SECTION("armadillo") {
        auto m1 = arma::Mat<double>(3, 3);
        m1 = {{double{  2}, double{  3}, double{  4}},
              {double{  4}, double{  5}, double{  5}},
              {double{100}, double{200}, double{300}}};

        BENCHMARK("computing determinant of matrix") {
            auto z  = det(m1);
            return z;
        };
    }
    SECTION("Eigen3") {
        using Matrix = Eigen::Matrix<double, 3, 3, 0, 3, 3>;
        auto m1 = Matrix{};
        m1(0, 0) = double{2};
        m1(0, 1) = double{3};
        m1(0, 2) = double{4};
        m1(1, 0) = double{4};
        m1(1, 1) = double{5};
        m1(1, 2) = double{5};
        m1(2, 0) = double{100};
        m1(2, 1) = double{200};
        m1(2, 2) = double{300};

        BENCHMARK("computing determinant of matrix") {
            auto z  = m1.determinant();
            return z;
        };
    }
}

TEST_CASE("4x4 Matrix determinant (double)", "[benchmark][determinant][double]") {
    constexpr int N = 4;
    SECTION("SiLi") {
        auto m1 = SiLi::Matrix<N, N, double>{};

        auto gen = std::mt19937{N};
        auto dist = std::uniform_real_distribution<double>{-1000., 1000.};
        for (int row{0}; row < N; ++row) {
            for (int col{0}; col < N; ++col) {
                m1(row, col) = dist(gen);
            }
        }

        BENCHMARK("computing determinant of matrix") {
            auto z  = det(m1);
            return z;
        };
    }
    SECTION("armadillo") {
        auto m1 = arma::Mat<double>(N, N);

        auto gen = std::mt19937{N};
        auto dist = std::uniform_real_distribution<double>{-1000., 1000.};
        for (int row{0}; row < N; ++row) {
            for (int col{0}; col < N; ++col) {
                m1(row, col) = dist(gen);
            }
        }

        BENCHMARK("computing determinant of matrix") {
            auto z  = det(m1);
            return z;
        };
    }
    SECTION("Eigen3") {
        using Matrix = Eigen::Matrix<double, N, N, 0, N, N>;
        auto m1 = Matrix{};

        auto gen = std::mt19937{N};
        auto dist = std::uniform_real_distribution<double>{-1000., 1000.};
        for (int row{0}; row < N; ++row) {
            for (int col{0}; col < N; ++col) {
                m1(row, col) = dist(gen);
            }
        }

        BENCHMARK("computing determinant of matrix") {
            auto z  = m1.determinant();
            return z;
        };
    }
}

TEST_CASE("5x5 Matrix determinant (double)", "[benchmark][determinant][double]") {
    constexpr int N = 5;
    SECTION("SiLi") {
        auto m1 = SiLi::Matrix<N, N, double>{};

        auto gen = std::mt19937{N};
        auto dist = std::uniform_real_distribution<>{-1000., 1000.};
        for (int row{0}; row < N; ++row) {
            for (int col{0}; col < N; ++col) {
                m1(row, col) = dist(gen);
            }
        }

        BENCHMARK("computing determinant of matrix") {
            auto z  = det(m1);
            return z;
        };
    }
    SECTION("armadillo") {
        auto m1 = arma::Mat<double>(N, N);

        auto gen = std::mt19937{N};
        auto dist = std::uniform_real_distribution<>{-1000., 1000.};
        for (int row{0}; row < N; ++row) {
            for (int col{0}; col < N; ++col) {
                m1(row, col) = dist(gen);
            }
        }

        BENCHMARK("computing determinant of matrix") {
            auto z  = det(m1);
            return z;
        };
    }
    SECTION("Eigen3") {
        using Matrix = Eigen::Matrix<double, N, N, 0, N, N>;
        auto m1 = Matrix{};

        auto gen = std::mt19937{N};
        auto dist = std::uniform_real_distribution<double>{-1000., 1000.};
        for (int row{0}; row < N; ++row) {
            for (int col{0}; col < N; ++col) {
                m1(row, col) = dist(gen);
            }
        }

        BENCHMARK("computing determinant of matrix") {
            auto z  = m1.determinant();
            return z;
        };
    }
}

TEST_CASE("10x10 Matrix determinant (double)", "[benchmark][determinant][double]") {
    constexpr int N = 10;
    SECTION("SiLi") {
        auto m1 = SiLi::Matrix<N, N, double>{};

        auto gen = std::mt19937{N};
        auto dist = std::uniform_real_distribution<>{-1000., 1000.};
        for (int row{0}; row < N; ++row) {
            for (int col{0}; col < N; ++col) {
                m1(row, col) = dist(gen);
            }
        }

        BENCHMARK("computing determinant of matrix") {
            auto z  = det(m1);
            return z;
        };
    }
    SECTION("armadillo") {
        auto m1 = arma::Mat<double>(N, N);

        auto gen = std::mt19937{N};
        auto dist = std::uniform_real_distribution<>{-1000., 1000.};
        for (int row{0}; row < N; ++row) {
            for (int col{0}; col < N; ++col) {
                m1(row, col) = dist(gen);
            }
        }

        BENCHMARK("computing determinant of matrix") {
            auto z  = det(m1);
            return z;
        };
    }
    SECTION("Eigen3") {
        using Matrix = Eigen::Matrix<double, N, N, 0, N, N>;
        auto m1 = Matrix{};

        auto gen = std::mt19937{N};
        auto dist = std::uniform_real_distribution<double>{-1000., 1000.};
        for (int row{0}; row < N; ++row) {
            for (int col{0}; col < N; ++col) {
                m1(row, col) = dist(gen);
            }
        }

        BENCHMARK("computing determinant of matrix") {
            auto z  = m1.determinant();
            return z;
        };
    }
}

TEST_CASE("20x20 Matrix determinant (double)", "[benchmark][determinant][double]") {
    constexpr int N = 20;
    SECTION("SiLi") {
        auto m1 = SiLi::Matrix<N, N, double>{};

        auto gen = std::mt19937{N};
        auto dist = std::uniform_real_distribution<>{-1000., 1000.};
        for (int row{0}; row < N; ++row) {
            for (int col{0}; col < N; ++col) {
                m1(row, col) = dist(gen);
            }
        }

        BENCHMARK("computing determinant of matrix") {
            auto z  = det(m1);
            return z;
        };
    }
    SECTION("armadillo") {
        auto m1 = arma::Mat<double>(N, N);

        auto gen = std::mt19937{N};
        auto dist = std::uniform_real_distribution<>{-1000., 1000.};
        for (int row{0}; row < N; ++row) {
            for (int col{0}; col < N; ++col) {
                m1(row, col) = dist(gen);
            }
        }

        BENCHMARK("computing determinant of matrix") {
            auto z  = det(m1);
            return z;
        };
    }
    SECTION("Eigen3") {
        using Matrix = Eigen::Matrix<double, N, N, 0, N, N>;
        auto m1 = Matrix{};

        auto gen = std::mt19937{N};
        auto dist = std::uniform_real_distribution<double>{-1000., 1000.};
        for (int row{0}; row < N; ++row) {
            for (int col{0}; col < N; ++col) {
                m1(row, col) = dist(gen);
            }
        }

        BENCHMARK("computing determinant of matrix") {
            auto z  = m1.determinant();
            return z;
        };
    }
}

TEST_CASE("50x50 Matrix determinant (double)", "[benchmark][determinant][double]") {
    constexpr int N = 50;
    SECTION("SiLi") {
        auto m1 = SiLi::Matrix<N, N, double>{};

        auto gen = std::mt19937{N};
        auto dist = std::uniform_real_distribution<>{-1000., 1000.};
        for (int row{0}; row < N; ++row) {
            for (int col{0}; col < N; ++col) {
                m1(row, col) = dist(gen);
            }
        }

        BENCHMARK("computing determinant of matrix") {
            auto z  = det(m1);
            return z;
        };
    }
    SECTION("armadillo") {
        auto m1 = arma::Mat<double>(N, N);

        auto gen = std::mt19937{N};
        auto dist = std::uniform_real_distribution<>{-1000., 1000.};
        for (int row{0}; row < N; ++row) {
            for (int col{0}; col < N; ++col) {
                m1(row, col) = dist(gen);
            }
        }

        BENCHMARK("computing determinant of matrix") {
            auto z  = det(m1);
            return z;
        };
    }
    SECTION("Eigen3") {
        using Matrix = Eigen::Matrix<double, N, N, 0, N, N>;
        auto m1 = Matrix{};

        auto gen = std::mt19937{N};
        auto dist = std::uniform_real_distribution<double>{-1000., 1000.};
        for (int row{0}; row < N; ++row) {
            for (int col{0}; col < N; ++col) {
                m1(row, col) = dist(gen);
            }
        }

        BENCHMARK("computing determinant of matrix") {
            auto z  = m1.determinant();
            return z;
        };
    }
}

TEST_CASE("100x100 Matrix determinant (double)", "[benchmark][determinant][double]") {
    constexpr int N = 100;
    SECTION("SiLi") {
        auto m1 = SiLi::Matrix<N, N, double>{};

        auto gen = std::mt19937{N};
        auto dist = std::uniform_real_distribution<>{-1000., 1000.};
        for (int row{0}; row < N; ++row) {
            for (int col{0}; col < N; ++col) {
                m1(row, col) = dist(gen);
            }
        }

        BENCHMARK("computing determinant of matrix") {
            auto z  = det(m1);
            return z;
        };
    }
    SECTION("armadillo") {
        auto m1 = arma::Mat<double>(N, N);

        auto gen = std::mt19937{N};
        auto dist = std::uniform_real_distribution<>{-1000., 1000.};
        for (int row{0}; row < N; ++row) {
            for (int col{0}; col < N; ++col) {
                m1(row, col) = dist(gen);
            }
        }

        BENCHMARK("computing determinant of matrix") {
            auto z  = det(m1);
            return z;
        };
    }
    SECTION("Eigen3") {
        using Matrix = Eigen::Matrix<double, N, N, 0, N, N>;
        auto m1 = Matrix{};

        auto gen = std::mt19937{N};
        auto dist = std::uniform_real_distribution<double>{-1000., 1000.};
        for (int row{0}; row < N; ++row) {
            for (int col{0}; col < N; ++col) {
                m1(row, col) = dist(gen);
            }
        }

        BENCHMARK("computing determinant of matrix") {
            auto z  = m1.determinant();
            return z;
        };
    }
}
