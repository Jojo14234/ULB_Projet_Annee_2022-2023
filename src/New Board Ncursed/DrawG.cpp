#include "DrawG.hpp"

DrawGame::DrawGame(int n_player): n_player{n_player}{
    initscr();

    //Disabling display of entered characters
    noecho();

    //hide the cursor
    curs_set(0);  

    //creat a gameboard
    board.setNplayer(n_player);
    board.initBoard();
    for (int i = 1; i <= n_player; i++){
        board.setPlayer(0,i); //(0,i) => 0 = n° box and i = player 
    }
    DrawDice dice1({50,25});
    DrawDice dice2({55,25});
    dice1.drawDice();
    dice2.drawDice();

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



