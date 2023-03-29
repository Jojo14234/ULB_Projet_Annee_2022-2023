#pragma once

#include <vector>
#include "AbstractCUIController.hpp"
#include "../configs.hpp"


class Client; // forward declaration
class GameCUIView; // forward declaration

class GameCUIController: public AbstractCUIController {

	enum GAME_STATE { CHAT, CONSOLE, IDLE };
	GAME_STATE state = IDLE;

	GameCUIView* view;
	Subject* win;

	int player_nb;
	std::vector<std::string> players_username;
	std::vector<std::string> build_mode;

public: 
	
	GameCUIController(Client* model, GameCUIView* view);

	~GameCUIController()=default;

	void handle(int event) override;
	
	void move() override;

	void receiveMsgLoop();

	void initGame();

	void initScreen();

	void startGame(int beginner);

    //todo add from n-curse
    void playerJoinUpdate();
    void setSubject(Subject* win) { this->win = win; }



};