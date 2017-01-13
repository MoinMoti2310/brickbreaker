all: game

game: main.cpp glad.c
	g++ -o game main.cpp glad.c -lGL -lglfw -ldl

clean:
	rm game
