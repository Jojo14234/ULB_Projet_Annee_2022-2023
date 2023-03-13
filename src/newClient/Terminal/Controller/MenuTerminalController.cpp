/**
 * Project Untitled
 */

#include <iostream>

#include "MenuTerminalController.hpp"


// Public

MenuTerminalController::MenuTerminalController(Client* model, MenuTerminalView* view) :
	AbstractTerminalController(model, STATE::MENU), view{view} {}

void MenuTerminalController::handle(int event) {
	std::cout << event << std::endl;
}

void MenuTerminalController::move() {

}