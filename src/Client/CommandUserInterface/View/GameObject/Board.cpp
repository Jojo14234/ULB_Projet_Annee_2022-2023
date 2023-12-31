#include "Board.hpp"


void Board::draw() { 
	for (auto& box : board) box->draw();
	this->legend.draw();
	this->lucky_cart.draw();
	this->commu_cart.draw();
}

//method to have a list of name for the cells
void Board::loadCellNames(){
	std::string cell;
	std::ifstream cell_names_file("Client/CommandUserInterface/View/cellNames.txt");
	
	if (cell_names_file.is_open()){
		int i=0;
		while (std::getline(cell_names_file , cell)) {cellname[i] = cell; i++;}
		cell_names_file.close();
	} else exit(1);
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
	int n=0;
	for (int i=line_nb-1; i >= 0; i--) {
		board[n] = std::make_shared<Cell>(ObjectInfo{height, width, i*height-(i) + info.getY(), 0 + info.getX()}, cellname[n]); n++;
	}
	for (int i=1; i < col_nb; i++) {
		board[n] = std::make_shared<Cell>(ObjectInfo{height, width, 0 + info.getY(), i*width-i + info.getX() }, cellname[n]); n++;
	}
	for (int i=1; i < line_nb-1; i++) {
		board[n] = std::make_shared<Cell>(ObjectInfo{height, width, i*height-i + info.getY(), (col_nb-2)*width+1 + info.getX()}, cellname[n]); n++;
	}
	for (int i=col_nb-1; i > 0; i--){
		board[n] = std::make_shared<Cell>(ObjectInfo{height, width, (line_nb-3)*height + info.getY(), i*width-i + info.getX()}, cellname[n]); n++;
	}
}

////////////////////////////////////////////////////////////////
//method for setting and unsetting player
void Board::unsetPlayer(int player){
	board[old_pos_player[player-1]]->removePlayer(player);
}

void Board::setPlayer(int cell,int player){
	board[cell]->setPlayer(player);
	old_pos_player[player-1] = cell;
}

void Board::movePlayer(int cell, int player){
	unsetPlayer(player);
	setPlayer(cell, player);
}
 


//method to clear all buildings a cell
void Board::setIdle(int cell){
	board[cell]->setIdle();
}

void Board::setPurchased(int cell, int player){
	board[cell]->setOwner(player);	
}

void Board::setHouse(int cell, int house_nb){
	board[cell]->setBuilding(house_nb);
}

void Board::setBuildable(int cell) { board[cell]->enterBuildMode(); }

void Board::setSalable(int cell) { board[cell]->enterSellMode(); }

void Board::setMortgaged(int cell) { board[cell]->setMortgaged(); }

void Board::setMortgageable(int cell) { board[cell]->enterMortgageMode(); }

void Board::setUnmortgageable(int cell) { board[cell]->enterUnmortgageMode(); }

void Board::setExchangeable(int cell) { board[cell]->enterExchangeMode(); }

void Board::leaveSelection(int cell) { board[cell]->leaveSpecialMode(); }

void Board::unmortgage(int cell) { board[cell]->unmortgage(); }


void Board::clearAll() {
	for (auto cell : board) cell->clearAll();
}

