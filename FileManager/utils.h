#ifndef UTILS_H
#define UTILS_H

#include <ncurses.h>
#include <string>

std::string promptInput(WINDOW *window, const std::string& prompt);
void showError(const std::string& message);
void drawStatusBar(WINDOW *window, const std::string& status,int cord);
std::string getAbsolutePath(const std::string& relativePath);
#endif // UTILS_H
