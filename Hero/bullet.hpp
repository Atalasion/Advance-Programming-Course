#ifndef __Bullet__
#define __Bullet__
#include "defines.hpp"
#include "rsdl.hpp"

class Bullet{
private:
	int x, y, dir;
	std::string img_address;
	bool is_expire;
public:
	Bullet(int, int, int, std::string);
	void play_turn(); 
	void move();
	void draw(Window*);
	void expire();
	Rectangle rect();
	int get_dir();
	bool get_is_expire();
};
#endif