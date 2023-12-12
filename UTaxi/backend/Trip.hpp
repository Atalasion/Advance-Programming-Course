#ifndef __TRIP_HPP__
#define __TRIP_HPP__

#include "Passenger.hpp"
#include "Driver.hpp"
#include "defines.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>

class Trip{
private:
	Passenger* passenger;
	Driver* driver;
	std::string origin, destination;
	std::string status;
	long double cost;
	int id;
public:
	Trip(Passenger* passenger_username, std::string origin_name, std::string destination_name, int _id, long double _cost);
	std::vector<std::string> show_informations();
	int get_id();
	bool compare_passenger(std::string username);
	std::string get_status();
	void set_driver(Driver* _driver);
	void finish_trip();
	long double get_cost();
};

#endif