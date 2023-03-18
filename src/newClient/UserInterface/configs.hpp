/**
 * Project Untitled
 */

#pragma once


enum class STATE {
	WELCOME,
	CONNECTION,
	MENU,
	FRIENDS,
	RANK,
	GAME
};


constexpr int WINDOW_WIDTH = 1600;
constexpr int WINDOW_HEIGHT = WINDOW_WIDTH * 9 / 16;
