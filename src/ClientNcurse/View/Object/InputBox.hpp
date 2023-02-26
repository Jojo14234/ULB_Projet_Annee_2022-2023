#ifndef _INPUT_BOX_HPP
#define _INPUT_BOX_HPP

#include <string>

#include "Box.hpp"
#include "ObjectInfo.hpp"


class InputBox : public Box {

protected:
	
    std::string text="";
    int cursor=0;

public:

	using Box::Box;

    void handleInput(int ch) {
        if (ch == '\n') {
            // l'utilisateur a appuyé sur la touche "Entrée", on vide le texte
            text = "";
            cursor = 0;
        } else if (ch == KEY_BACKSPACE) {
            // l'utilisateur a appuyé sur la touche "Retour", on supprime le caractère précédent
            if (cursor > 0) {
                text.erase(cursor - 1, 1);
                cursor--;
            }
        } else if (ch == KEY_LEFT) {
            // l'utilisateur a appuyé sur la touche "Gauche", on déplace le curseur à gauche
            if (cursor > 0) {
                cursor--;
            }
        } else if (ch == KEY_RIGHT) {
            // l'utilisateur a appuyé sur la touche "Droite", on déplace le curseur à droite
            if (cursor < static_cast<int>(text.length())) {
                cursor++;
            }
        } else if (isprint(ch)) {
            // l'utilisateur a entré un caractère imprimable, on l'ajoute au texte
            if (static_cast<int>(text.length()) < info.getWidth() - 2) {
                text.insert(cursor, 1, ch);
                cursor++;
            }
        }
    }

    virtual void draw() {
        // dessiner la boîte parent
        Box::draw();
        // dessiner le texte
        mvwprintw(win, 1, 1, "%s", text.c_str());
        // dessiner le curseur
        wmove(win, 1, cursor + 1);
		this->refresh();
	}

    std::string getText() {
        return text;
    }

};

#endif
