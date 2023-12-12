#ifndef __PASSENGER_HPP__
#define __PASSENGER_HPP__

#include "User.hpp"

class Passenger:public User{
public:
	Passenger(std::string username);
	void check_is_passenger();
	void check_is_driver();
}; 

#endif