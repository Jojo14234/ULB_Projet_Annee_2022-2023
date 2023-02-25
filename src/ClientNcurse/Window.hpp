#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_


#include <ncurses.h>
#include <iostream>
#include <string>

using namespace std;

class Window {
private:
    WINDOW* m_window;
public:
    Window(int height, int width, int starty, int startx);
    ~Window();

    // Write a string to the window
    void write(const char* str, int x, int y);

    // Clear all the window
    void clear();

    void clearBox(int startLine, int startCol, int endLine, int endCol);

    // Move the cursor to a specific position in the window
    void move(int y, int x);

    // Wait for a key press and return the key code
    int cgetch() { return wgetch(m_window); }

    void createBox(const char* text);

};

#endif // _WINDOW_HPP_
