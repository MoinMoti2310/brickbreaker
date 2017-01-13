all: sample2D

sample2D: main.cpp glad.c
	g++ -o sample2D main.cpp glad.c -lGL -lglfw -ldl

clean:
	rm sample2D
