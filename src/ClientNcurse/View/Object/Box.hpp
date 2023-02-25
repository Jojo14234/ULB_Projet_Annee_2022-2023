#ifndef _BOX_HPP
#define _BOX_HPP

#include <ncurses.h>

#include "AbstractViewObject.hpp"
#include "ObjectInfo.hpp"


class Box : public AbstractViewObject {

protected:

    WINDOW* win;

public:

    Box(ObjectInfo info) : AbstractViewObject(info) {
        win = newwin(info.getHeight(), info.getWidth(), info.getY(), info.getX());
		box(win, 0, 0);
		this->refresh();
	}

	~Box() { delwin(win); }

    void refresh() { wrefresh(win); }
	
	void clear() { werase(win); wrefresh(win); }

	virtual void draw() {
		box(win, 0, 0);
		this->refresh();
	}

};

#endif
