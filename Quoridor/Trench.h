#pragma once
#include "using_matrix.h"
#include <algorithm>

template <size_t N, size_t M>
class Trench
{
public:
	Trench() =default;
	matrix<bool, N, M> m_grid;
	bool AtForward(size_t i, size_t j) const
	{
		// FIX ME
		if (i >= N || j >= M)
			throw "[Error] Out of bounds access";
		return m_grid[i][j];
	}
	bool AtBackward(size_t i, size_t j) const
	{
		constexpr size_t max = std::max(N, M);

		// effective indecies
		i -= (max - N);
		j -= (max - M);

		// FIX ME
		if (i >= N || j >= M)
			throw "[Error] Out of bounds access";

		return m_grid[i][j];
	}
};
