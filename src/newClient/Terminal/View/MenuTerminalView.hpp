/**
 * Project Untitled
 */

#pragma once

#include "AbstractTerminalView.hpp"
#include "Objects.hpp"


class MenuTerminalController; // forward declaration

class MenuTerminalView: public AbstractTerminalView {

	InputButtonFrame console{ObjectInfo{LINES-6, COLS/2-14, 3, COLS/2+6}};
	IntInputButtonBox join{ObjectInfo{3, 7, LINES/2 + 2, COLS/4 - 3}};
	
	TextButton disconnect{ObjectInfo{3, 20, LINES - 7, COLS/4 - 10}, "Deconnexion"};
	
	Text join_txt{ObjectInfo{3, 22, LINES/2, COLS/4 - 11}, {"Rejoindre une partie:"} };
	Text error_txt{ObjectInfo{3, 25, LINES/2 + 4, COLS/4 - 12}, {"Aucune partie trouvée !"} };
	TextBox infos_txt{ObjectInfo{10, 50, 3, COLS/4 - 15}, {"Liste des commandes:"}};
	Text commands_txt{ObjectInfo{10, 50, 5, COLS/4 - 15}, {"/create", "/friends -> list, add, accept, decline, remove", "/rank -> top, pos", "/msg -> list, send"}};

public: 
	
	MenuTerminalView();
	
	~MenuTerminalView()=default;

	void draw() override;

	friend class MenuTerminalController;

};