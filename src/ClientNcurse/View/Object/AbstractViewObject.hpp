#ifndef _ABSTRACT_VIEW_OBJECT_HPP
#define _ABSTRACT_VIEW_OBJECT_HPP

#include <ncurses.h>

#include "ObjectInfo.hpp"


class AbstractViewObject {

	bool visible = true;

protected:

	ObjectInfo info;
	WINDOW* win;

public:

	AbstractViewObject(ObjectInfo info) : info(info) {
		win = newwin(info.getHeight(), info.getWidth(), info.getY(), info.getX());
	}
	AbstractViewObject(int height, int width, int y, int x) : info(height, width, y, x) {
		win = newwin(info.getHeight(), info.getWidth(), info.getY(), info.getX());
	}

	virtual ~AbstractViewObject() { delwin(this->win); }

	virtual void draw() = 0;

    void refresh() { wrefresh(this->win); }	
	void clear() { werase(this->win); wrefresh(this->win); }

	// GETTERS
	ObjectInfo getInfo() const { return this->info; }

	bool isVisible() const { return this->visible; }
	
	// SETTERS
	void setVisible() { this->visible = true; }
	void setInvisible() { this->visible = false; }

};

#endif
