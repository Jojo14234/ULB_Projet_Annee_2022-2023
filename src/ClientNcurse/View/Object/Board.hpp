#ifndef _BOARD_HPP_
#define _BOARD_HPP_

#include <stdlib.h>
#include <ncurses.h>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include "utility"

#include "AbstractViewObject.hpp"
#include "ObjectInfo.hpp"
#include "Cell.hpp"

 

//Class representing the gameboard with the different game spaces and the spaces for the cards.
class Board : public AbstractViewObject {
	
	static const int col_nb = 11; 
	static const int line_nb = 11; 
	static const int board_box_nb = col_nb * line_nb; 
	static const int gamebox_nb = 40;

	int n_player; //number of players in game

	//WINDOW *board[board_box_nb];  //box_nb number of windows for gameboxes
	std::array<std::shared_ptr<Cell>, gamebox_nb> board;
	std::array<std::string, gamebox_nb> cellname; //vector of names of each cells
	WINDOW *cardcases[2];  //box for cards (luck and community)
	WINDOW *legend; //window for the legend's box

	//size of a cell
	int height = 5; 
	int width = 11;
	int posplayer = 2; //line on the window for players
	int posbuilding = 3; //line on the window for buildings

	const Point legend_pos {25,35};
	const Point legend_size {16,7};
	Point pos_text1 {1,1};
	Point pos_text2{1,2};
	Point pos_text3 {1,3};
	Point pos_text4 {1,4};

	const Point luckycasepos {20,10};
	const Point commucasepos {65, 38};
	Point cardcasesize {30,7};
	Point pos_text5{9,3};
	Point pos_text6{5,3};

	void loadCellNames();
	void createBoard();

public: 

	void draw() override;

	Board(ObjectInfo info, int n_player): AbstractViewObject{info}, n_player{n_player} {
		this->loadCellNames();    
		this->createBoard();
	}

	void createCardCase();
	void createLegend();

	void setPlayer(int cell, int player);
	void unsetPlayer(int cell, int player);
	void clearBuilding(int cell);
	void setPurchased(int cell, int player);
	void addHouse(int cell, int house_nb);
	void setHotel(int cell);

};

#endif