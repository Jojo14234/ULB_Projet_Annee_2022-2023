#include "Window.hpp" 

int main() {
    Window win(LINES, COLS, 0, 0);
    win.createBox();
    win.write("CAPITALIST", (LINES-1)/10, (COLS-1)/2 - 4);
    win.cgetch();
    return 0;
}