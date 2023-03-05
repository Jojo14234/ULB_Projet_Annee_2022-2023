#ifndef _INFORMATION_BOX_HPP_
#define _INFORMATION_BOX_HPP_

#include <stdlib.h>
#include <ncurses.h>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <memory>

#include "../Object/TextBox.hpp"

class InformationBox: public TextBox{

public:
	InformationBox(ObjectInfo info): 
		TextBox{info,{"Cartes pour sortir de prison :"},false},
		AbstractViewObject(info),
		Box(info),
		Text(info,{"Cartes pour sortir de prison : 0"},false){}

	void setNumberCard(int new_jcard){
		setText("Cartes pour sortir de prison : " + std::to_string(new_jcard),0);
	}

};

#endif
