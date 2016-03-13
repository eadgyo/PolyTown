#pragma once
// Flags
enum HudEvent
{
	OK = 0,
	RESET = 1 << 0,
	POP = 1 << 1,
	MENU = 1 << 2,
	NEW_GAME = 1 << 3,
	LOAD_GAME = 1 << 4,
	SCORE = 1 << 5,
	CREDIT = 1 << 6,
	EXIT = 1 << 7
};

inline HudEvent operator|(HudEvent a, HudEvent b)
{
	return static_cast<HudEvent>(static_cast<int>(a) | static_cast<int>(b));
}

inline bool operator%(HudEvent a, HudEvent b)
{
	return static_cast<HudEvent>(static_cast<int>(a) & static_cast<int>(b)) == b;
}