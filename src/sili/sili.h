// SPDX-FileCopyrightText: 2017 Lutz Freitag + Simon Gene Gottlieb
// SPDX-License-Identifier: MIT

#pragma once

/*! Overview
 * \page
 *
 * sili is a auto-storage only library (no heap allocation).
 *
 * It uses **c++20** and its purpose is to be used on embedded system
 *
 * The main idea is to use fixed size matrices and fixed size
 * views onto these matrices.
 *
 * \creategroup 1 Pages
 * \creategroup 2 Concepts
 * \creategroup 3 Classes
 * \creategroup 4 Free Matrix Functions
 * \creategroup 4 Matrix Operations
 * \creategroup 5 Free Vector Functions
 */


/*! Examples
 * \page
 * Example of Element Access
 * \code
 *   #include <sili/sili.h>
 *   #include <sili/ostream.h>
 *
 *   int main() {
 *       auto a = sili::Matrix{{{3, 4},
 *                              {5, 6}}};
 *       std::cout << a << "\n"; // prints {{3, 4},
 *                               //         {5, 6}}
 *
 *       a(0, 0) = a(0, 1) * 2;
 *
 *       std::cout << a << "\n"; // prints {{8, 4},
 *                               //         {5, 6}}

 *   }
 * \endcode

 * Example of Matrix Multiplication:
 * \code
 *   #include <sili/sili.h>
 *   #include <sili/ostream.h>
 *
 *   int main() {
 *       auto a = sili::Matrix{{{3, 4, 7},
 *                              {5, 6, 8}}};
 *       auto b = sili::Matrix{{{1, 2},
 *                              {4, 5},
 *                              {3, 6}};
 *       auto c = a * b; // c is of type sili::Matrix<2, 2, int>
 *       std::cout << c << "\n"; // prints {{40, 68},
 *                               //         {53, 88}}
 *   }
 * \endcode
 *
 *
 * Example of Matrix inversion:
 * \code
 *   #include <sili/sili.h>
 *   #include <sili/ostream.h>
 *
 *   int main() {
 *       auto a = sili::Matrix{{{3, 4},
 *                              {5, 6}}};
 *       auto b = inv(a);
 *       std::cout << b << "\n"; \\ prints {{ -3,  2},
 *                                          {2.4, -1.5}}
 *   }
 * \endcode
 *
 *
 * Example of view
 * \code
 *   #include <sili/sili.h>
 *   #include <sili/ostream.h>
 *
 *   int main() {
 *       auto a = sili::Matrix{{{ 3,  4, 5},
 *                              { 6,  7, 8},
 *                              { 9, 10, 11}};
 *       std::cout << a << "\n"; // prints {{ 3,  4,  5},
 *                               //         { 6,  7,  8},
 *                               //         { 9, 10, 11}}
 *
 *       auto v = view<1, 1, 3, 3>(a); // view to the lower right 2x2 (7, 8, 10, 11) matrix
 *       std::cout << v << "\n"; // prints {{ 7,  8},
 *                               //         {10, 11}}
 *
 *       v *= 2.;
 *       std::cout << v << "\n"; // prints {{14, 16},
 *                               //         {20, 22}}
 *
 *       std::cout << a << "\n"; // prints {{ 3,  4,  5},
 *                               //         { 6, 14, 16},
 *                               //         { 9, 20, 22}}
 *   }
 * \endcode
 */



#include "Matrix.h"
#include "View.h"
#include "operations.h"
#include "Iterator.h"
