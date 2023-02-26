#ifndef _CLIENT_WINDOW_HPP
#define _CLIENT_WINDOW_HPP

#include <ncurses.h>


class Window {

	WINDOW* win;


public:

	Window(int x, int y):win{newwin(x, y, 0, 0)} {
		box(win, 0, 0);
		mvwprintw(win, 1, 1, "Entrez un texte :");
		wrefresh(win);
	}

	void eventLoop() {
		while(true)
		
	}

}


#endif