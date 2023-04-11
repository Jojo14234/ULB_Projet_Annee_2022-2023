#ifndef _CELL_HPP
#define _CELL_HPP

#include <string>
#include "../Objects/ModalBox.hpp"

class Cell : public ModalBox {

	int building_nb=0; // For now, it's useless
	int owner=0;
	Image cell_im;
	int cell_number;

public :

    explicit Cell(ObjectInfo<> info, sf::Color color, std::string path, int cell_number):
         AbstractViewObject(info), ModalBox(info,color), cell_im(info, path), cell_number(cell_number){
			if (cell_number <= 9){cell_im.rotate(90);}
			else if(cell_number >= 10 and cell_number <= 19){cell_im.rotate(180);}
			else if(cell_number >= 20 and cell_number <= 29){cell_im.rotate(-90);}
			addImage(&cell_im);}

	void draw(sf::RenderWindow &window) const override {
		if (isHidden()) return;
		Box::draw(window);
		for (auto &image : images) image->draw(window);
		for (auto &text : texts) text->draw(window);
		for (auto &button : buttons) button->draw(window);
	}

	/*void setPlayer(int player) {

	}

	void removePlayer(int player) {
	}*/

	void setOwner(int player){
		std::string path ;
		if (player == 0){
			path = FLAG_PATH;
		}
		else {
			path = FLAG_PATH;
		}
		Image* flag = new Image (info, path);
		flag->setFlag();
		addImage(flag);

	}

	/*void enterBuildMode(){
	}

	void enterSellMode(){
	}

	void leaveBuildMode(){
	}

	void setIdle(){
	}

	void addBuilding(int nb){
		delete image[1]; // delete le flag 	
	}

	void removeBuilding(int nb){
	}*/

};

#endif