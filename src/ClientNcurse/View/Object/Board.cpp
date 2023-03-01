#include "Board.hpp"


void Board::draw() { 
	for (auto& box : board) {
		box->draw();
	}
}

//method to have a list of name for the cells
void Board::loadCellNames(){
	std::string cell;
	std::ifstream cell_names_file("ClientNcurse/cardname.txt", 'r');
	
	if (cell_names_file.is_open()){
		int i=0;
		while (std::getline(cell_names_file , cell)) {cellname[i] = cell; i++;}
		cell_names_file.close();
	} else std::ofstream("ClientNcurse/cardname.txt");
}

//method to create the gameboard
void Board::createBoard(){
	//define positions for each box 
	int n=0;
	for (int i=0; i < col_nb; i++) {
		std::cout << cellname[n] << std::endl;
		board[n] = std::make_shared<TextBox>(ObjectInfo{height, width, 0 + info.getY(), i*width-i + info.getX() }, cellname[n]); n++;
	}
	for (int i=1; i < line_nb-1; i++) {
		board[n] = std::make_shared<TextBox>(ObjectInfo{height, width, i*height-i + info.getY(), 0 + info.getX()}, cellname[n]); n++;
		board[n] = std::make_shared<TextBox>(ObjectInfo{height, width, i*height-i + info.getY(), (col_nb-2)*width+1 + info.getX()}, cellname[n]); n++;
	}
	for (int i=0; i < col_nb; i++){
		board[n] = std::make_shared<TextBox>(ObjectInfo{height, width, (line_nb-3)*height + info.getY(), i*width-i + info.getX()}, cellname[n]); n++;
	}
}

//method to put name on each box
void Board::setBoxName(){
	for (int i =  0; i < gamebox_nb; i ++){
		//mvwprintw(board[listofcell[i]], pos_text1.getY(), pos_text1.getX(), "%s", (cellname[i]).c_str());
		//wrefresh(board[listofcell[i]]); 
	}
}

//method to destroy the gameboard
void Board::destroyBoard(){
	//for (int i = 0; i <  board_box_nb ; i++) delwin(board[i]);
}


////////////////////////////////////////////////////////////////////////
//define + create cards zones and legends
//method to create zones for game's cards
void Board::createCardCase(){

	//zone for luck cards
	cardcases[0] = newwin(cardcasesize.getY(), cardcasesize.getX(), luckycasepos.getY() , luckycasepos.getX() );
	wborder(cardcases[0], '|', '|', '-', '-', '+', '+', '+', '+');
	mvwprintw(cardcases[0], pos_text5.getY(),pos_text5.getX(), "CARTE CHANCE");
	wrefresh(cardcases[0]);

	//zone for communitgetY() cards
	cardcases[1] = newwin(cardcasesize.getY(), cardcasesize.getX(), commucasepos.getY()  , commucasepos.getX() );
	wborder(cardcases[1], '|', '|', '-', '-', '+', '+', '+', '+');
	mvwprintw(cardcases[1],pos_text6.getY(),pos_text6.getX(), "CAISSE DE COMMUNAUTE");
	wrefresh(cardcases[1]);
}


//method to create a box for legend
void Board::createLegend(){
	legend = newwin( legend_size.getY() , legend_size.getX() , legend_pos.getY() , legend_pos.getX());
	wborder(legend, '|', '|', '-', '-', '+', '+', '+', '+');
	mvwprintw(legend, pos_text1.getY(), pos_text1.getX(), "Légende");
	mvwprintw(legend, pos_text2.getY(), pos_text2.getX(), "* : maison");
	mvwprintw(legend, pos_text3.getY(), pos_text3.getX(), "$ : hotel");
	mvwprintw(legend, pos_text4.getY(), pos_text4.getX(), "1-6 : Joueur");
	wrefresh(legend);  
}

////////////////////////////////////////////////////////////////
//method for setting and unsetting player
void Board::setPlayer(int cell,int player){
	//mvwprintw(board[listofcell[cell]], posplayer,player, "%s",std::to_string(player).c_str());
	//wrefresh(board[listofcell[cell]]);  
}
 
void Board::unsetPlayer(int cell,int player){
	//mvwprintw(board[listofcell[cell]], posplayer,player," ");
	//wrefresh(board[listofcell[cell]]); 
}

//method to clear all buildings a cell
void Board::clearBuilding(int cell){
	for (int i = 1; i < width-1; i++){
		//mvwprintw(board[listofcell[cell]], posbuilding,i," ");
	}
	//wrefresh(board[listofcell[cell]]); 
}

void Board::setPurchased(int cell){
	clearBuilding(cell);
	//mvwprintw(board[listofcell[cell]], posbuilding,1,"POSSEDEE");
	//wrefresh(board[listofcell[cell]]); 
	
}

void Board::setHouse(int cell,int n_house){
	//n_house is the number of house on a cell after setting a house
	clearBuilding(cell);
	for (int i = 1; i <= n_house; i++){
		//mvwprintw(board[listofcell[cell]], posbuilding,i,"*");
	}
	//wrefresh(board[listofcell[cell]]); 
}
	 

void Board::setHotel(int cell){
	clearBuilding(cell);
	//mvwprintw(board[listofcell[cell]], posbuilding,1,"$");
	//wrefresh(board[listofcell[cell]]); 
}

//method to make the board
void Board::initBoard(){
	this->loadCellNames();    
	this->createBoard();
	//setBoxName();
	//createCardCase();
	//createLegend();
}