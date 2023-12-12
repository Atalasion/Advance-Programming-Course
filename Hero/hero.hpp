#ifndef __Hero__
#define __Hero__

#include "spaceship.hpp"
#include "bullet.hpp"
#include <vector>

class Hero: public Spaceship{
private:
	bool is_right, is_left, is_up, is_down, is_shoot;
public:
	Hero(int, int, std::string);
	void set_right();
	void set_left();
	void set_down();
	void set_up();
	void set_shoot();
	Bullet* play_turn();
	void move();
	Bullet* shoot();
};

#endif