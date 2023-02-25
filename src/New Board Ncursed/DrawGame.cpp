#include <iostream>


#include "DrawBoard.hpp"
#include "DrawChat.hpp"
#include "DrawDice.hpp"
#include "DrawMoney.hpp"

int drawGame(int nplayer){
    int n_player = nplayer;
    initscr();

    //hide the cursor
    curs_set(0);  

    //creat a gameboard
    DrawBoard board;
    board.setNplayer(n_player);
    board.initBoard();

    //test - initialiser les joueurs
    for (int i = 1; i <= n_player; i++){
        board.setPlayer(0,i); //(0,i) => 0 = n° box and i = player 
    }

    //create 2 dice + print them
    DrawDice dice1({50,25});
    DrawDice dice2({55,25});
    dice1.drawDice();
    dice2.drawDice();

    //test - initialiser le dé
    dice1.setDice(4);
    dice2.setDice(3);



    //create money zone and print + test changer argent d'un joueur

    DrawMoney zone(n_player, 1000);
    zone.changeMoney(4,980);


    //creater chat
    int key;
    bool flag = true;

    DrawChat chat;
    while(flag){
        chat.writeText();
        wmove(chat.getWin(), chat.getLine(), 1);
        key = wgetch(chat.getWin());  //wait for the user press a button to quit 
        if (key == 65307){
            flag = false;
            board.destroyBoard();
            endwin();       //restore default settings
        }
    }

    

}

int main(){
    drawGame(6);
}
