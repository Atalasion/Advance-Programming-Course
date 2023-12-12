#include "spaceship.hpp"

Spaceship::Spaceship(int _x, int _y, std::string _img_address){
	x = _x, y = _y, img_address = _img_address, is_dead = 0;
}

Rectangle Spaceship::rect(){
	return Rectangle(x, y, spaceship_width, spaceship_height);
}

void Spaceship::die(){
	is_dead = 1;
}

void Spaceship::draw(Window* window){
	if (is_dead == 0) 
		window->draw_img(img_address, Rectangle(x, y, spaceship_width, spaceship_height));
}

bool Spaceship::get_is_dead(){
	return is_dead;
}
