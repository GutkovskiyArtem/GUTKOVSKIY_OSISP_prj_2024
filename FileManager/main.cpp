#include <ncurses.h>
#include "tab_manager.h"

int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    TabManager tabManager(maxY, maxX);
    tabManager.createTab();

    int ch;
    while ((ch = getch()) != KEY_F(1)) {
        tabManager.handleInput(ch);
        tabManager.drawCurrentTab();
    }

    endwin();
    return 0;
}
