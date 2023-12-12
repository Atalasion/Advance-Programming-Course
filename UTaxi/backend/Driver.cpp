#include "Driver.hpp"

Driver::Driver(std::string _username):User(_username){}

void Driver::check_is_passenger(){
	throw std::runtime_error(PERMISSION_DENIED_ERROR);
}

void Driver::check_is_driver(){
	return;
}