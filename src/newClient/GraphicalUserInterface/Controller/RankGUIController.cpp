#include <SFML/Window.hpp>

#include "RankGUIController.hpp"
#include "../View/RankGUIView.hpp"
#include "../../Model/Client.hpp"


void RankGUIController::handle(sf::Event event) {
    switch (event.type) {
        case sf::Event::MouseButtonPressed: {
            if ( this->view->top.contains(event.mouseButton.x, event.mouseButton.y)) {
                this->state = TOP;
                this->view->drawTopBox();
            } else if (this->view->my_rank.contains(event.mouseButton.x, event.mouseButton.y)) {
                this->state = MY_RANK;
                this->view->drawMyRankBox();
            }
        }
    }
}
