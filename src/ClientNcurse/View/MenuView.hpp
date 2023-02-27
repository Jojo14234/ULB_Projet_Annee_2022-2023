#ifndef _MENU_VIEW_HPP
#define _MENU_VIEW_HPP

#include "AbstractView.hpp"
#include "Object/TextButton.hpp"
#include "Object/InputButtonBox.hpp"
#include "Object/TextBox.hpp"
#include "Object/Text.hpp"


class MenuView : public AbstractView {

	InputButtonBox console{ObjectInfo{LINES-6, COLS/2-14, 3, COLS/2+6}};
	InputButtonBox gameCode{ObjectInfo{3, 7, LINES/2 + 2, COLS/4 - 3}};
	
	TextButton disconnect{ObjectInfo{3, 20, LINES - 7, COLS/4 - 10}, "Déconnexion"};
	
	Text join{ObjectInfo{3, 22, LINES/2, COLS/4 - 11}, {"Rejoindre une partie:"} };
	Text error{ObjectInfo{3, 25, LINES/2 + 4, COLS/4 - 12}, {"Aucune partie trouvée !"} };
	TextBox informations{ObjectInfo{10, 30, 3, COLS/4 - 15}, "Liste des commandes:"};
	Text commands{ObjectInfo{10, 30, 5, COLS/4 - 15}, {"/friends", "/create", "/top", "/tBoGogo"}};

public:

	MenuView(Client* client) : AbstractView(client) {
		this->error.setHidden();
	}
	
	void draw() override {
		informations.draw();
		commands.draw();
		join.draw();
		gameCode.draw();
		error.draw();
		disconnect.draw();
		console.draw();
	}

	InputBox* getConsoleInputBox() { return &console; }	
	InputBox* getGameCodeInputBox() { return &gameCode; }

	TextButton* getDisconnectButton() { return &disconnect; }

};

#endif
