// tab_manager.cpp
#include "tab_manager.h"
#include "utils.h"

TabManager::TabManager(int maxY, int maxX)
        : currentTabIndex(0), maxY(maxY), maxX(maxX),leftWindow(newwin(maxY - 1, maxX / 2, 0, 0)),rightWindow(newwin(maxY - 1, maxX / 2, 0, maxX / 2)) {
}

void TabManager::createTab() {
    tabs.emplace_back(".", ".");
    currentTabIndex = tabs.size() - 1;
}

void TabManager::switchTab(int index) {
    if (index >= 0 && index < tabs.size()) {
        currentTabIndex = index;
    }
}

void TabManager::closeTab(int index) {
    if (index >= 0 && index < tabs.size()) {
        tabs.erase(tabs.begin() + index);
        if (currentTabIndex >= tabs.size()) {
            currentTabIndex = tabs.size() - 1;
        }
    }
}

void TabManager::drawCurrentTab() {

        werase(leftWindow);
        werase(rightWindow);
        if (!tabs.empty()) {
            tabs[currentTabIndex].draw(leftWindow, rightWindow);
        }
        drawStatusBar(stdscr, "C: Copy | V: Past | M: Move | N: Create new file | F: Create new folder | D: Delete | R: Rename",maxY-1);
        drawStatusBar(stdscr,"Up/Down: Navigate | Right: Open folder | Left: Go back | TAB: Switch panel | F1: Exit | F2 Create tab | F3/F4: Switch tabs | F5: Close tab",maxY-2);
        drawStatusBar(stdscr,"Tab: " + std::to_string(currentTabIndex + 1),maxY-3);
        wrefresh(leftWindow);
        wrefresh(rightWindow);

}

void TabManager::handleInput(int ch) {
    if (!tabs.empty()) {
        tabs[currentTabIndex].handleInput(ch);
    }
    switch (ch) {
        case KEY_F(1):
            endwin();
            exit(0);
        case KEY_F(2):
            TabManager::createTab();
            break;
        case KEY_F(3):
            if (TabManager::getCurrentTabIndex() > 0) {
                switchTab(currentTabIndex - 1);
            }
            break;
        case KEY_F(4):
            if (currentTabIndex < tabs.size() - 1) {
                switchTab(currentTabIndex + 1);
            }
            break;
        case KEY_F(5):
            if (tabs.size()>1){
                closeTab(currentTabIndex);
            }
            break;
        default:
            break;
    }


}

int TabManager::getCurrentTabIndex() const {
    return currentTabIndex;
}
