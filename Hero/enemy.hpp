#ifndef __Enemy__
#define __Enemy__
#include "spaceship.hpp"
#include "defines.hpp"
#include "bullet.hpp"
#include <vector>

class Enemy:public Spaceship{
public:
	Enemy(int, int, std::string);
	virtual Bullet* play_turn(int);
	Bullet* shoot(int);
};
#endif