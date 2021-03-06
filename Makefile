
kompilator=g++
standard=-std=c++14
optymalizacja=-O3
errors=-pedantic-errors -Wall
grafika=-lsfml-graphics -lsfml-window -lsfml-system
debug=#-g
headery= -I header
.PHONY: clean

all : zigiman
	./zigiman


zigiman : bin/obj.o bin/wall.o bin/character.o bin/pacman.o bin/ghost.o bin/points.o  bin/game.o bin/main.o
	$(kompilator) $(headery)  $(standard) $(debug) $(optymalizacja) $(errors)  -o $@ $^   $(grafika)

bin/main.o : src/main.cpp
	$(kompilator) $(headery)  $(standard) $(debug) $(optymalizacja) $(errors) $(grafika) -c -o $@ $^

bin/ghost.o : src/ghost.cpp
	$(kompilator) $(headery)  $(standard) $(debug) $(optymalizacja) $(errors) $(grafika) -c -o $@ $^

bin/character.o : src/character.cpp
	$(kompilator) $(headery)  $(standard) $(debug) $(optymalizacja) $(errors) $(grafika) -c -o $@ $^

bin/pacman.o : src/pacman.cpp
	$(kompilator) $(headery)  $(standard) $(debug) $(optymalizacja) $(errors) $(grafika) -c -o $@ $^

bin/points.o : src/points.cpp
	$(kompilator) $(headery)  $(standard) $(debug) $(optymalizacja) $(errors) $(grafika) -c -o $@ $^


bin/obj.o : src/obj.cpp
	$(kompilator) $(headery)  $(standard) $(debug) $(optymalizacja) $(errors) $(grafika) -c -o $@ $^


bin/wall.o : src/wall.cpp
	$(kompilator) $(headery)  $(standard) $(debug) $(optymalizacja) $(errors) $(grafika) -c -o $@ $^

bin/game.o : src/game.cpp
	$(kompilator) $(headery)  $(standard) $(debug) $(optymalizacja) $(errors) $(grafika) -c -o $@ $^




clean :
	rm bin/*.o
	rm zigiman

d : doxy
	firefox html/index.html

doxy :
	doxygen Doxyfile

c: clean
	git add -A

	