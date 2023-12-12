#ifndef __LOCATION_HPP__
#define __LOCATION_HPP

#include <string>
#include "defines.hpp"

class Location{
private:
	std::string name;
	long double lat, lng;
	int traffic;
public:
	Location(std::string _name, long double _lat, long double _lng, int _traffic);
	std::string get_name();
	long double get_lat();
	long double get_lng();
	int get_traffic();
};
#endif