/**
 * Project Untitled
 */

#pragma once

#include "AbstractTerminalController.hpp"
#include "../configs.hpp"


class Client; // forward declaration
class GameTerminalView; // forward declaration

class GameTerminalController: public AbstractTerminalController {

	enum GAME_STATE { CHAT, CONSOLE, IDLE };
	GAME_STATE state = IDLE;

	GameTerminalView* view;

public: 
	
	GameTerminalView(Client* model, GameTerminalView* view) : AbstractTerminalController(model, STATE::GAME), view{view} {}

	~GameTerminalController()=default;

	void handle(int event) override;
	
	void move() override;

	void receiveMsgLoop();

	void initGame();

	void initScreen();

	void startGame();

};