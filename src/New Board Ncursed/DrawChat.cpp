#include "DrawChat.hpp"

//create a window for the chat 
DrawChat::DrawChat(){
    chat = newwin(chat_size.y-1,chat_size.x-1 ,chat_pos.y +2,chat_pos.x + 2);
    chat_border = newwin(chat_size.y + 2,chat_size.x + 2 ,chat_pos.y,chat_pos.x);
    mvwprintw(chat_border,1,25,"chat");  
    box(chat_border, 0, 0);
    scrollok(chat, true);
    wrefresh(chat);
    wrefresh(chat_border);
    
}

void DrawChat::writeText(){
    curs_set(1);  // Activate the cursor
    wmove(chat, line,1);
    line++;
    wgetstr(chat,input);
    mvwprintw(chat,line, 1, "Vous avez entré : %s", input);
    wrefresh(chat);
    line++;

}

int DrawChat::getLine(){
    return line;
}

WINDOW* DrawChat::getWin(){
    return chat;
}
