FLAGS=-lGL -lglfw -ldl -I"irrKlang-64bit-1.5.0/include" -L"/usr/lib" irrKlang-64bit-1.5.0/bin/linux-gcc-64/libIrrKlang.so -pthread -std=c++11

all: game

game: main.o dont-touch.o bricks.o baskets.o background.o laserGun.o mirrors.o glad.c
	g++ -o game main.o dont-touch.o bricks.o baskets.o background.o laserGun.o mirrors.o glad.c $(FLAGS)

main.o: main.cpp glad.c
	g++ -c main.cpp glad.c $(FLAGS)

dont-touch.o: dont-touch.cpp glad.c
	g++ -c dont-touch.cpp glad.c $(FLAGS)

bricks.o: bricks.cpp glad.c
	g++ -c bricks.cpp glad.c $(FLAGS)

baskets.o: baskets.cpp glad.c
	g++ -c baskets.cpp glad.c $(FLAGS)

background.o: background.cpp glad.c
	g++ -c background.cpp glad.c $(FLAGS)

laserGun.o: laserGun.cpp glad.c
	g++ -c laserGun.cpp glad.c $(FLAGS)

mirrors.o: mirrors.cpp glad.c
	g++ -c mirrors.cpp glad.c $(FLAGS)

clean:
	rm *.o game
