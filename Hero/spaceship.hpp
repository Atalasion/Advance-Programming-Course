#ifndef __Spaceship__
#define __Spaceship__
#include "rsdl.hpp"
#include "defines.hpp"

class Spaceship{
protected:
	int x, y;
	bool is_dead;
	std::string img_address;
public:
	Spaceship(int, int, std::string);
	Rectangle rect();
	void die();
	void draw(Window*);
	bool get_is_dead();
};
#endif