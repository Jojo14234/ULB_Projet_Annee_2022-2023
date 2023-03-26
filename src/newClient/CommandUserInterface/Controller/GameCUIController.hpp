/**
 * Project Untitled
 */

#pragma once

#include "AbstractCUIController.hpp"
#include "../configs.hpp"


class Client; // forward declaration
class GameCUIView; // forward declaration

class GameCUIController: public AbstractCUIController {

	enum GAME_STATE { CHAT, CONSOLE, IDLE };
	GAME_STATE state = IDLE;

	GameCUIView* view;

public: 
	
	GameCUIController(Client* model, GameCUIView* view);

	~GameCUIController()=default;

	void handle(int event) override;
	
	void move() override;

	void receiveMsgLoop();

	void initGame();

	void initScreen();

	void startGame();

};