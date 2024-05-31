// tab_manager.h
#ifndef TAB_MANAGER_H
#define TAB_MANAGER_H

#include <ncurses.h>
#include <vector>
#include "tab.h"
class Tab;
class TabManager {
public:
    TabManager(int maxY, int maxX);
    void createTab();
    void switchTab(int index);
    void closeTab(int index);
    void drawCurrentTab();
    void handleInput(int ch);
    [[nodiscard]] int getCurrentTabIndex()const ; // Добавлено

private:
    std::vector<Tab> tabs;
    int currentTabIndex ;
    int maxY;
    int maxX;
    WINDOW* leftWindow;
    WINDOW* rightWindow;
};

#endif // TAB_MANAGER_H
