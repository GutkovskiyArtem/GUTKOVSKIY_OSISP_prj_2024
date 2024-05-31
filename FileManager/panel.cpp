#include "panel.h"
#include <algorithm>
#include <dirent.h>
#include <sys/stat.h>

Panel::Panel(const std::string& path) : currentPath(path), currentSelection(0) {
    loadDirectory(path);
}

void Panel::navigateUp() {
    if (currentSelection > 0) {
        currentSelection--;
    }
}

void Panel::navigateDown() {
    if (currentSelection < contents.size() - 1) {
        currentSelection++;
    }
}
void Panel::scrollUp(WINDOW* window) {
        --scrollPosition;
    draw(window);
}

void Panel::scrollDown(WINDOW* window) {
    if (scrollPosition<0)
        ++scrollPosition;
    draw(window);
}


void Panel::goBack() {
    if (currentPath != "/") {
        size_t pos = currentPath.find_last_of('/');
        if (pos != std::string::npos) {
            loadDirectory(currentPath.substr(0, pos));
        }
    }
}

void Panel::enterDirectory() {
    std::string newPath = currentPath + "/" + contents[currentSelection];
    struct stat s;
    if (stat(newPath.c_str(), &s) == 0 && S_ISDIR(s.st_mode)) {
        loadDirectory(newPath);
    }
}

void Panel::draw(WINDOW* window) {
    werase(window);
    wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    int startY = 1 + scrollPosition;
    for (size_t i = 0; i < contents.size(); ++i) {
        if (i == currentSelection) {
            wattron(window, A_REVERSE);
        }
        mvwprintw(window, i + startY, 1, "%s", contents[i].c_str());
        if (i == currentSelection) {
            wattroff(window, A_REVERSE);
        }
    }
    wrefresh(window);
}




void Panel::loadDirectory(const std::string& path) {
    contents.clear();
    DIR* dir = opendir(path.c_str());
    if (dir) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            contents.push_back(entry->d_name);
        }
        closedir(dir);
    }
    std::sort(contents.begin(), contents.end());
    currentSelection = 0;
    currentPath = path;
}

std::string Panel::getCurrentPath() const {
    return currentPath;
}

std::string Panel::getCurrentSelection() const {
    return contents[currentSelection];
}
