#include "Window.hpp" 

int main() {
    Window win(COLS, LINES, 0, 0);
    win.createBox();
    win.write("Hello, world!", COLS/20, LINES);
    win.write(to_string(LINES).c_str(), 10, 5);
    win.cgetch();
    return 0;
}