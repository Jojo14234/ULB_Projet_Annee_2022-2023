#ifndef _CONNECTION_HPP_
#define _CONNECTION_HPP_

#include <iostream>
#include <string>
#include <ncurses.h>
#include "Window.hpp"

class Connection : public Window {
private:
    string username;
    string password;

public:
    Connection(int height, int width, int starty, int startx);

    void login();

};


#endif // _CONNECTION_HPP_