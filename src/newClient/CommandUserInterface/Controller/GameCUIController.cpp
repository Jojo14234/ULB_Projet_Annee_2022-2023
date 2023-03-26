/**
 * Project Untitled
 */

#include <iostream>

#include "GameCUIController.hpp"


// Public

GameCUIController::GameCUIController(Client* model, GameCUIView* view) :
	AbstractCUIController(model, STATE::GAME), view{view} {}

void GameCUIController::handle(int event) {
	std::cout << event << std::endl;
}

void GameCUIController::move() {

}

void GameCUIController::receiveMsgLoop() {
	
}

void GameCUIController::initGame() {
	
}

void GameCUIController::initScreen() {
	
}

void GameCUIController::startGame() {
	
}