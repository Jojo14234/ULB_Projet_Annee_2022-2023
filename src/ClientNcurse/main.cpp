#include "Window.hpp"

int main() {
	Window win(LINES, COLS, 0, 0);
    win.createBox();
    win.cgetch();
    return 0;
}
