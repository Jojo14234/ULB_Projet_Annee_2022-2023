//
// Created by Rémy Ryckeboer on 25/03/2023.
//

#ifndef INFO_F209_GR5_2022_MAINCLIWINDOW_HPP
#define INFO_F209_GR5_2022_MAINCLIWINDOW_HPP

#include "../AbstractMainWindow.hpp"



class MainCliWindow : public AbstractMainWindow<STATE, int > {

public:
    void mainLoop();
};


#endif //INFO_F209_GR5_2022_MAINCLIWINDOW_HPP
