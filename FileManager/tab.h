#ifndef TAB_H
#define TAB_H

#include "panel.h"
#include "string.h"
#include "tab_manager.h"

class Tab {
public:
    Tab(const std::string& leftPath, const std::string& rightPath);
    void switchActivePanel();
    void draw(WINDOW* leftWindow, WINDOW* rightWindow);
    void handleInput(int ch);
    std::string getCurrentSelection() const;

private:
    Panel leftPanel;
    Panel rightPanel;
    std::string path;
    std::string name;
    int activePanelIndex;
    Panel* activePanel;
};

#endif // TAB_H
