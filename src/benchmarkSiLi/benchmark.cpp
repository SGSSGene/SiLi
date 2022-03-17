#include "DataGenerator.h"

template <typename T, size_t N>
void benchmarkAddition() {
    auto data = GenerateData<T, N>{};
    {
        auto [m1, m2] = data.template getMatrix<SiLi::Matrix<N, N, T>>();
        BENCHMARK("addition - SiLi") {
            auto z  = SiLi::Matrix{m1 + m2};
            return z;
        };
    }
    {
        auto [m1, m2] = data.template getMatrix(arma::Mat<T>(N, N));
        BENCHMARK("addition - armadillo") {
            auto z  = arma::Mat<T>{m1 + m2};
            return z;
        };
    }
    {
        using Matrix = Eigen::Matrix<T, N, N, 0, N, N>;
        auto [m1, m2] = data.template getMatrix<Matrix>();
        BENCHMARK("addition - Eigen3") {
            auto z  = Matrix{m1 + m2};
            return z;
        };
    }
}
template <typename T, size_t N>
void benchmarkMultiplication() {
    auto data = GenerateData<T, N>{};
    {
        auto [m1, m2] = data.template getMatrix<SiLi::Matrix<N, N, T>>();
        BENCHMARK("multiplication - SiLi") {
            auto z  = SiLi::Matrix{m1 * m2};
            return z;
        };
    }
    {
        auto [m1, m2] = data.template getMatrix(arma::Mat<T>(N, N));
        BENCHMARK("multiplication - armadillo") {
            auto z  = arma::Mat<T>{m1 * m2};
            return z;
        };
    }
    {
        using Matrix = Eigen::Matrix<T, N, N, 0, N, N>;
        auto [m1, m2] = data.template getMatrix<Matrix>();
        BENCHMARK("multiplication - Eigen3") {
            auto z  = Matrix{m1 + m2};
            return z;
        };
    }
}
template <typename T, size_t N>
void benchmarkDet() {
    auto data = GenerateData<T, N>{};
    {
        auto [m1, m2] = data.template getMatrix<SiLi::Matrix<N, N, T>>();
        BENCHMARK("determinant - SiLi") {
            auto z  = det(m1);
            return z;
        };
    }
    {
        auto [m1, m2] = data.template getMatrix(arma::Mat<T>(N, N));
        BENCHMARK("determinant - armadillo") {
            auto z  = det(m1);
            return z;
        };
    }
    {
        using Matrix = Eigen::Matrix<T, N, N, 0, N, N>;
        auto [m1, m2] = data.template getMatrix<Matrix>();
        BENCHMARK("determinant - Eigen3") {
            auto z  = m1.determinant();
            return z;
        };
    }
}
template <typename T, size_t N>
void benchmarkInv() {
    auto data = GenerateData<T, N>{};
    {
        auto [m1, m2] = data.template getMatrix<SiLi::Matrix<N, N, T>>();
        BENCHMARK("inverse - SiLi") {
            auto z  = inv(m1);
            return z;
        };
    }
    {
        auto [m1, m2] = data.template getMatrix(arma::Mat<T>(N, N));
        BENCHMARK("inverse - armadillo") {
            auto z  = arma::Mat<T>{inv(m1)};
            return z;
        };
    }
    {
        using Matrix = Eigen::Matrix<T, N, N, 0, N, N>;
        auto [m1, m2] = data.template getMatrix<Matrix>();
        BENCHMARK("inverse - Eigen3") {
            auto z  = Matrix{m1.inverse()};
            return z;
        };
    }
}



template <typename T, size_t N>
void benchmark() {
    benchmarkAddition<T, N>();
    benchmarkMultiplication<T, N>();
    if constexpr (std::is_floating_point_v<T>) {
        benchmarkDet<T, N>();
        benchmarkInv<T, N>();
    }
}


TEST_CASE("Matrix", "[benchmark]") {
    SECTION("float 1x1")   { benchmark<float,  1>(); }
    SECTION("float 2x2")   { benchmark<float,  2>(); }
    SECTION("float 3x3")   { benchmark<float,  3>(); }
    SECTION("float 4x4")   { benchmark<float,  4>(); }
    SECTION("float 5x5")   { benchmark<float,  5>(); }
    SECTION("float 10x10") { benchmark<float, 10>(); }
    SECTION("float 20x20") { benchmark<float, 20>(); }

    SECTION("double 1x1")   { benchmark<double,  1>(); }
    SECTION("double 2x2")   { benchmark<double,  2>(); }
    SECTION("double 3x3")   { benchmark<double,  3>(); }
    SECTION("double 4x4")   { benchmark<double,  4>(); }
    SECTION("double 5x5")   { benchmark<double,  5>(); }
    SECTION("double 10x10") { benchmark<double, 10>(); }
    SECTION("double 20x20") { benchmark<double, 20>(); }

    SECTION("int16 1x1")   { benchmark<int16_t,  1>(); }
    SECTION("int16 2x2")   { benchmark<int16_t,  2>(); }
    SECTION("int16 3x3")   { benchmark<int16_t,  3>(); }
    SECTION("int16 4x4")   { benchmark<int16_t,  4>(); }
    SECTION("int16 5x5")   { benchmark<int16_t,  5>(); }
    SECTION("int16 10x10") { benchmark<int16_t, 10>(); }
    SECTION("int16 20x20") { benchmark<int16_t, 20>(); }

    SECTION("int32 1x1")   { benchmark<int32_t,  1>(); }
    SECTION("int32 2x2")   { benchmark<int32_t,  2>(); }
    SECTION("int32 3x3")   { benchmark<int32_t,  3>(); }
    SECTION("int32 4x4")   { benchmark<int32_t,  4>(); }
    SECTION("int32 5x5")   { benchmark<int32_t,  5>(); }
    SECTION("int32 10x10") { benchmark<int32_t, 10>(); }
    SECTION("int32 20x20") { benchmark<int32_t, 20>(); }

    SECTION("int64 1x1")   { benchmark<int64_t,  1>(); }
    SECTION("int64 2x2")   { benchmark<int64_t,  2>(); }
    SECTION("int64 3x3")   { benchmark<int64_t,  3>(); }
    SECTION("int64 4x4")   { benchmark<int64_t,  4>(); }
    SECTION("int64 5x5")   { benchmark<int64_t,  5>(); }
    SECTION("int64 10x10") { benchmark<int64_t, 10>(); }
    SECTION("int64 20x20") { benchmark<int64_t, 20>(); }

}
