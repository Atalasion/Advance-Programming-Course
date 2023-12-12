#include "game.hpp"
#include <iostream>
#include <time.h>

using namespace std;

int main(int argc, char const *argv[]){
	freopen(argv[1], "r", stdin);
	srand(time(NULL));
	Game* game = new Game();
	game->total_process();
}