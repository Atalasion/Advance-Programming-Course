#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__

#include "User.hpp"

class Driver:public User{
public:
	Driver(std::string _username);
	void check_is_passenger();
	void check_is_driver();
};

#endif