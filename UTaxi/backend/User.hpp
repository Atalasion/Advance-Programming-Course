#ifndef __USER_HPP__
#define __USER_HPP__

#include "defines.hpp"
#include <string>
#include <stdexcept>

class User{
protected:
	std::string username;
	int trip_id;
public:
	User(std::string _username);
	std::string get_username();
	virtual void check_is_passenger() = 0;
	virtual void check_is_driver() = 0;
	bool has_trip();
	void set_trip(int id);
	int get_trip();
};

#endif