#ifndef _BOARD_HPP_
#define _BOARD_HPP_

#include <stdlib.h>
#include <cstdlib>
#include <SFML/Graphics.hpp> 
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <memory>

#include "../AssetsPath.hpp"
#include "Cell.hpp"

//Class representing the gameboard with the different game spaces and the spaces for the cards.
class Board{
	
	static const int col_nb = 11; 
	static const int line_nb = 11; 
	static const int gamebox_nb = 40;

	std::vector<int> old_pos_player;
	std::array<int,40> old_lev_house;

    int n_player; //number of players in game
	std::array<std::shared_ptr<Cell>, gamebox_nb> board;
	std::array<std::string, gamebox_nb> cellname; //vector of names of each cells
	std::array<std::string, gamebox_nb> cell_file; 

	int text_size = 10;

    sf::Vector2f v_cell_size{90,70};  // vertical cell's size 
	sf::Vector2f h_cell_size{v_cell_size.y,v_cell_size.x};  // horizontal cell's size 
    sf::Vector2f corner_cell_size{90,90} ;
    sf::Vector2f start_corner{350,800};  //bottom left position

    /*

	TextBox legend{ObjectInfo{6, 18, ((height-1)*(line_nb-1))/2 + info.getY(), 3 + width + info.getX() },{"Legende", "* : maison", "$ : hotel", "1-6 : Joueur"}};
	TextBox lucky_cart{ObjectInfo{6, 30, 1 + height + info.getY(), 3 + width + info.getX() }, {"", "Cartes Chances"}};
	TextBox commu_cart{ObjectInfo{6, 30, ((line_nb-1) * (height-1)) - 6 - 1 + info.getY(), 
								  ((col_nb-1) * (width-1)) - 30 - 3 + info.getX()}, {"","Caisse de communaute"}};*/

	Image red{ObjectInfo<>(15,15,0,0), PLAYER_RED };
	Image blue{ObjectInfo<>(15,15,0,0), PLAYER_BLUE };
	Image green{ObjectInfo<>(15,15,0,0), PLAYER_GREEN };
	Image magenta{ObjectInfo<>(15,15,0,0), PLAYER_MAGENTA };
	Image yellow{ObjectInfo<>(15,15,0,0), PLAYER_YELLOW };
	Image cyan{ObjectInfo<>(15,15,0,0), PLAYER_CYAN };

	std::vector<Image*> player_color{};


	void loadCellNames();
	void loadCellFile();
	void createBoard();

public: 

    
	Board(){
		this->loadCellNames();
		this->loadCellFile();
		this->createBoard();
		
		board[31]->setPlayer(&red,0);
		board[31]->setPlayer(&blue,1);
		board[31]->setPlayer(&green,2);
		board[31]->setPlayer(&magenta,3);
		board[31]->setPlayer(&yellow,4);
		board[31]->setPlayer(&cyan,5);
		}
	
    void draw(sf::RenderWindow &window);
	int getCellIndex(std::string cell);

	void setColorNumber(std::vector<std::string> color_list);
	void movePlayer(int cell, int player);


    /*int getNPlayer() { return n_player; }
	

	
	void setIdle(int cell);
	void setPurchased(int cell, int player);
	void setHouse(int cell, int house_nb);
	//void removeHouse(int cell, int house_nb);
	void setBuildable(int cell);
	void setSalable(int cell);
	void leaveSelection(int cell);*/

};

#endif