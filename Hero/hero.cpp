#include "hero.hpp"

Hero::Hero(int _x, int _y, std::string _img_address):Spaceship(_x, _y, _img_address){
	is_right = is_left = is_up = is_down = is_shoot = 0;
}

void Hero::set_right(){
	is_right ^= 1;
}
void Hero::set_left(){
	is_left ^= 1;
}
void Hero::set_up(){
	is_up ^= 1;
}
void Hero::set_down(){
	is_down ^= 1;
}
void Hero::set_shoot(){
	is_shoot = 1;
}
void Hero::move(){
	y += hero_spaceship_speed * (-(is_up == 1) + (is_down == 1));
	x += hero_spaceship_speed * ((is_right == 1) - (is_left == 1));
	if (y <= 0) 
		y = 0;
	if (y >= window_height - spaceship_height) 
		y = window_height - spaceship_height;
	if (x <= 0)
		x = 0;
	if (x >= window_width - spaceship_width)
		x = window_width - spaceship_width;
}

Bullet* Hero::play_turn(){
	if (is_dead == 0){
		move();
		if (is_shoot)
			return shoot();
	}
	return NULL;
}

Bullet* Hero::shoot(){
	is_shoot = 0;
	int mid_x = (2 * x + spaceship_width) / 2;
	Bullet* bullet = new Bullet(mid_x, y, -1, "Hero_bullet.png");
	return bullet;	
}