#pragma once


enum class STATE {
	CONNECTION,
	MENU,
	GAME
};

class MenuCLIObserver {
public:
    virtual void update() = 0;
};

class GameCLISubject {
    MenuCLIObserver* sub;
public:
    GameCLISubject(MenuCLIObserver* sub): sub{sub} {}
    void notify() { sub->update(); }
};