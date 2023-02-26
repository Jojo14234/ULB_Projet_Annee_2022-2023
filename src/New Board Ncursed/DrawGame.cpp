#include <iostream>


#include "DrawBoard.hpp"
#include "DrawChat.hpp"
#include "DrawDice.hpp"
#include "DrawMoney.hpp"
#include "DrawInfo.hpp"
#include "DrawChoice.hpp"

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



    //create zone text
    DrawChat chat;



    //create zone for action + tester afficher des texte
    vector<string> a {"j2 va sur jaune2","jaune2 est possédé par j3","j2 doit 300e à j3","j2 perd 300e","j3 reçoit 300e",
                "j2 est dégouté", "c la hess", "j2 pense à mettre fin à sa vie", "j2 hésite", "que doit faire j2","aider le",
                "voici les actions disponibles" };
    DrawInfo info;

    //exemple comment imprimer du texte ds la zone
    for ( auto i : a){
        info.printText(i);
    }

    //create zone for choice action
    vector<string> b {"Finir le tour", "Placer des bâtiments","Négocier"};
    DrawChoice choice(3,b);  //parametre: nombre de choix + liste de choix

    //le choix est ensuite imprimé dans le zone de texte (info)
    string res = "j2 décide de " + choice.getChoice();
    info.printText(res);
    //on supprime les choix à la fin
    choice.delChoice();



    //permettre d'ecrire dans un chat
    int key;
    bool flag = true;

    
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
