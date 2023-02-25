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
    mvwprintw(m_window, x, y, str);
    wrefresh(m_window);
}

void Window::clear() {
    wclear(m_window);
    wrefresh(m_window);
}

void Window::move(int x, int y) {
    wmove(m_window, x, y);
    wrefresh(m_window);
}

void Window::createBox() {
    box(m_window, 0, 0);
    write("CAPITALIST", (LINES-1)/10, (COLS-1)/2 - 4);
    wrefresh(m_window);
}