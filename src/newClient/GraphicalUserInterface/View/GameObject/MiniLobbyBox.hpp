#ifndef _MINI_LOBBY_BOX_HPP
#define _MINI_LOBBY_BOX_HPP

#include "../Objects/Box.hpp"
#include "../Objects/Text.hpp"
#include "../AssetsPath.hpp"

class MiniLobbyBox : public Box{
	std::vector<std::string> colorlist {"red","blue","yellow","green","magenta","cyan"};
	std::vector<std::shared_ptr<Text>> pseudo_list;

public:
	MiniLobbyBox(ObjectInfo <>info, sf::Color color): AbstractViewObject{info}, Box{info, color} {}

	void draw(sf::RenderWindow &window) const override {
		Box::draw(window);
		for (auto& pseudo : pseudo_list){pseudo->draw(window);}
	}

	sf::Color getColor(int i){
		if (colorlist[i] == "red"){return sf::Color::Red;}
        else if (colorlist[i] == "blue"){return sf::Color::Blue;}
        else if (colorlist[i] == "green"){ return  sf::Color::Green;}
        else if (colorlist[i] == "magenta"){return sf::Color::Magenta;}
        else if (colorlist[i] == "cyan"){ return  sf::Color::Cyan;}
        else if (colorlist[i] == "yellow"){ return sf::Color::Yellow;}
	}

	void newPlayerJoin(std::string new_player) {
		int n = pseudo_list.size();
		sf::Color color = getColor(n);
		pseudo_list.push_back(std::make_shared<Text>(ObjectInfo<>(0,18,info.getX() + 400 - 370  , info.getY() + (n * 60) +30), new_player, color));
	}
};

#endif