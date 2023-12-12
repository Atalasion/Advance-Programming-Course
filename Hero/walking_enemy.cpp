#include "walking_enemy.hpp"
#include <time.h>

Walking_enemy::Walking_enemy(int _x, int _y, std::string _img_address):Enemy(_x, _y, _img_address){
	if (rand() % 2 == 1)
		dir = 1;
	else 
		dir = -1;
}

void Walking_enemy::move(){
	if (dir == 1 && x + dir * walking_spaceship_speed + spaceship_width > window_width)
		dir = -1;
	else if(dir == -1 && x + dir * walking_spaceship_speed < 0)
		dir = 1;
	else 
		x += dir * walking_spaceship_speed;
}

Bullet* Walking_enemy::play_turn(int counter){
	if (is_dead == 0){
		move();
		return Enemy::shoot(counter);
	}
	return NULL;
}