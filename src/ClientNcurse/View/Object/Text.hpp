#ifndef _TEXT_HPP
#define _TEXT_HPP

#include <ncurses.h>
#include <vector>
#include <string>
#include <initializer_list>

#include "AbstractViewObject.hpp"
#include "ObjectInfo.hpp"


class Text : public virtual AbstractViewObject {

protected:

	std::vector<std::string> texts;

	int getTextPos(int x) { return info.getWidth()/2 - texts[x].length()/2 -1; }

public:

    explicit Text(ObjectInfo info, std::initializer_list<std::string> sentences) : AbstractViewObject(info), texts{sentences} {
        this->win = newwin(info.getHeight(), info.getWidth(), info.getY(), info.getX());
		this->draw();
	}

	
	virtual void draw() {
		if ( !this->isVisible() ) return;
		int i = 0;
		for (auto txt : texts) i++, mvwprintw(win, i, this->getTextPos(i-1), "%s", txt.c_str());
		this->refresh();
	}

};

#endif
