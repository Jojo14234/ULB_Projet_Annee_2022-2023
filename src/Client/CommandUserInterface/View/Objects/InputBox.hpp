/**
 * Project Untitled
 */

#pragma once

#include <string>
#include <iostream>
#include "Box.hpp"
#include "ObjectInfo.hpp"


class InputBox : public virtual Box {

protected:
	
	std::string text="";
	int cursor=0;

	int getTextPos() { return info.getWidth()/2 - text.length()/2 -1; }
	int getCursorPos() { return this->getTextPos() + cursor +1; }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
	virtual bool inputChecker(char c) { return true; }
#pragma GCC diagnostic pop


	virtual void addChar(char c) { text.insert(cursor, 1, c); }

public:

	explicit InputBox(ObjectInfo info) : AbstractViewObject(info), Box(info) {}

	virtual void draw() override {
		if ( !this->isVisible() ) return;
		this->clear();
		Box::draw();
		mvwprintw(win, 1, this->getTextPos()+1, "%s", text.c_str());
		this->refresh();
	}

	virtual void move() {
		wmove(win, 1, this->getCursorPos());
		this->refresh();
	}

	virtual void reset() { this->text = ""; this->cursor = 0; }

	std::string getText() {
		return text;
	}

	void resetInput() { this->text = ""; this->cursor = 0; }

	void handleInput(int ch) {
		if (ch == KEY_BACKSPACE || ch == KEY_DC || ch == 127 || ch == 65288) {
			// l'utilisateur a appuyé sur la touche "Supprimer/delete", on supprime le caractère précédent
			if (cursor > 0) {
				text.erase(cursor - 1, 1);
				cursor--;
			}
		} else if (ch == KEY_LEFT || ch == 65361) {
			// l'utilisateur a appuyé sur la touche "Gauche", on déplace le curseur à gauche
			if (cursor > 0) {
				cursor--;
			}
		} else if (ch == KEY_RIGHT || ch == 65363) {
			// l'utilisateur a appuyé sur la touche "Droite", on déplace le curseur à droite
			if (cursor < static_cast<int>(text.length())) {
				cursor++;
			}
		} else if (isprint(ch)) {
			// l'utilisateur a entré un caractère imprimable, on l'ajoute au texte
			if (static_cast<int>(text.length()) < info.getWidth() - 2) {
				if (!this->inputChecker(ch)) { return; }
				this->addChar(ch);
				cursor++;
			}
		}
	}

};