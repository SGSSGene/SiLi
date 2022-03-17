#pragma once

#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>

#include <SiLi/SiLi.h>
#include <armadillo>
#include <eigen3/Eigen/Dense>
#include <random>


template <typename T, size_t N>
struct GenerateData {
    std::array<std::array<T, N>, N> values1;
    std::array<std::array<T, N>, N> values2;

    GenerateData(){
        auto gen = std::mt19937{N};
        auto dist = std::uniform_real_distribution<double>{-1000., 1000.};
        for (size_t row{0}; row < N; ++row) {
            for (size_t col{0}; col < N; ++col) {
                values1[row][col] = static_cast<T>(dist(gen));
                values2[row][col] = static_cast<T>(dist(gen));
            }
        }
    }

    template <typename M>
    auto getMatrix() -> std::tuple<M, M> {
        M m1;
        M m2;
        for (size_t row{0}; row < N; ++row) {
            for (size_t col{0}; col < N; ++col) {
                m1(row, col) = values1[row][col];
                m2(row, col) = values2[row][col];
            }
        }
        return std::make_tuple(m1, m2);
    }

    template <typename M>
    auto getMatrix(M const& m) -> std::tuple<M, M> {
        M m1 = m;
        M m2 = m;
        for (size_t row{0}; row < N; ++row) {
            for (size_t col{0}; col < N; ++col) {
                m1(row, col) = values1[row][col];
                m2(row, col) = values2[row][col];
            }
        }
        return std::make_tuple(m1, m2);
    }
};
