#pragma once

#include "using_functional.h"
#include "using_optional.h"
#include "using_variant.h"

template <typename T>
using OptRef = optional<ref_wrapper<T>>;

enum class GameType : char {
	TwoPlayers = 2,
	ThreePlayers = 3,
	FourPlayers = 4
};

static inline const char* GameTypeToString(GameType gt)
{
	static const char twoPlayersStr[] = "TwoPlayers";
	static const char threePlayersStr[] = "ThreePlayers";
	static const char fourPlayersStr[] = "FourPlayers";

	switch (gt)
	{
	case GameType::TwoPlayers:
		return twoPlayersStr;
	case GameType::ThreePlayers:
		return threePlayersStr;
	case GameType::FourPlayers:
		return fourPlayersStr;
	}
}

#ifdef _WIN32
#define SYS_CLEAR "cls"
#define SYS_PAUSE "pause"
#else
#define SYS_CLEAR "clear"
#define SYS_PAUSE ""
#endif
