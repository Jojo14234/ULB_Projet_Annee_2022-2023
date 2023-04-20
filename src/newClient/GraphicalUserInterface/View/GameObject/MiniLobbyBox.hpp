#ifndef _MINI_LOBBY_BOX_HPP
#define _MINI_LOBBY_BOX_HPP

#include "../Objects/Box.hpp"
#include "../Objects/Text.hpp"
#include "../AssetsPath.hpp"

class MiniLobbyBox : public Box{
	std::vector<std::string> colorlist {"red","blue","yellow","green","magenta","cyan"};
	std::vector<std::shared_ptr<Text>> pseudo_list;

public:
	MiniLobbyBox(ObjectInfo <>info): AbstractViewObject{info}, Box{info} {
		for(int i =0; i< 6; i++){
				sf::Color color;
                if (colorlist[i] == "red"){color = sf::Color::Red;}
                else if (colorlist[i] == "blue"){color = sf::Color::Blue;}
                else if (colorlist[i] == "green"){ color =  sf::Color::Green;}
                else if (colorlist[i] == "magenta"){color = sf::Color::Magenta;}
                else if (colorlist[i] == "cyan"){ color =  sf::Color::Cyan;}
                else if (colorlist[i] == "yellow"){ color = sf::Color::Yellow;}

                pseudo_list.push_back(std::make_shared<Text>(ObjectInfo<>(0,18,info.getX() + 400 - 370  , info.getY() + (i * 60) +30), "0", color));
                pseudo_list[i]->setBold();
            }
	}

	void draw(sf::RenderWindow &window) const override {
		Box::draw(window);
		for (auto& pseudo : pseudo_list){pseudo->draw(window);}
	}

/*	void newPlayer(std::string new_player) {
		int number = pseudo.size() + 1
		push_back(objet text, avec la couleur i+1)
	}*/
};

#endif