#pragma once

#include "util_templates.h"
#include <string_view>
#include <string>

using std::string;
using std::string_view;

enum class GameState :char {
	Moving,
	Placing,
	Quiting
};

//using ParseState = std::pair<GameState, char>;

template<GameState>
struct ParsedValue
{
	ParsedValue(char character) : c{ character } {};
	const char c;

	operator char() { return c; }
};

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

// idea: and_if
class SimpleParser
{
public:
	SimpleParser(const string_view& keychars) :
		m_keychars{ keychars }
	{}

	inline optional<char> operator()(const string_view& line)
	{
		if (line.empty()) {
			return {};
		}

		size_t optionIndex = line.find_first_of(m_keychars);
		if (string_view::npos == optionIndex) {
			return {};
		}

		return line[optionIndex];
	}

private:
	const string m_keychars;
};

template <GameState gameState>
class GameStateParser
{
	using LocalParsedValue = ParsedValue<gameState>;

public:
	constexpr GameStateParser() = default;

	inline constexpr variant<LocalParsedValue, string_view> operator()(const string_view& line) const
	{
		if (line.empty()) {
			return line;
		}

		size_t optionIndex = line.find_first_of(keychars);
		if (string_view::npos == optionIndex) {
			return line;
		}

		return LocalParsedValue(line[optionIndex]);
	}

private:
	constexpr static string_view keychars = Parse::gameStateToKeychars(gameState);
};

namespace Parse {

	constexpr static GameStateParser<GameState::Moving> Moving;
	constexpr static GameStateParser<GameState::Placing> Placing;
	constexpr static GameStateParser<GameState::Quiting> Quiting;
}


template<typename Result, GameState gameState>
using Function = ignore_deduction_t<function<Result(ParsedValue<gameState>&, GameState)>>;

//using ParseResult = variant<Direction, Place, Err>;



template<GameState gameState>
variant<Success, string_view> applyParser(
	const string_view& line,
	const GameStateParser<gameState>& parser)
{
	using LocalParsedValue = ParsedValue<gameState>;

	// [Debug]
	static_assert(sizeof(string_view) == sizeof(string_view&));

	auto parseResult = parser(line); // <?, string_view>
	if (std::holds_alternative<LocalParsedValue>(parseResult)) {
		return Success{};

	}
	return std::get<string_view>(parseResult);
}

template<typename Result, GameState gameState>
variant<Result, string_view> applyParser(
	const string_view& line,
	const GameStateParser<gameState>& parser,
	Function<Result, gameState> action)
{
	using LocalParsedValue = ParsedValue<gameState>;

	// [Debug]
	static_assert(sizeof(string_view) == sizeof(string_view&));

	auto parseResult = parser(line); // <?, string_view>
	if (std::holds_alternative<LocalParsedValue>(parseResult)) {
		return action(std::get<LocalParsedValue>(parseResult), gameState);

	}
	return std::get<string_view>(parseResult);
}