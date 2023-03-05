#ifndef _JAILCARDSTORAGE_HPP_
#define _JAILCARDSTORAGE_HPP_

#include <stdlib.h>
#include <ncurses.h>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <memory>

#include "TextBox.hpp"

class JailCardStorage: public TextBox{
    public:
        JailCardStorage(ObjectInfo info): TextBox{info,{"Cartes pour sortir de prison :"},false},AbstractViewObject(info),
Box(info),Text(info,{"Cartes pour sortir de prison : 0"},false){}
        void setNumberCard(int new_jcard){setText("Cartes pour sortir de prison : " + std::to_string(new_jcard),0);}

};

#endif
