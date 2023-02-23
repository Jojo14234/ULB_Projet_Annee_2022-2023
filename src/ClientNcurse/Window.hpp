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
    Window(int height, int width, int starty, int startx) {
        // Initialize ncurses
        initscr();

        // Create a new window
        m_window = newwin(height, width, starty, startx);

        // Enable keypad input
        keypad(m_window, true);

        // Disable line buffering and echoing
        cbreak();
        noecho();

        // Hide the cursor
        curs_set(0);

        // Refresh the window
        refresh();
    }

    ~Window() {
        // Clean up ncurses
        delwin(m_window);
        endwin();
    }

    // Write a string to the window
    void write(const char* str, int x, int y) {
        mvwprintw(m_window, x, y, str);
        wrefresh(m_window);
    }

    // Clear the window
    void clear() {
        wclear(m_window);
        wrefresh(m_window);
    }

    // Move the cursor to a specific position in the window
    void move(int y, int x) {
        wmove(m_window, y, x);
        wrefresh(m_window);
    }

    // Wait for a key press and return the key code
    int cgetch() {
        return wgetch(m_window);
    }

    void createBox() {
        box(m_window, 0, 0);
        wrefresh(m_window);
    }

};

#endif // _WINDOW_HPP_
