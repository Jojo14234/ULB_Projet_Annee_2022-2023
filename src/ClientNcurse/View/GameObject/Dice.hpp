#ifndef _DICE_HPP_
#define _DICE_HPP_

#include <stdlib.h>
#include <ncurses.h>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <memory>



#include "../Object/TextBox.hpp"



class Dice: public TextBox {
    public:
        Dice(ObjectInfo info): AbstractViewObject(info), Box(info), Text(info,{"?"}), TextBox{info,{"?"}} {}

        void setDice(int new_number){ setText(std::to_string(new_number),0); }
};



#endif