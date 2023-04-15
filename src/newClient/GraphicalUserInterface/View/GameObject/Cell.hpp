#ifndef _CELL_HPP
#define _CELL_HPP

#include <string>
#include "../Objects/ModalBox.hpp"
#include <iostream>

class Cell : public Box {

	ImageButton cell_im;
	int cell_number;
	std::string owner;
	std::vector<Image*> images_player {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
	std::vector<std::unique_ptr<Image>> images_building;
	Image mortgaged{info,PATTERN};
	Box grayed;

public :

    explicit Cell(ObjectInfo<> info, sf::Color color, std::string path, int cell_number):
         AbstractViewObject(info),Box(info,color), cell_im(info, path), cell_number(cell_number)
		 ,grayed(info,sf::Color(0, 0, 0, 180)){
			grayed.setHidden();
			mortgaged.setHidden();
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

		grayed.draw(window);
		mortgaged.draw(window);

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

	void removePlayer(int player_number ) {
		images_player[player_number] = nullptr;
		

	}

	void setOwner(std::string player_color){
		owner = player_color;
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
		owner = "";
	}

	void setHouse(int nb, std::string player_color){
		std::string path;
		if (player_color == "red"){path = HOUSE_RED;}
		else if (player_color == "blue"){path = HOUSE_BLUE;}
		else if (player_color == "green"){path = HOUSE_GREEN;}
		else if (player_color == "yellow"){path = HOUSE_YELLOW;}
		else if (player_color == "magenta"){path = HOUSE_MAGENTA;}
		else if (player_color == "cyan"){path = HOUSE_CYAN;}

		int pos_x = 5;
		int pos_y = 5;
		
		if(cell_number >20 and cell_number < 30){pos_x = 25;}
		if (  cell_number >30 and cell_number < 40){pos_y = 30;}

		for ( int i = 0; i< nb;i ++){
			images_building.emplace_back(std::make_unique<Image>(ObjectInfo<>(15,15,info.getX() + pos_x +(15 * i), info.getY() + pos_y),path));}}

	void setHotel(std::string player_color){
		std::string path;
		if (player_color == "red"){path = HOTEL_RED;}
		else if (player_color == "blue"){path = HOTEL_BLUE;}
		else if (player_color == "green"){path = HOTEL_GREEN;}
		else if (player_color == "yellow"){path = HOTEL_YELLOW;}
		else if (player_color == "magenta"){path = HOTEL_MAGENTA;}
		else if (player_color == "cyan"){path = HOTEL_CYAN;}

		int pos_x = 20;
		int pos_y = 3;
		
		if(cell_number >20 and cell_number < 30){pos_x = 40;}
		if (  cell_number >30 and cell_number < 40){pos_y = 22;}

		images_building.emplace_back(std::make_unique<Image>(ObjectInfo<>(25,25,info.getX() + pos_x, info.getY() + pos_y),path));
	}



	void setBuilding(int nb){
		images_building.clear();
		if (nb == 0){setOwner(owner);}
		else if(nb > 0 and nb <= 4  ){setHouse(nb, owner);}
		else if( nb >= 5){setHotel(owner);}}

	void setGrayed(){grayed.setVisible();}

	void unsetGrayed(){grayed.setHidden();}
	
	void setIdle(){
		setBuilding(0);
		removeOwner();
	}

	void setMortgaged(){
		mortgaged.setVisible();
	}

	void unsetMortgaged(){
		mortgaged.setHidden();
	}

	ImageButton* getButton(){return &cell_im; }



};

#endif