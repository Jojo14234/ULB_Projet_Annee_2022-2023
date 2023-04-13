#include <SFML/Window.hpp>

#include "GameGUIController.hpp"
#include "../View/GameGUIView.hpp"
#include "../../Model/Client.hpp"


void GameGUIController::handle(sf::Event event) {
    if (event.type != sf::Event::MouseButtonPressed) return;
            if(this->view->button_mode == "start_round"){
                if(this->view->mortgage_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->unmortgage_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->sell_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->construct_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->exchange_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->roll_dice_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }}
            else if (this->view->button_mode == "empty_cell"){
                if(this->view->buy_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->no_buy_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }}
            else if (this->view->button_mode == "paid_cell"){
                if(this->view->paid_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }}
            else if (this->view->button_mode == "card_cell"){
                if(this->view->draw_card_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }}
            else if (this->view->button_mode == "on_prison"){
                if(this->view->paid_prison_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->roll_dice_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->card_prison_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }}
            else if (this->view->button_mode == "exchange_round"){
                if(this->view->yes_exchange_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->no_exchange_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }}
            else if (this->view->button_mode == "bankrupt_round"){
                if(this->view->sell_bankrupt_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->give_up_button.contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }}
            else if (this->view->button_mode == "auction_round"){
                if(this->view->auction_box.getUpButton()->contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->auction_box.getDownButton()->contains(event.mouseButton.x, event.mouseButton.y)){//TODO
                        }
                else if(this->view->auction_box.getValidateButton()->contains(event.mouseButton.x, event.mouseButton.y)){
                    //TODo
                    this->view->setAuctionRound(false);
                        }}
                        
                
    
	
}
