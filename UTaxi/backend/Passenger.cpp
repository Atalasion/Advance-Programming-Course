#include "Passenger.hpp"

Passenger::Passenger(std::string _username):User(_username){}

void Passenger::check_is_driver(){
	throw std::runtime_error(PERMISSION_DENIED_ERROR);
}

void Passenger::check_is_passenger(){
	return;
}