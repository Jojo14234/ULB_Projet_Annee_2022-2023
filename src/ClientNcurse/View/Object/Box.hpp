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
        this->win = newwin(info.getHeight(), info.getWidth(), info.getY(), info.getX());
		this->draw();
	}

	~Box() { delwin(this->win); }

    void refresh() { wrefresh(this->win); }
	
	void clear() { werase(this->win); wrefresh(this->win); }

	virtual void draw() {
		box(this->win, 0, 0);
		this->refresh();
	}

};

#endif
