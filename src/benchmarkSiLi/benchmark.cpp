// SPDX-FileCopyrightText: 2017 Lutz Freitag + Simon Gene Gottlieb
// SPDX-License-Identifier: CC-BY-4.0

#include "DataGenerator.h"

#include <nanobench.h>


static std::string prefix;
template <typename T, size_t N>
void benchmarkAddition() {
    auto data = GenerateData<T, N>{};
    auto bench = ankerl::nanobench::Bench{};
    {
        auto [m1, m2] = data.template getMatrix<sili::Matrix<N, N, T>>();
        bench.run(prefix + "addition - sili", [&]() {
            auto z  = sili::Matrix{m1 + m2};
            ankerl::nanobench::doNotOptimizeAway(z);
        });
    }
    {
        auto [m1, m2] = data.template getMatrix(arma::Mat<T>(N, N));
        bench.run(prefix + "addition - armadillo", [&]() {
            auto z  = arma::Mat<T>{m1 + m2};
            ankerl::nanobench::doNotOptimizeAway(&z);
        });
    }
    {
        using Matrix = Eigen::Matrix<T, N, N, 0, N, N>;
        auto [m1, m2] = data.template getMatrix<Matrix>();
        bench.run(prefix + "addition - Eigen3", [&]() {
            auto z  = Matrix{m1 + m2};
            ankerl::nanobench::doNotOptimizeAway(z);
        });
    }
}
template <typename T, size_t N>
void benchmarkMultiplication() {
    auto data = GenerateData<T, N>{};
    auto bench = ankerl::nanobench::Bench{};
    {
        auto [m1, m2] = data.template getMatrix<sili::Matrix<N, N, T>>();
        bench.run(prefix + "multiplication - sili", [&]() {
            auto z  = sili::Matrix{m1 * m2};
            ankerl::nanobench::doNotOptimizeAway(z);
        });
    }
    {
        auto [m1, m2] = data.template getMatrix(arma::Mat<T>(N, N));
        bench.run(prefix + "multiplication - armadillo", [&]() {
            auto z  = arma::Mat<T>{m1 * m2};
            ankerl::nanobench::doNotOptimizeAway(&z);
        });
    }
    {
        using Matrix = Eigen::Matrix<T, N, N, 0, N, N>;
        auto [m1, m2] = data.template getMatrix<Matrix>();
        bench.run(prefix + "multiplication - Eigen3", [&]() {
            auto z  = Matrix{m1 + m2};
            ankerl::nanobench::doNotOptimizeAway(z);
        });
    }
}
template <typename T, size_t N>
void benchmarkDet() {
    auto data = GenerateData<T, N>{};
    auto bench = ankerl::nanobench::Bench{};
    {
        auto [m1, m2] = data.template getMatrix<sili::Matrix<N, N, T>>();
        bench.run(prefix + "determinant - sili", [&]() {
            auto z  = det(m1);
            ankerl::nanobench::doNotOptimizeAway(z);
        });
    }
    {
        auto [m1, m2] = data.template getMatrix(arma::Mat<T>(N, N));
        bench.run(prefix + "determinant - armadillo", [&]() {
            auto z  = det(m1);
            ankerl::nanobench::doNotOptimizeAway(&z);
        });
    }
    {
        using Matrix = Eigen::Matrix<T, N, N, 0, N, N>;
        auto [m1, m2] = data.template getMatrix<Matrix>();
        bench.run(prefix + "determinant - Eigen3", [&]() {
            auto z  = m1.determinant();
            ankerl::nanobench::doNotOptimizeAway(z);
        });
    }
}
template <typename T, size_t N>
void benchmarkInv() {
    auto data = GenerateData<T, N>{};
    auto bench = ankerl::nanobench::Bench{};
    {
        auto [m1, m2] = data.template getMatrix<sili::Matrix<N, N, T>>();
        bench.run(prefix + "inverse - sili", [&]() {
            auto z  = inv(m1);
            ankerl::nanobench::doNotOptimizeAway(z);
        });
    }
    {
        auto [m1, m2] = data.template getMatrix(arma::Mat<T>(N, N));
        bench.run(prefix + "inverse - armadillo", [&]() {
            auto z  = arma::Mat<T>{inv(m1)};
            ankerl::nanobench::doNotOptimizeAway(&z);
        });
    }
    {
        using Matrix = Eigen::Matrix<T, N, N, 0, N, N>;
        auto [m1, m2] = data.template getMatrix<Matrix>();
        bench.run(prefix + "inverse - Eigen3", [&]() {
            auto z  = Matrix{m1.inverse()};
            ankerl::nanobench::doNotOptimizeAway(z);
        });
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
    SECTION("float 1x1",   "[float][1x1]")    { prefix="float 1x1";   benchmark<float,  1>(); }
    SECTION("float 2x2",   "[float][2x2]")    { prefix="float 2x2";   benchmark<float,  2>(); }
    SECTION("float 3x3",   "[float][3x3]")    { prefix="float 3x3";   benchmark<float,  3>(); }
    SECTION("float 4x4",   "[float][4x4]")    { prefix="float 4x4";   benchmark<float,  4>(); }
    SECTION("float 5x5",   "[float][5x5]")    { prefix="float 5x5";   benchmark<float,  5>(); }
    SECTION("float 10x10", "[float][10x10]")  { prefix="float 10x10"; benchmark<float, 10>(); }
    SECTION("float 20x20", "[float][20x20]")  { prefix="float 20x20"; benchmark<float, 20>(); }

    SECTION("double 1x1",   "[double][1x1]")   { prefix="double 1x1";   benchmark<double,  1>(); }
    SECTION("double 2x2",   "[double][2x2]")   { prefix="double 2x2";   benchmark<double,  2>(); }
    SECTION("double 3x3",   "[double][3x3]")   { prefix="double 3x3";   benchmark<double,  3>(); }
    SECTION("double 4x4",   "[double][4x4]")   { prefix="double 4x4";   benchmark<double,  4>(); }
    SECTION("double 5x5",   "[double][5x5]")   { prefix="double 5x5";   benchmark<double,  5>(); }
    SECTION("double 10x10", "[double][10x10]") { prefix="double 10x10"; benchmark<double, 10>(); }
    SECTION("double 20x20", "[double][20x20]") { prefix="double 20x20"; benchmark<double, 20>(); }

    SECTION("int16 1x1",   "[int16][1x1]")    { prefix="int16 1x1";   benchmark<int16_t,  1>(); }
    SECTION("int16 2x2",   "[int16][2x2]")    { prefix="int16 2x2";   benchmark<int16_t,  2>(); }
    SECTION("int16 3x3",   "[int16][3x3]")    { prefix="int16 3x3";   benchmark<int16_t,  3>(); }
    SECTION("int16 4x4",   "[int16][4x4]")    { prefix="int16 4x4";   benchmark<int16_t,  4>(); }
    SECTION("int16 5x5",   "[int16][5x5]")    { prefix="int16 5x5";   benchmark<int16_t,  5>(); }
    SECTION("int16 10x10", "[int16][10x10]")  { prefix="int16 10x10"; benchmark<int16_t, 10>(); }
    SECTION("int16 20x20", "[int16][20x20]")  { prefix="int16 20x20"; benchmark<int16_t, 20>(); }

    SECTION("int32 1x1",   "[int32][1x1]")    { prefix="int32 1x1";   benchmark<int32_t,  1>(); }
    SECTION("int32 2x2",   "[int32][2x2]")    { prefix="int32 2x2";   benchmark<int32_t,  2>(); }
    SECTION("int32 3x3",   "[int32][3x3]")    { prefix="int32 3x3";   benchmark<int32_t,  3>(); }
    SECTION("int32 4x4",   "[int32][4x4]")    { prefix="int32 4x4";   benchmark<int32_t,  4>(); }
    SECTION("int32 5x5",   "[int32][5x5]")    { prefix="int32 5x5";   benchmark<int32_t,  5>(); }
    SECTION("int32 10x10", "[int32][10x10]")  { prefix="int32 10x10"; benchmark<int32_t, 10>(); }
    SECTION("int32 20x20", "[int32][20x20]")  { prefix="int32 20x20"; benchmark<int32_t, 20>(); }

    SECTION("int64 1x1",   "[int64][1x1]")    { prefix="int64 1x1";   benchmark<int64_t,  1>(); }
    SECTION("int64 2x2",   "[int64][2x2]")    { prefix="int64 2x2";   benchmark<int64_t,  2>(); }
    SECTION("int64 3x3",   "[int64][3x3]")    { prefix="int64 3x3";   benchmark<int64_t,  3>(); }
    SECTION("int64 4x4",   "[int64][4x4]")    { prefix="int64 4x4";   benchmark<int64_t,  4>(); }
    SECTION("int64 5x5",   "[int64][5x5]")    { prefix="int64 5x5";   benchmark<int64_t,  5>(); }
    SECTION("int64 10x10", "[int64][10x10]")  { prefix="int64 10x10"; benchmark<int64_t, 10>(); }
    SECTION("int64 20x20", "[int64][20x20]")  { prefix="int64 20x20"; benchmark<int64_t, 20>(); }

}
