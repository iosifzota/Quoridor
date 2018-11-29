#pragma once

#include "using_functional.h"
#include "using_optional.h"

template <typename T>
using OptRef = optional<ref_wrapper<T>>;

enum class GameType : char {
	TwoPlayers = 2,
	FourPlayers = 4
};

static inline const char* GameTypeToString(GameType gt)
{
	static const char twoPlayersStr[] = "TwoPlayers";
	static const char fourPlayersStr[] = "FourPlayers";

	if (gt == GameType::TwoPlayers)
		return twoPlayersStr;
	return fourPlayersStr;
}