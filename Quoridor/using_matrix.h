#pragma once
#include <array>

using std::array;
using std::size_t;

template <typename T, size_t Rows, size_t Cols=Rows>
using matrix = array<array<T, Cols>, Rows>;