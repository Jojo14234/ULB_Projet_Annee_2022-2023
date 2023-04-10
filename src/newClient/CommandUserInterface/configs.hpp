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

class MenuCUIObserver {
public:
	virtual void update() = 0;
};

class GameCUISubject {
	MenuCUIObserver* sub;
public:
	GameCUISubject(MenuCUIObserver* sub): sub{sub}{}
	void notify() { sub->update(); }
};