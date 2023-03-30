#include "MainCLIWindow.hpp"
#include "View/ConnectionCLIView.hpp"
#include "View/MenuCLIView.hpp"
#include "View/GameCLIView.hpp"

#include "Controller/ConnectionCLIController.hpp"
#include "Controller/MenuCLIController.hpp"
#include "Controller/GameCLIController.hpp"




MainCLIWindow::MainCLIWindow() {
    this->initAttributes();
    this->draw();
    this->controller.move(state);
}

void MainCLIWindow::mainLoop() {
    while ( true ) {
        this->controller.handle(state, 1);
        this->draw();
    }
}

void MainCLIWindow::initAttributes() {
    ConnectionCLIView* connection_view = new ConnectionCLIView();
    MenuCLIView* menu_view = new MenuCLIView();
    GameCLIView* game_view = new GameCLIView();
    this->view.setViews({connection_view, menu_view, game_view});

    ConnectionCLIController* connection_controller = new ConnectionCLIController(&this->model, connection_view);
    GameCLIController* game_controller = new GameCLIController(&this->model, game_view);
    MenuCLIController* menu_controller = new MenuCLIController(&this->model, menu_view, game_controller);

    this->controller.setController({connection_controller, menu_controller, game_controller});


}

void MainCLIWindow::draw() {
    this->view.draw(state);
}
