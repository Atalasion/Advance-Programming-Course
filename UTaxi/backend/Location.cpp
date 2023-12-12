#include "Location.hpp"

Location::Location(std::string _name, long double _lat, long double _lng, int _traffic){
	name = _name;
	lat = _lat;
	lng = _lng;
	traffic = _traffic;
}

std::string Location::get_name(){
	return name;
}

long double Location::get_lat(){
	return lat;
}

long double Location::get_lng(){
	return lng;
}

int Location::get_traffic(){
	return traffic;
}