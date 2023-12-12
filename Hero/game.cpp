#include "game.hpp"

Game::Game(){
	window = new Window(window_width, window_height, "RSDL Demo");
	std::string round_now = "Round1.jpg";
	std::string round_sound_now = "Round1.mp3";
	for (int i = 0; i < rounds_of_game; i++){
		round_now[5] = (i + 1) + '0';
		round_sound_now[5] = (i + 1) + '0';
		round_img_address[i] = round_now;
		round_sound_address[i] = round_sound_now;
	}
}

void Game::total_process(){
	std::cin >> number_of_rows >> number_of_columns >> number_of_rounds;
	for (int round = 0; round < number_of_rounds; round++){
		process_round();
		start_round(round);
		delay(500);
	}
	end_game_as_winner();
}

void Game::empty_events_queue(){
	while (window->has_pending_event())
		Event event = window->poll_for_event();
}

void Game::process_round(){
	enemies.clear();
	bullets.clear();
	hostages.clear();
	for (int i = 0; i < number_of_rows; i++){
		for (int j = 0; j < number_of_columns; j++){
			char input;
			std::cin >> input;
			if (input == 'E'){
				Enemy* enemy = new Enemy(find_x(j), find_y(i), "Enemy.png");
				enemies.push_back(enemy);
			}
			else if (input == 'M'){
				Walking_enemy* enemy = new Walking_enemy(find_x(j), find_y(i), "Enemy.png");
				enemies.push_back(enemy);
			}else if(input == 'S'){
				Spaceship* hostage = new Spaceship(find_x(j), find_y(i), "Hostage.png");
				hostages.push_back(hostage);
			}
		}
	}
	std::string input;
	std::cin >> input;
	hero = new Hero(find_x(rand() % number_of_columns), find_y(number_of_rows - 1), "Hero.png");
}	

void Game::draw(){
	window->clear();
	window->draw_img("background.jpg");
	for (Enemy* enemy:enemies)
		enemy->draw(window);
	for (Spaceship* hostage:hostages)
		hostage->draw(window);
	for (Bullet* bullet:bullets)
		bullet->draw(window);
	hero->draw(window);
	window->update_screen();
}

void Game::handle_events(){
	while (window->has_pending_event()){
		Event event = window->poll_for_event();
		switch(event.get_type()){
			case Event::EventType::QUIT:
				exit(0);
				break;
			case Event::EventType::KEY_PRESS:
				if (event.get_pressed_key() == 'd')
					hero->set_right();
				else if(event.get_pressed_key() == 's')
					hero->set_down();
				else if(event.get_pressed_key() == 'w')
					hero->set_up();
				else if(event.get_pressed_key() == 'a')
					hero->set_left();
				else if(event.get_pressed_key() == ' ')
					hero->set_shoot();
				break;
			case Event::EventType::KEY_RELEASE:
				if (event.get_pressed_key() == 'd')
					hero->set_right();
				else if(event.get_pressed_key() == 's')
					hero->set_down();
				else if(event.get_pressed_key() == 'w')
					hero->set_up();
				else if(event.get_pressed_key() == 'a')
					hero->set_left();
				break;
		}
	}

}

bool Game::have_colision(Rectangle a, Rectangle b){
	int mid_a_x = (2 * a.x + a.w) / 2, mid_a_y = (2 * a.y + a.h) / 2;
	int mid_b_x = (2 * b.x + b.w) / 2, mid_b_y = (2 * b.y + b.h) / 2; 
	int dis = (mid_a_x - mid_b_x) * (mid_a_x - mid_b_x) + (mid_a_y - mid_b_y) * (mid_a_y - mid_b_y);
	return (dis + 25 <= ((a.w + b.w) / 2) * ((a.w + b.w) / 2));
}

void Game::end_game_as_loser(){
	window->play_sound_effect("losing_sound.mp3");
	window->draw_img("Lose.png");
	window->update_screen();
	delay(2000);
	exit(0);
}

void Game::end_game_as_winner(){
	window->play_sound_effect("winning_sound.mp3");
	window->draw_img("Win.jpeg");
	window->update_screen();
	delay(2000);
	exit(0);
}

void Game::check_colisions(){
	for (Enemy* enemy:enemies)
		if (enemy->get_is_dead() == 0 && have_colision(hero->rect(), enemy->rect()))
			end_game_as_loser();
	for (Spaceship* hostage:hostages)
		if (have_colision(hero->rect(), hostage->rect()))
			end_game_as_loser();
	for (Bullet* bullet:bullets){
		if (bullet->get_is_expire() == 0 && bullet->get_dir() == 1 && have_colision(hero->rect(), bullet->rect()))
			end_game_as_loser();
		if (bullet->get_dir() == -1){
			for (Enemy* enemy:enemies)
				if (bullet->get_is_expire() == 0 && enemy->get_is_dead() == 0 && have_colision(bullet->rect(), enemy->rect())){
					bullet->expire();
					enemy->die();
				}
			for (Spaceship* hostage:hostages)
				if (bullet->get_is_expire() == 0 && have_colision(bullet->rect(), hostage->rect()))
					end_game_as_loser();
		}
	}
	
}

void Game::update(int counter){
	for (Bullet* bullet:bullets)
		bullet->play_turn();
	for (Enemy* enemy:enemies){
		Bullet* bullet = enemy->play_turn(counter);
		if (bullet != NULL)
			bullets.push_back(bullet);
	}
	Bullet* bullet = hero->play_turn();
	if (bullet != NULL)
		bullets.push_back(bullet);
}

bool Game::is_game_ended(){
	for (Enemy* enemy:enemies)
		if (enemy->get_is_dead() == 0)
			return 0;
	return 1;
}

void Game::start_round(int round){
	int counter = 0;
	window->play_sound_effect(round_sound_address[round]);
	window->draw_img(round_img_address[round]);
	window->update_screen();
	delay(3000);
	empty_events_queue();
	while (!is_game_ended()){
		counter ++;
		handle_events();
		update(counter);
		draw();
		check_colisions();
		delay(30);
		if (counter == counter_per_shot) counter = 0;
	}
}

int Game::find_x(int ind){
	return ind * spaceship_width;
}

int Game::find_y(int ind){
	return ind * spaceship_height;
}