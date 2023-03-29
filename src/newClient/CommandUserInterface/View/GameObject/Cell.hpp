#ifndef _CELL_HPP
#define _CELL_HPP

#include <string>
#include "../Objects/TextBox.hpp"

class Cell : public TextBox {

	int building_nb=0; // For now, it's useless
	int owner=0;

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
		texts.at(2) = "BUILD";
	}

	void enterSellMode(){
		texts.at(2) = "SELL";
	}

	void leaveBuildMode(){
		addBuilding(this->building_nb);
	}

	void setIdle(){
		texts.at(2).clear();
		building_nb = 0;
		owner = 0;
	}

	void addBuilding(int nb){
		if(building_nb == 0) texts.at(2) = std::to_string(owner) + ": ";
		building_nb += nb;
		if (building_nb >= 5){
			texts.at(2) = std::to_string(owner) + ": $";
		} else {
			for (int i=0; i<nb; i++) texts.at(2) += "*";
		}	
	}

	void removeBuilding(int nb){
		building_nb -= nb;
		if (building_nb == 0){
			this->setOwner(owner);
		} else {
			texts.at(2) = std::to_string(owner) + ": ";
			this->addBuilding(building_nb);
		}	
	}

};

#endif