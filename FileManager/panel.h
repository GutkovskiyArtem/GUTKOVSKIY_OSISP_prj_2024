#ifndef PANEL_H
#define PANEL_H

#include <ncurses.h>
#include <string>
#include <vector>
#include "utils.h"

class Panel {
public:
    Panel(const std::string& path);
    void navigateUp();
    void navigateDown();
    void scrollUp(WINDOW* window);
    void scrollDown(WINDOW* window);
    void goBack();
    void enterDirectory();
    void draw(WINDOW* window);
    void loadDirectory(const std::string& path);
    std::string getCurrentPath() const;
    std::string getCurrentSelection() const;

private:
    std::string currentPath;
    std::vector<std::string> contents;
    size_t currentSelection;
    int scrollPosition = 0;
};

#endif // PANEL_H
