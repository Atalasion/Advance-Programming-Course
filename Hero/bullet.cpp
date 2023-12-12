#include "bullet.hpp"

Bullet::Bullet(int _x, int _y, int _dir, std::string _img_address){
	x = _x, y = _y, img_address = _img_address, is_expire = 0, dir = _dir;
}

void Bullet::play_turn(){
	if (is_expire == 0)
		move();
}

void Bullet::move(){
	y += dir * bullet_speed;
	if (y < -100)
		y = -100;
	if (y > window_height)
		y = window_height + 10; 
}

void Bullet::draw(Window* window){
	if (is_expire == 0) 
		window->draw_img(img_address, Rectangle(x, y, bullet_width, bullet_height));
}

void Bullet::expire(){
	is_expire = 1;
}

Rectangle Bullet::rect(){
	return Rectangle(x, y, bullet_width, bullet_height);
}

int Bullet::get_dir(){
	return dir;
}

bool Bullet::get_is_expire(){
	return is_expire;
}