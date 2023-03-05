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
	bool centered;
	int getTextPos(int x) { return centered ? info.getWidth()/2 - texts[x].length()/2 -1 : 1; }

	int startIdx() { return static_cast<int>(this->texts.size()) > info.getHeight() - 2 ? this->texts.size() - info.getHeight() + 2 : 0; }

public:

    explicit Text(ObjectInfo info, std::initializer_list<std::string> sentences, bool centered=true) : AbstractViewObject(info), texts{sentences} , centered{centered} {
        this->win = newwin(info.getHeight(), info.getWidth(), info.getY(), info.getX());
		this->draw();
	}

	void setText(std::string new_text, int line){texts[line] = new_text;}
	void addText(std::string new_text){texts.push_back(new_text);}

	virtual void draw() {
		if ( !this->isVisible() ) return;
		int line=0;
		for (unsigned int i=this->startIdx(); i<this->texts.size(); i++) {
			mvwprintw(win, ++line, this->getTextPos(i), "%s", this->texts[i].c_str());
		}
		this->refresh();
	}

};

#endif
