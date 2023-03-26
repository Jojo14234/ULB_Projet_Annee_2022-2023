#ifndef _BOARD_HPP_
#define _BOARD_HPP_

#include <stdlib.h>
#include <ncurses.h>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <memory>

#include "Cell.hpp"
#include "../Object/AbstractViewObject.hpp"
#include "../Object/ObjectInfo.hpp"
#include "../Object/TextBox.hpp"


//Class representing the gameboard with the different game spaces and the spaces for the cards.
class Board : public AbstractViewObject {
	
	static const int col_nb = 11; 
	static const int line_nb = 11; 
	static const int gamebox_nb = 40;

	std::vector<int> old_pos_player;
	std::array<int,40> old_lev_house;

    int n_player; //number of players in game

	std::array<std::shared_ptr<Cell>, gamebox_nb> board;
	std::array<std::string, gamebox_nb> cellname; //vector of names of each cells

	//size of a cell
	int height = 5; 
	int width = 11;

	TextBox legend{ObjectInfo{6, 18, ((height-1)*(line_nb-1))/2 + info.getY(), 3 + width + info.getX() },{"Legende", "* : maison", "$ : hotel", "1-6 : Joueur"}};
	TextBox lucky_cart{ObjectInfo{6, 30, 1 + height + info.getY(), 3 + width + info.getX() }, {"", "Cartes Chances"}};
	TextBox commu_cart{ObjectInfo{6, 30, ((line_nb-1) * (height-1)) - 6 - 1 + info.getY(), 
								  ((col_nb-1) * (width-1)) - 30 - 3 + info.getX()}, {"","Caisse de communaute"}};

	void loadCellNames();
	void createBoard();

public: 

	void draw() override;

	Board(ObjectInfo info, int n_player): AbstractViewObject{info}, n_player{n_player} {
		this->loadCellNames();    
		this->createBoard();
		old_pos_player.resize(n_player);
		for(int i = 0; i< n_player ; i++){old_pos_player[i] = 0;}
	}
    int getNPlayer() { return n_player; }
	int getCellIndex(std::string cell);
	void setPlayer(int cell, int player);
	void unsetPlayer(int player);
	void movePlayer(int cell, int player);
	void setIdle(int cell);
	void setPurchased(int cell, int player);
	void setHouse(int cell, int house_nb);
	//void removeHouse(int cell, int house_nb);
	void setBuildable(int cell);
	void setSalable(int cell);
	void leaveSelection(int cell);

};

#endif