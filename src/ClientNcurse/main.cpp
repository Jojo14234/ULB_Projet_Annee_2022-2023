#include "Window.hpp"
#include "Connection.hpp"
/*
int main() {
	Window win(LINES, COLS, 0, 0);
    win.createBox("CAPITALI$T");
    win.cgetch();
    return 0;
}*/
int main() {
    Connection connection(LINES, COLS, 0, 0);
    connection.login();
    return 0;
}