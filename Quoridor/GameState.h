#pragma once

#include "req.hh"
#include <string_view>
using std::string_view;

enum class GameState :char {
	Moving,
	Placing,
	Quiting
};

using ParseState = std::pair<GameState, char>;

namespace Parse {
	constexpr static char moving[] = "wasdWASD";
	constexpr static char placing[] = "pP";
	constexpr static char quiting[] = "qQ";

	inline constexpr static const char* gameStateToKeychars(GameState gameState)
	{
		switch (gameState)
		{
		case GameState::Moving:
			return Parse::moving;
		case GameState::Placing:
			return Parse::placing;
		case GameState::Quiting:
			return Parse::quiting;
		default:
			req("[Debug] Must've forgot to include case for a GameState.");
			return {};
		}
	}
}

template <GameState gameState>
class GameStateParser
{
public:
	constexpr GameStateParser() = default;

	inline constexpr variant<ParseState, string_view> operator()(const string_view& line) const
	{
		if (line.empty()) {
			return line;
		}

		size_t optionIndex = line.find_first_of(keychars);
		if (string_view::npos == optionIndex) {
			return line;
		}

		return ParseState(gameState, line[optionIndex]);
	}

private:
	constexpr static string_view keychars = Parse::gameStateToKeychars(gameState);
};

namespace Parse {

	constexpr static GameStateParser<GameState::Moving> Moving;
	constexpr static GameStateParser<GameState::Placing> Placing;
	constexpr static GameStateParser<GameState::Quiting> Quiting;
}
