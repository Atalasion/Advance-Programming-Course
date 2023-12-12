#ifndef __Game__
#define __Game__

#include "spaceship.hpp"
#include "enemy.hpp"
#include "walking_enemy.hpp"
#include "bullet.hpp"
#include "rsdl.hpp"
#include "hero.hpp"
#include "defines.hpp"
#include <vector>

class Game{
private:
	int number_of_rows, number_of_columns, number_of_rounds;
	Window* window;
	std::vector<Enemy*> enemies;
	Hero* hero;
	std::vector<Spaceship*> hostages;
	std::vector<Bullet*> bullets;
	std::string round_img_address[rounds_of_game];
	std::string round_sound_address[rounds_of_game];
public:
	Game();
	int find_x(int);
	int find_y(int);
	void total_process();
	void process_round();
	void start_round(int);
	void draw();
	void handle_events();
	void update(int);
	bool is_game_ended();
	void check_colisions();
	bool have_colision(Rectangle, Rectangle);
	void end_game_as_loser();
	void end_game_as_winner();
	void empty_events_queue();
};

#endif