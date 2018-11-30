#pragma once
#include "using_matrix.h"
#include <algorithm>

template <size_t Rows, size_t Cols>
class Trench
{
private:
	matrix<bool, Rows, Cols> m_grid{};

public:
	Trench() =default;
	bool AtForward(size_t i, size_t j) const
	{
		if (i >= Rows || j >= Cols)
			return true;

		return m_grid[i][j];
	}
	bool AtBackward(size_t i, size_t j) const
	{
		constexpr static size_t max = std::max(Rows, Cols);

		// effective indecies
		i -= (max - Rows);
		j -= (max - Cols);

		if (i >= Rows || j >= Cols)
			return true;

		return m_grid[i][j];
	}
	size_t Height() const
	{
		return Rows;
	}
	size_t Width() const
	{
		return Cols;
	}

	void OccupyTrench(size_t i, size_t j)
	{
		if (i >= Rows || j >= Cols)
			return;

		m_grid[i][j] = true;
	}
};
