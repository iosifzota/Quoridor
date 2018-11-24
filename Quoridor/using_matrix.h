#pragma once
#include <array>

using std::array;
using std::size_t;

template <typename T, size_t N, size_t M>
using matrix = array<array<T, M>, N>;