#pragma once
#include <array>
#include <algorithm>
using std::array;
using std::size_t;

template <size_t N, size_t M, typename T>
class Trench
{
public:
	Trench() =default;
	matrix<N, M, bool> m_grid;
	bool AtForward(size_t i, size_t j) const
	{
		return grid[i][j];
	}
	bool AtBackward(size_t i, size_t j) const
	{
		constexpr size_t max = std::max(N, M);
		return grid[i - (max - N)][j - (max - M];
	}
};
