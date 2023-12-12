#ifndef __DATABASE_HPP__
#define __DATABASE_HPP__

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <fstream>
#include <math.h>
#include "User.hpp"
#include "Passenger.hpp"
#include "Driver.hpp"
#include "Trip.hpp"
#include "Location.hpp"
#include "defines.hpp"

class DataBase{
private:
	std::vector<User*> members;
	std::vector<Location*> locations;
	std::vector<Trip*> trips;
	int trip_counter;
public:
	DataBase();
	User* search_user_by_name(std::string username);
	Location* search_location_by_name(std::string name);
	Trip* search_trip_by_id(int id);
	void signup(std::string username, std::string role);
	void handle_signup(std::vector<std::string> input);
	int add_trip(std::string username, std::string origin, std::string destination, std::string in_hurry);
	void handle_add_trip(std::vector<std::string> input);
	std::vector<Trip*> show_trips_list_to_driver(std::string username, std::string sort_by_cost);
	void show_trip_to_driver(std::string username, int id);
	void handle_get_trip(std::vector<std::string> input);
	void delete_trip(std::string username, int id);
	void handle_delete_trip(std::vector<std::string> input);
	void accept_trip(std::string username, int id);
	void handle_accept_trip(std::vector<std::string> input);
	void finish_trip(std::string username, int id);
	void handle_finish_trip(std::vector<std::string> input);
	void process(const char* address);
	void read_locations(const char* address);
	std::string find_object(std::vector<std::string> input, std::string s);
	std::vector<std::string> split_by_space(std::string s);
	void handle_input(std::vector<std::string> input);
	long double get_cost(std::string username, std::string origin, std::string destination, std::string in_hurry);
	void handle_get_cost(std::vector<std::string> input);
	long double calc_cost(Location* origin, Location* destination);
};

#endif