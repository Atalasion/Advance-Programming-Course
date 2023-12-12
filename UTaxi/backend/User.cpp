#include "User.hpp"

std::string User::get_username(){
	return username;
}

User::User(std::string _username){
	username = _username;
	trip_id = -1;
}

bool User::has_trip(){
	return (trip_id != -1);
}

void User::set_trip(int id){
	trip_id = id;
}

int User::get_trip(){
	return trip_id;
}