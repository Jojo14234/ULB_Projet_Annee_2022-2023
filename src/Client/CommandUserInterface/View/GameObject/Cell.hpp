#ifndef _CELL_HPP
#define _CELL_HPP

#include <string>
#include "../Objects/TextBox.hpp"

class Cell : public TextBox {

	int owner=0;
	std::string save;

public :

    explicit Cell(ObjectInfo info, std::string name) : AbstractViewObject(info), Box(info), Text(info, {name}, true), TextBox{info, {name}, true} {
		this->win = newwin(info.getHeight(), info.getWidth(), info.getY(), info.getX());
		this->draw();
		texts.resize(3);
	}

	virtual void draw() override {
		TextBox::draw();
	}

	void setPlayer(int player) {
		texts.at(1) += std::to_string(player);
	}

	void removePlayer(int player) {
		std::size_t e = texts.at(1).find(std::to_string(player));
		texts.at(1).erase(e, 1);
	}

	void setOwner(int player){
		owner = player;
		texts.at(2) = "Owner: " + std::to_string(player);
	}

	void enterBuildMode(){
		save = texts.at(1);
		texts.at(1) = "BUILD";
	}

	void enterSellMode(){
		save = texts.at(1);
		texts.at(1) = "SELL";
	}

	void enterMortgageMode(){
		save = texts.at(1);
		texts.at(1) = "MORTGAGE";
	}

	void enterUnmortgageMode(){
		save = texts.at(1);
		texts.at(1) = "UNMRTGAG"; //on ne peut pas avoir un string de taille >9
	}

	void enterExchangeMode(){
		save = texts.at(1);
		texts.at(1) = "EXCHANGE";
	}

	void leaveSpecialMode(){
		texts.at(1) = save;
	}

	void setIdle(){
		texts.at(2).clear();
		owner = 0;
	}

	void clearAll(){
		texts.at(1).clear();
		setIdle();
	}

	void setBuilding(int nb){
		if (nb == 0) { setOwner(owner); return; }

		texts.at(2) = std::to_string(owner) + ": ";
		if (nb >= 5){
			texts.at(2) = std::to_string(owner) + ": $";
		} else {
			for (int i=0; i<nb; i++) texts.at(2) += "*";
		}	
	}

	void setMortgaged(){
		texts.at(2) = "MRTGAGED"; //on ne peut pas avoir un string de taille >9
	}

	void unmortgage(){
		this->setOwner(owner);
	}

};

#endif