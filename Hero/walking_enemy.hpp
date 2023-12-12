#ifndef __Walking_enemy__
#define __Walking_enemy__

#include "enemy.hpp"

class Walking_enemy: public Enemy{
private:
	int dir;
public:
	Walking_enemy(int, int, std::string);
	void move();
	virtual Bullet* play_turn(int);
};
#endif