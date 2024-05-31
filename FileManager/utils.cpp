#include "utils.h"
std::string promptInput(WINDOW *window, const std::string& prompt) {
    werase(window);
    box(window, 0, 0);
    mvwprintw(window, 1, 1, "%s", prompt.c_str());
    wrefresh(window);

    char input[256];
    wgetnstr(window, input, sizeof(input) - 1);
    std::string result(input);

    if (result.empty()) {
        showError("Name cannot be empty!");
        return promptInput(window, prompt);
    }

    return result;
}

void showError(const std::string& message) {
    WINDOW *errorWindow = newwin(3, message.length() + 4, (LINES - 3) / 2, (COLS - message.length()) / 2);
    box(errorWindow, 0, 0);
    mvwprintw(errorWindow, 1, 2, "%s", message.c_str());
    wrefresh(errorWindow);
    getch();
    delwin(errorWindow);
}

void drawStatusBar(WINDOW *window, const std::string& status,int cord) {
    int maxY, maxX;
    getmaxyx(window, maxY, maxX);
    mvwprintw(window, cord, 0, "%s", status.c_str());
    clrtoeol();
    wrefresh(window);
}
std::string getAbsolutePath(const std::string& relativePath) {
    char absolutePath[256];
    if (realpath(relativePath.c_str(), absolutePath) == nullptr) {
        perror("realpath");
        return "";
    }
    return std::string(absolutePath);
}