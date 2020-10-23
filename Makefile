all:
	clang++ -std=c++17 -g ./src/*.cpp ./main.cpp -o main -lncurses -lpthread
