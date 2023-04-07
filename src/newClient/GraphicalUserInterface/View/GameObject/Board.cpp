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
/*void Board::unsetPlayer(int player){}

void Board::setPlayer(int cell,int player){
	old_pos_player[player-1] = cell;
}

void Board::movePlayer(int cell, int player){
	unsetPlayer(player);
	setPlayer(cell, player);
}
 


//method to clear all buildings a cell
void Board::setIdle(int cell){}

void Board::setPurchased(int cell, int player){}

void Board::setHouse(int cell, int house_nb){}

void Board::setBuildable(int cell) {}

void Board::setSalable(int cell) {}

void Board::leaveSelection(int cell) {}*/

