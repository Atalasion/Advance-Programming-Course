#include "Trip.hpp"

Trip::Trip(Passenger* passenger_username, std::string origin_name, std::string destination_name, int _id, long double _cost){
	passenger = passenger_username;
	origin = origin_name;
	destination = destination_name;
	id = _id;
	status = WAITING_STATUS;
	cost = _cost;
}

std::vector<std::string> Trip::show_informations(){
	std::vector<std::string> res;
	std::stringstream s;
	s << id;
	res.push_back(s.str());
	res.push_back(passenger->get_username());
	res.push_back(origin);
	res.push_back(destination);
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) << cost;
	res.push_back(ss.str());
	res.push_back(status);
	return res;
}

int Trip::get_id(){
	return id;
}

bool Trip::compare_passenger(std::string username){
	return (username == passenger->get_username());
}

std::string Trip::get_status(){
	return status;
}

void Trip::set_driver(Driver* _driver){
	driver = _driver;
	status = TRAVELING_STATUS;
}

void Trip::finish_trip(){
	passenger->set_trip(-1);
	driver->set_trip(-1);
	status = FINISHED_STATUS;
}

long double Trip::get_cost(){
	return cost;
}