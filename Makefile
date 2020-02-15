all:
	g++ -c main.cpp -o main.o
	g++ -o minesweeper main.o -lsfml-graphics -lsfml-window -lsfml-system
