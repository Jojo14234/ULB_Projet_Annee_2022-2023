#include "Window.hpp" 

Window::Window(int height, int width, int starty, int startx) {
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

Window::~Window() {
    // Clean up ncurses
    delwin(m_window);
    endwin();
}

void Window::write(const char* str, int x, int y) {
    mvwprintw(m_window, x, y, "%s", str);
    wrefresh(m_window);
}

void Window::clear() {
    wclear(m_window);
    wrefresh(m_window);
}

void Window::clearBox(int startLine, int startCol, int endLine, int endCol) {
    for (int i = startLine; i <= endLine; i++) {
        for (int j = startCol; j <= endCol; j++)
            mvwprintw(m_window, i, j, " ");
    }
}

void Window::move(int x, int y) {
    wmove(m_window, x, y);
    wrefresh(m_window);
}

void Window::createBox(const char* text) {
    box(m_window, 0, 0);
    write(text, (LINES-1)/12, (COLS-1)/2 - 4);
    wrefresh(m_window);
}