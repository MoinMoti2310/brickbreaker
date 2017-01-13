FLAGS=-lGL -lglfw -ldl

all: game

game: main.o dont-touch.o glad.c
	g++ -o game main.o dont-touch.o glad.c $(FLAGS)

main.o: main.cpp glad.c
	g++ -c main.cpp glad.c $(FLAGS)

dont-touch.o: dont-touch.cpp glad.c
	g++ -c dont-touch.cpp glad.c $(FLAGS)

clean:
	rm *.o game
