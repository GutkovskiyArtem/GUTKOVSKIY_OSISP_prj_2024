cmake_minimum_required(VERSION 3.10)

# Имя проекта
project(FileManager)

# Установка стандартов C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Включение всех исходных файлов
set(SOURCES
        main.cpp
        panel.cpp
        tab.cpp
        tab_manager.cpp
        file_operations.cpp
        utils.cpp
)

# Включение всех заголовочных файлов
set(HEADERS
        panel.h
        tab.h
        tab_manager.h
        file_operations.h
        utils.h
)

# Добавление исполняемого файла
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Подключение библиотеки ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})
