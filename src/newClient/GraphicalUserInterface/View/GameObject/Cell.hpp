#ifndef _CELL_HPP
#define _CELL_HPP

#include <string>
#include "../Objects/ModalBox.hpp"
#include <iostream>

class Cell : public Box {

	int building_nb=0; // For now, it's useless
	int owner=0;
	ImageButton cell_im;
	int cell_number;
	std::vector<Image*> images_player {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
	std::vector<std::unique_ptr<Image>> images_building;

public :

    explicit Cell(ObjectInfo<> info, sf::Color color, std::string path, int cell_number):
         AbstractViewObject(info),Box(info,color), cell_im(info, path), cell_number(cell_number){
			if (cell_number <= 9){cell_im.rotate(90);}
			else if(cell_number >= 10 and cell_number <= 19){cell_im.rotate(180);}
			else if(cell_number >= 20 and cell_number <= 29){cell_im.rotate(-90);}}

	void draw(sf::RenderWindow &window) const override {
		if (isHidden()) return;
		Box::draw(window);
		cell_im.draw(window);
		for (auto &image : images_player ){
			if ( image != nullptr){
				image->draw(window);}} 

		for (auto &building : images_building){
			building->draw(window);
		}

	}

	void setPlayer(Image* player, int player_number){	
		int space_x = 5;
		int space_y = 30;
		if ( cell_number >20 and cell_number < 30){space_x = 25;}
		if ( cell_number >30 and cell_number < 40){space_y = 50;}

		if (player_number < 3){
			player->setPosition(ObjectInfo<>(info.getWidth(),info.getHeight(),info.getX()+ space_x + (20 * (player_number %3)),info.getY() + space_y));
		}
		else if(player_number >= 3){
			player->setPosition(ObjectInfo<>(info.getWidth(),info.getHeight(),info.getX()+ space_x + (20 * (player_number %3)),info.getY() + space_y + 20));}
		images_player [player_number] = player;
		

	}

	void removePlayer(Image* player,int player_number ) {
		images_player [player_number] = nullptr;
		

	}

	void setOwner(std::string player_color){
		std::string path;
		if (player_color == "red"){path = FLAG_RED;}
		else if (player_color == "blue"){path = FLAG_BLUE;}
		else if (player_color == "green"){path = FLAG_GREEN;}
		else if (player_color == "yellow"){path = FLAG_YELLOW;}
		else if (player_color == "magenta"){path = FLAG_MAGENTA;}
		else if (player_color == "cyan"){path = FLAG_CYAN;}

		int pos_x = 30;
		int pos_y = 3;
		if (  cell_number >30 and cell_number < 40){pos_y = 20;}
		images_building.emplace_back(std::make_unique<Image>(ObjectInfo<>(25,25,info.getX() + pos_x, info.getY() + pos_y),path));}
	
	void removeOwner(){
		images_building.erase(images_building.begin(),images_building.begin()+1);
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