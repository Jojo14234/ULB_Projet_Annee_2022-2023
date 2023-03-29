/**
 * Project Untitled
 */

#pragma once


enum class STATE {
	CONNECTION = 0,
	MENU = 1,
	GAME = 2
};

class Subject {
public:
	virtual void update() = 0;
};