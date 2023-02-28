#include "Board.hpp"


void Board::draw(){
	for (int i=0; i<board_box_nb; i++) drawBox(i);
}

//method to have a list of name for the cells
std::vector<std::string> Board::getCellName(){
	std::ifstream cells("cardname.txt");
	std::vector <std::string> listofcell;
	std::string cell;
	while (getline(cells , cell)){
	   listofcell.push_back(cell);}
	cells.close();
	return listofcell;
}

////////////////////////////////////////////////////////////////
//define + create board
//method to define the borders of each gamebox
void Board::drawBox(int n_case){
	//wborder :Left border, Right border, Top / Upper, Bottom / Lower, Top left corner, Top right corner, Bottom left corner, Bottom right corner.
	//Top left corner
	if ( n_case == 0){
		wborder(board[n_case], '|', '|', '-', '_', '+', '-', '|', '|');}
	//Top right corner
	else if (n_case == col_nb - 1){
		wborder(board[n_case], ' ', '|', '-', '_', '-', '+', '_', '|');}
	//Bottom left corner
	else if( n_case == (line_nb-1) * col_nb){
		wborder(board[n_case], '|', '|', ' ', '-', '|', '|', '+', '-');}
	//Bottom right corner
	else if( n_case == line_nb * col_nb - 1){
		wborder(board[n_case], ' ', '|', ' ', '-', ' ', '|', '-', '+');}
	//Top cells
	else if (n_case / 11 == 0){
		wborder(board[n_case], ' ', '|', '-', '_', '-', '-', '_', '|');}
	//Bottom cells
	else if (n_case / ((line_nb-1) * col_nb) == 1){
		wborder(board[n_case], ' ', '|', ' ', '-', ' ', '|', '-', '-');}
	//Left cells
	else if(n_case % line_nb == 0){
		wborder(board[n_case], '|', '|', ' ', '_', '|', '|', '|', '|');}
	//Right cells
	else if( (n_case+1) % line_nb == 0){
		wborder(board[n_case], ' ', '|', ' ', '_', ' ', '|', '_', '|');}
	//internal borders bottom right corner
	else if(n_case == 108){
		wborder(board[n_case], ' ', '|', ' ', '_', ' ', '|', '_', '|');}
	//internal borders bottom 
	else if(n_case >=100 and n_case < 109){  
		wborder(board[n_case], ' ', ' ', ' ', '_', ' ', ' ', '_', '_');}
	//internal borders right 
	else if (n_case % 11 == 9){
		wborder(board[n_case], ' ', '|', ' ', ' ', ' ', '|', ' ', '|');}
	wrefresh(board[n_case]);
}

//method to create the gameboard
void Board::createBoard(){
	int n = 0;
	//define positions for each box 
	for (int i = 0; i <  col_nb; i++){
		for (int j = 0; j < line_nb; j++) {
			int x = j * width;
			int y = i * height;
			board[n] = newwin(height , width, y , x ); //rigjeroigjioerjgioerjgioejgioejrgierjgoiejgioerjgireogjie
			n++;}}

	//draw boxes
	for (int k = 0; k < n; k++) {
		drawBox(k);
	}
}

//method to put name on each box
void Board::setBoxName(){
	for (int i =  0; i < gamebox_nb; i ++){
		mvwprintw(board[listofcell[i]], pos_text1.getY(), pos_text1.getX(), "%s", (cellname[i]).c_str());
		wrefresh(board[listofcell[i]]); 
	}
}

//method to destroy the gameboard
void Board::destroyBoard(){
	for (int i = 0; i <  board_box_nb ; i++) delwin(board[i]);
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
	mvwprintw(board[listofcell[cell]], posplayer,player, "%s",std::to_string(player).c_str());
	wrefresh(board[listofcell[cell]]);  
}
 
void Board::unsetPlayer(int cell,int player){
	mvwprintw(board[listofcell[cell]], posplayer,player," ");
	wrefresh(board[listofcell[cell]]); 
}

//method to clear all buildings a cell
void Board::clearBuilding(int cell){
	for (int i = 1; i < width-1; i++){
		mvwprintw(board[listofcell[cell]], posbuilding,i," ");
	}
	wrefresh(board[listofcell[cell]]); 
}

void Board::setPurchased(int cell){
	clearBuilding(cell);
	mvwprintw(board[listofcell[cell]], posbuilding,1,"POSSEDEE");
	wrefresh(board[listofcell[cell]]); 
	
}

void Board::setHouse(int cell,int n_house){
	//n_house is the number of house on a cell after setting a house
	clearBuilding(cell);
	for (int i = 1; i <= n_house; i++){
		mvwprintw(board[listofcell[cell]], posbuilding,i,"*");
	}
	wrefresh(board[listofcell[cell]]); 
}
	 

void Board::setHotel(int cell){
	clearBuilding(cell);
	mvwprintw(board[listofcell[cell]], posbuilding,1,"$");
	wrefresh(board[listofcell[cell]]); 
}

//method to make the board
void Board::initBoard(){
	cellname = getCellName();    
	createBoard();
	setBoxName();
	createCardCase();
	createLegend();
}