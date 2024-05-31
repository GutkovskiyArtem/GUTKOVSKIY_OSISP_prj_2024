# Название проекта
TARGET = FileManager

# Компилятор и флаги компиляции
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Файлы проекта
SRCS = main.cpp file_operations.cpp panel.cpp tab.cpp tab_manager.cpp utils.cpp
HEADERS = file_manager.h

# Объектные файлы
OBJS = $(SRCS:.cpp=.o)

# Библиотеки для линковки
LIBS = -lncurses

# Цель по умолчанию
all: $(TARGET)

# Правила сборки
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(TARGET) $(OBJS)

# Установка и очистка
rebuild: clean all
