#pragma once
#include <array>
#include <algorithm>
using std::array;
using std::size_t;

template < int N, int M, typename T>
using matrix = array<array<T, M>, N>;

template <size_t N, size_t M>
class Trench
{
public:
	Trench() =default;
	matrix<N, M, bool> m_grid;
	bool AtForward(size_t i, size_t j) const
	{
		return m_grid[i][j];
	}
	bool AtBackward(size_t i, size_t j) const
	{
		constexpr size_t max = std::max(N, M);
		return m_grid[i - (max - N)][j - (max - M)];
	}
};
