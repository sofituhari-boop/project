CXXFLAGS = -std=c++20 -Wall -Wextra -Wconversion -Werror -g

# Raylib лежит в папке external: заголовочный файл и статическая библиотека.
# -I - где искать .h, -L - где искать библиотеку, -lraylib - какую библиотеку подключить.
RAYLIB_CFLAGS = -Iexternal/raylib/include
RAYLIB_LIBS = -Lexternal/raylib/lib -lraylib

# Библиотеки самой macOS, через которые Raylib открывает окно и рисует.
MACOS_LIBS = -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -framework QuartzCore

# Первое правило - основное: команда make собирает именно его.
tic_tac_toe: main.o logic.o layout.o controller.o graphic.o
	g++ -o tic_tac_toe main.o logic.o layout.o controller.o graphic.o $(RAYLIB_LIBS) $(MACOS_LIBS)

main.o: main.cpp controller.h graphic.h layout.h logic.h
	g++ -c main.cpp $(CXXFLAGS) $(RAYLIB_CFLAGS)

controller.o: controller.cpp controller.h layout.h logic.h
	g++ -c controller.cpp $(CXXFLAGS) $(RAYLIB_CFLAGS)

graphic.o: graphic.cpp graphic.h layout.h logic.h
	g++ -c graphic.cpp $(CXXFLAGS) $(RAYLIB_CFLAGS)

logic.o: logic.cpp logic.h
	g++ -c logic.cpp $(CXXFLAGS)

layout.o: layout.cpp layout.h logic.h
	g++ -c layout.cpp $(CXXFLAGS)

tests.o: tests.cpp layout.h logic.h
	g++ -c tests.cpp $(CXXFLAGS)

run_tests: tests.o logic.o layout.o
	g++ -o run_tests tests.o logic.o layout.o

# Эти цели - команды, а не файлы.
.PHONY: run test clean

run: tic_tac_toe
	./tic_tac_toe

test: run_tests
	./run_tests

clean:
	rm -f *.o tic_tac_toe run_tests
