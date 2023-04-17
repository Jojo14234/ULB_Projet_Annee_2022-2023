#include <SFML/Window.hpp>

#include "RankGUIController.hpp"
#include "../View/RankGUIView.hpp"
#include "../../Model/Client.hpp"
#include "../../Model/QueryParser/MenuParser.hpp"


void RankGUIController::handle(sf::Event event) {
	if (event.type != sf::Event::MouseButtonPressed) return;
	if (this->view->back_button.contains(event.mouseButton.x, event.mouseButton.y)) { // return button
		this->new_state = STATE::MENU;
	} 
	else if ( this->view->top.contains(event.mouseButton.x, event.mouseButton.y)) { // top button
		MainInputParser parser("/rank top");
		std::string response;
		if (this->model->sendCommand(parser)) { 
			this->model->receive(response);
			RankingInfosList ranking{response};
			
			for (auto info : ranking.infos) {
				this->view->setUpPlayer(info.pos, info.username, info.points);
			}
		}

        this->view->hideMyRank();
		this->view->showTop();
    } 
	else if (this->view->my_rank.contains(event.mouseButton.x, event.mouseButton.y)) { // my rank button
		MainInputParser parser("/rank pos");
		std::string response;
		if (this->model->sendCommand(parser)) { 
			this->model->receive(response);
			RankingINFO info{response};
			this->view->setUpMyRank(info.pos, info.username, info.points);
		}
        this->view->hideTop();
		this->view->showMyRank();
    }
}
