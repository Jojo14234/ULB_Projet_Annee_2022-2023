/**
 * Project Untitled
 */

#include <iostream>

#include "GameTerminalController.hpp"


// Public

GameTerminalController::GameTerminalController(Client* model, GameTerminalView* view) :
	AbstractTerminalController(model, STATE::GAME), view{view} {}

void GameTerminalController::handle(int event) {
	std::cout << event << std::endl;
}

void GameTerminalController::move() {

}

void GameTerminalController::receiveMsgLoop() {
	
}

void GameTerminalController::initGame() {
	
}

void GameTerminalController::initScreen() {
	
}

void GameTerminalController::startGame() {
	
}