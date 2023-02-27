#ifndef _MENU_VIEW_HPP
#define _MENU_VIEW_HPP

#include "AbstractView.hpp"
#include "Object/TextButton.hpp"
#include "Object/InputButtonBox.hpp"
#include "Object/IntInputButtonBox.hpp"
#include "Object/TextBox.hpp"
#include "Object/Text.hpp"


class MenuView : public AbstractView {

	InputButtonBox console{ObjectInfo{LINES-6, COLS/2-14, 3, COLS/2+6}};
	IntInputButtonBox join{ObjectInfo{3, 7, LINES/2 + 2, COLS/4 - 3}};
	
	TextButton disconnect{ObjectInfo{3, 20, LINES - 7, COLS/4 - 10}, "Deconnexion"};
	
	Text join_txt{ObjectInfo{3, 22, LINES/2, COLS/4 - 11}, {"Rejoindre une partie:"} };
	Text error_txt{ObjectInfo{3, 25, LINES/2 + 4, COLS/4 - 12}, {"Aucune partie trouvée !"} };
	TextBox infos_txt{ObjectInfo{10, 30, 3, COLS/4 - 15}, "Liste des commandes:"};
	Text commands_txt{ObjectInfo{10, 30, 5, COLS/4 - 15}, {"/create", "/friends -> list, add, accept, decline, remove", "/rank -> top, pos", "/msg -> list, send"}};

public:

	MenuView(Client* client) : AbstractView(client) {
		this->error_txt.setHidden();
	}
	
	void draw() override {
		infos_txt.draw();
		commands_txt.draw();
		join_txt.draw();
		join.draw();
		error_txt.draw();
		disconnect.draw();
		console.draw();
	}

	InputButtonBox* getConsoleInputBox() { return &console; }	
	IntInputButtonBox* getJoinInputBox() { return &join; }

	TextButton* getDisconnectButton() { return &disconnect; }

};

#endif
