#include "Board_Creator.hpp"

BoardCreator::BoardCreator(int n_player): n_player{n_player}{
    }


vector<string> BoardCreator::getCellName(){
    ifstream cells("cardname.txt");
    vector <string> listofcell;
    string cell;
    while (getline(cells , cell)){
       listofcell.push_back(cell);}
    cells.close();
    return listofcell;
}

void BoardCreator::drawBoard(int n_case){
    //case zero
    if ( n_case == 0){
        wborder(board[n_case], '|', '|', '-', '_', '-', '-', '|', '|');}
    //cases du haut
    else if (n_case >0 and n_case < 11){
        wborder(board[n_case], ' ', '|', '-', '_', '-', '-', '_', '|');}
    //case du bas
    else if (n_case >=111 and n_case <= 120){
        wborder(board[n_case], ' ', '|', ' ', '_', ' ', '|', '_', '|');}
    //case des colonnes
    else if( n_case % 11 == 0 or (n_case + 1) % 11 == 0 ){
            wborder(board[n_case], '|', '|', ' ', '_', '|', '|', '|', '|');}
    //bordure de la case du bas
    else if(n_case >=100 and n_case < 109){  
            wborder(board[n_case], ' ', ' ', ' ', '_', ' ', ' ', '_', '_');}
    wrefresh(board[n_case]);
}

void BoardCreator::text(){
    for (int i = 0; i< n_cell; i ++){
       mvwprintw(board[listofcell[i]], pos_text1.y, pos_text1.x,(cellname[i]).c_str());
    wrefresh(board[listofcell[i]]); 
    }}

void BoardCreator::legend(){
    WINDOW *legend;
    legend = newwin( legend_size.y , legend_size.x , legend_pos.y , legend_pos.x);
    wborder(legend, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwprintw(legend, pos_text1.y, pos_text1.x, "Légende");
    mvwprintw(legend, pos_text2.y, pos_text2.x, "* : maison");
    mvwprintw(legend, pos_text3.y, pos_text3.x, "$ : hotel");
    mvwprintw(legend, pos_text4.y, pos_text4.x, "1-6 : Joueur");
    wrefresh(legend);  

}

void BoardCreator::createCardCase(){
    cardcases[0] = newwin(cardcasesize.y, cardcasesize.x, luckycasepos.y , luckycasepos.x );
    wborder(cardcases[0], '|', '|', '-', '-', '+', '+', '+', '+');
    mvwprintw(cardcases[0], pos_text5.y,pos_text5.x, "CARTE CHANCE");
    wrefresh(cardcases[0]);

    cardcases[1] = newwin(cardcasesize.y, cardcasesize.x, commucasepos.y  , commucasepos.x );
    wborder(cardcases[1], '|', '|', '-', '-', '+', '+', '+', '+');
    mvwprintw(cardcases[1],pos_text6.y,pos_text6.x, "CAISSE DE COMMUNAUTE");
    wrefresh(cardcases[1]);
}

void BoardCreator::setPlayer(int cell,int player){
    mvwprintw(board[listofcell[cell]], posplayer,player, to_string(player).c_str());
    wrefresh(board[listofcell[cell]]);  
}

void BoardCreator::unsetPlayer(int cell,int player){
    mvwprintw(board[listofcell[cell]], posplayer,player," ");
    wrefresh(board[listofcell[cell]]); 
}

void BoardCreator::setHouse(int cell){
   
}
void BoardCreator::unsetHouse(int cell){}
void BoardCreator::setHotel(int cell){}
void BoardCreator::unsetHotel(int cell){}


void BoardCreator::createBoard(){
    int n = 0;
    for (int i = 0; i <  size; i++){
        for (int j = 0; j < size ; j++) {
            int x = j * width;
            int y = i * height;
            board[n] = newwin(height , width, y , x );
            n++;}}
    for (int k = 0; k < n; k++) {
        drawBoard(k);
    }
    

}

void BoardCreator::destroyBoard(){
    for (int i = 0; i < size*size; i++) {
        delwin(board[i]);
    }
}

void BoardCreator::initBoard(){
    cellname = getCellName();
    initscr();
    createBoard();
    createCardCase();
    text();
    legend();
    for (int i = 1; i <= n_player; i++){
        setPlayer(0,i);
    }
    setHouse(0);
    WINDOW *chat;
    chat = newwin( 2 , 2, 25 , COLS - 10);
    //nodelay(stdscr, false);
    int key;
    bool flag = true;
    while(flag){
        key = wgetch(chat); // On attend que l'utilisateur appui sur une touche pour quitter
        if (key == 'e'){
            flag = false;
            destroyBoard(); 
            endwin();       // Restaure les paramètres par défaut du terminal
        }
    }
}