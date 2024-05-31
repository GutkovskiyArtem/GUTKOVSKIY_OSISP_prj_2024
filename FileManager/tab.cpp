#include "tab.h"
#include "file_operations.h"
#include "utils.h"

Tab::Tab(const std::string& leftPath, const std::string& rightPath)
        : leftPanel(leftPath), rightPanel(rightPath), activePanelIndex(0), activePanel(&leftPanel) {}

void Tab::switchActivePanel() {
    activePanelIndex = (activePanelIndex + 1) % 2;
    activePanel = (activePanelIndex == 0) ? &leftPanel : &rightPanel;
}

void Tab::draw(WINDOW* leftWindow, WINDOW* rightWindow) {
    leftPanel.draw(leftWindow);
    rightPanel.draw(rightWindow);
    activePanel = (activePanelIndex == 0) ? &leftPanel : &rightPanel;
    drawStatusBar(stdscr, getAbsolutePath(activePanel->getCurrentPath()),0);
}

void Tab::handleInput(int ch) {

    switch (ch) {
        case KEY_UP:
            activePanel->navigateUp();

            break;
        case KEY_DOWN:
            activePanel->navigateDown();

            break;
        case '-':
            activePanel->scrollUp(stdscr);
            break;
        case '+':
            activePanel->scrollDown(stdscr);
            break;
        case KEY_LEFT:
            activePanel->goBack();
            break;
        case KEY_RIGHT:
            activePanel->enterDirectory();
            break;
        case '\t':
            switchActivePanel();
            break;
        case 'c':
            name = getCurrentSelection();
            path = activePanel->getCurrentPath();
            break;
        case 'v':
            if (path!="" && !FileOperations::fileExists(activePanel->getCurrentPath() + "/" + name) ){
                FileOperations::paste(path + "/" + name, activePanel->getCurrentPath() + "/" + name);
            } else{
                showError("Error: file already exist or path is empty. copy first!");
            }

            activePanel->loadDirectory(activePanel->getCurrentPath());
            wrefresh(stdscr);
            break;
        case 'm':
            if (path!="" && !FileOperations::fileExists(activePanel->getCurrentPath() + "/" + name) ){
                FileOperations::move(path + "/" + name, activePanel->getCurrentPath() + "/" + name);
            }else{
                showError("Error: file already exist or path is empty. copy first!");
            }

            activePanel->loadDirectory(activePanel->getCurrentPath());
            wrefresh(stdscr);
            break;
        case 'd':
            FileOperations::remove(activePanel->getCurrentPath() + "/" + getCurrentSelection());
            activePanel->loadDirectory(activePanel->getCurrentPath());
            wrefresh(stdscr);
            break;
        case 'n': {
            std::string newFileName = promptInput(stdscr, "New file name: ");
            std::string newFilePath = activePanel->getCurrentPath() + "/" + newFileName;
            if (!FileOperations::fileExists(newFilePath)) {
                FileOperations::createFile(newFilePath);
                activePanel->loadDirectory(activePanel->getCurrentPath());
            } else {
                showError("File already exists!");
            }
            wrefresh(stdscr);
            break;
        }
        case 'f': {
            std::string newDirName = promptInput(stdscr, "New directory name: ");
            std::string newDirPath = activePanel->getCurrentPath() + "/" + newDirName;
            if (!FileOperations::fileExists(newDirPath)) {
                FileOperations::createDirectory(newDirPath);
                activePanel->loadDirectory(activePanel->getCurrentPath());
            } else {
                showError("Directory already exists!");
            }
            wrefresh(stdscr);
            break;
        }
        case 'r': {
            FileOperations::rename(activePanel->getCurrentPath() + "/" + getCurrentSelection(), activePanel->getCurrentPath() + "/" + promptInput(stdscr, "New name: "));
            activePanel->loadDirectory(activePanel->getCurrentPath());
            wrefresh(stdscr);
            break;

        }
        default:
            break;
    }
}

std::string Tab::getCurrentSelection() const {
    return activePanel->getCurrentSelection();
}
