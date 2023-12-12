CC := g++
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: starwars.out

starwars.out: main.o rsdl.o spaceship.o enemy.o bullet.o walking_enemy.o hero.o game.o
	$(CC) main.o rsdl.o spaceship.o enemy.o bullet.o walking_enemy.o hero.o game.o $(CCFLAGS) -o starwars.out

main.o: rsdl.hpp spaceship.hpp enemy.hpp bullet.hpp walking_enemy.hpp hero.hpp game.hpp main.cpp 
	$(CC) -c main.cpp -o main.o
rsdl.o: rsdl.hpp rsdl.cpp
	$(CC) -c rsdl.cpp -o rsdl.o
spaceship.o: spaceship.hpp rsdl.hpp defines.hpp spaceship.cpp
	$(CC) -c spaceship.cpp -o spaceship.o
enemy.o: spaceship.hpp rsdl.hpp defines.hpp enemy.hpp bullet.hpp enemy.cpp
	$(CC) -c enemy.cpp -o enemy.o
bullet.o: defines.hpp bullet.hpp rsdl.hpp bullet.cpp 
	$(CC) -c bullet.cpp -o bullet.o
walking_enemy.o: walking_enemy.hpp spaceship.hpp rsdl.hpp defines.hpp enemy.hpp bullet.hpp walking_enemy.cpp 
	$(CC) -c walking_enemy.cpp -o walking_enemy.o  
hero.o: hero.hpp spaceship.hpp rsdl.hpp defines.hpp bullet.hpp hero.cpp
	$(CC) -c hero.cpp -o hero.o
game.o: rsdl.hpp spaceship.hpp enemy.hpp bullet.hpp walking_enemy.hpp hero.hpp game.hpp game.cpp 
	$(CC) -c game.cpp -o game.o 
.PHONY: clean
clean:
	rm -r *.o