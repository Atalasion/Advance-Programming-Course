#include "enemy.hpp"

Enemy::Enemy(int _x, int _y, std::string _img_address): Spaceship(_x, _y, _img_address){}

Bullet* Enemy::play_turn(int counter){
	if (is_dead == 0)
		return shoot(counter);
	return NULL;
}

Bullet* Enemy::shoot(int counter){
	if (counter == counter_per_shot){
		int mid_x = (2 * x + spaceship_width) / 2;
		Bullet* bullet = new Bullet(mid_x, y + spaceship_height, 1, "Bullet.png");
		return bullet;
	}
	return NULL;
}
