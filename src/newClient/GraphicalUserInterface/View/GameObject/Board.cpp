#include "Board.hpp"


void Board::draw(sf::RenderWindow& window) { 
	for (auto i : board){
        i->draw(window);
    }
        
}

//method to have a list of name for the cells
void Board::loadCellNames(){
	std::string cell;
	std::ifstream cell_names_file(CELL_NAME);
	if (cell_names_file.is_open()){
		int i=0;
		while (std::getline(cell_names_file , cell)) {cellname[i] = cell; i++;}
		cell_names_file.close();
	} 
	else exit(1);
}


void Board::loadCellFile(){
	std::string cell;
	std::ifstream cell_names_file(FILE_NAME);
	if (cell_names_file.is_open()){
		int i=0;
		while (std::getline(cell_names_file , cell)) {
            cell_file[i] = cell; 
            i++;}
		cell_names_file.close();
	} 
	else exit(1);
}



int Board::getCellIndex(std::string cell){
	int index_cell = -1;
	for(int i = 0; i < gamebox_nb; i++) {
        if(cellname[i] == cell){
            index_cell = i;
            break;
        }}
	return index_cell;
}

//method to create the gameboard
void Board::createBoard(){
	sf::Vector2f size;
	sf::Vector2f position;
    for (int i = 0; i < 40 ; i++){ 
        size =  v_cell_size;
        if ( i % 10 == 0 ){
            if ( i == 0){position.x = start_corner.x  +1; position.y =start_corner.y;}
            else if ( i == 10){position.x = start_corner.x - 1; position.y = start_corner.y - 9 *v_cell_size.y - corner_cell_size.y ;}
            else if ( i == 20){position.x = start_corner.x + 9 *v_cell_size.y + corner_cell_size.x - 1; position.y = start_corner.y - 9 *v_cell_size.y - corner_cell_size.y ;}
            else if ( i == 30){position.x = start_corner.x + 9 *v_cell_size.y + corner_cell_size.x +1; position.y = start_corner.y   ;}
            
            board[i] = std::make_shared<Cell>(ObjectInfo<>(corner_cell_size.x,corner_cell_size.y, position.x,position.y),
                                                sf::Color::White, CELL_PATH + cell_file[i], i);
        }

        else {
            if (i <= 9){position.x = start_corner.x +1; position.y =start_corner.y - i * v_cell_size.y;}
            else if ( i >= 11 and i <= 19){
				size = h_cell_size;
                position.x = (start_corner.x + corner_cell_size.x)+ (i-11)* v_cell_size.y ; position.y = start_corner.y - 9 * v_cell_size.y - corner_cell_size.y;  }
            else if ( i >= 21 and i <= 29){
				position.x = (start_corner.x+ corner_cell_size.x)+ 9* v_cell_size.y + 2; position.y =  start_corner.y - 9 * v_cell_size.y + (i - 21)*v_cell_size.y;}
            else if ( i >= 31 and i <= 39){
				size = h_cell_size;
                position.x =(start_corner.x+corner_cell_size.x+ 9*v_cell_size.y) - (i-30) * v_cell_size.y ;position.y = start_corner.y ;}
            board[i] = std::make_shared<Cell>(ObjectInfo<>(size.x,size.y, position.x,position.y),
                                                 sf::Color::White,  CELL_PATH + cell_file[i] , i);
        }}}


////////////////////////////////////////////////////////////////
//method for setting and unsetting player


void Board::setColorNumber(int n_player){
		player_color.clear();
		player_nb = n_player;
		for (int i = 0; i < n_player;i++){
			if(player_color_names[i] == "red"){player_color.emplace_back(&red);}
			else if(player_color_names[i]== "blue"){player_color.emplace_back(&blue);}
			else if(player_color_names[i] == "magenta"){player_color.emplace_back(&magenta);}
			else if(player_color_names[i] == "green"){player_color.emplace_back(&green);}
			else if(player_color_names[i] == "yellow"){player_color.emplace_back(&yellow);}
			else if(player_color_names[i] == "cyan"){player_color.emplace_back(&cyan);}}}


void Board::setPlayer(int cell, int player){
	board[cell]->setPlayer(player_color[player], player);
}

void Board::movePlayer(int cell, int player){
    std::cout << "m1" << std::endl;
    board[old_pos_player[player]]->removePlayer(player);
	 std::cout << "m2" << std::endl;
    old_pos_player[player] = cell;
	 std::cout << "m3" << std::endl;
	board[cell]->setPlayer(player_color[player], player);
	 std::cout << "m4" << std::endl;
}
 

//methods for setting or unsetting building

void Board::setIdle(int cell){
	board[cell]->setIdle();
}

void Board::setPurchased(int cell, int player){
	std::cout << "pursh" << std::endl;
	board[cell]->setOwner(player_color_names[player]);
	std::cout << "purshessh" << std::endl;
}

void Board::setHouse(int cell, int house_nb){
	board[cell]->setBuilding(house_nb);
}


void Board::setBuildable(int cell){
	board[cell]->setGrayed();

}
void Board::setAllGrayed(){
	for (auto i : board){
        i->setGrayed();
    }

}

void Board::setSalable(int cell){
	board[cell]->unsetGrayed();
}
void Board::setMortgageable(int cell){
	board[cell]->unsetGrayed();
}
void Board::setUnmortgageable(int cell){
	board[cell]->unsetGrayed();
}
void Board::setExchangeable(int cell){
	board[cell]->unsetGrayed();
}

void Board::leaveSelection(int cell){
	board[cell]->setGrayed();
}

void Board::unsetAllGrayed(){
	for (auto i : board){
        i->unsetGrayed();
    }
}

void Board::setMortgaged(int cell){
	board[cell]->setMortgaged();
}

void Board::unmortgage(int cell){
	board[cell]->unsetMortgaged();
}

std::array<std::shared_ptr<Cell>,40>* Board::getBoardButton(){
	return &board;
}

