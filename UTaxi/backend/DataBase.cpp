#include "DataBase.hpp"

DataBase::DataBase(){
	trip_counter = 0;
}

std::string DataBase::find_object(std::vector<std::string> input, std::string s){
	for (int i = 0; i < (int)input.size() - 1; i++){
		if (input[i] == s)
			return input[i + 1];
	}
	throw std::runtime_error(BAD_REQUEST_ERROR);
}

void DataBase::signup(std::string username, std::string role){
	if (username.size() == 0 || role.size() == 0) 
		throw std::runtime_error(BAD_REQUEST_ERROR);
	if (search_user_by_name(username) != NULL)
		throw std::runtime_error(BAD_REQUEST_ERROR);
	if (role != "driver" && role != "passenger")
		throw std::runtime_error(BAD_REQUEST_ERROR);
	if (role == "driver"){
		Driver* driver = new Driver(username);
		members.push_back(driver);
	}
	if (role == "passenger"){
		Passenger* passenger = new Passenger(username);
		members.push_back(passenger);
	}
	std::cout << OK_COMMAND << std::endl;
	return;
}

bool cmp_by_cost(Trip* trip1, Trip* trip2){
	if (trip1->get_cost() == trip2->get_cost())
		return trip1->get_id() < trip2->get_id();
	return trip1->get_cost() > trip2->get_cost();
}

bool cmp_by_id(Trip* trip1, Trip* trip2){
	return trip1->get_id() < trip2->get_id();
}

long double DataBase::calc_cost(Location* origin, Location* destination){
	long double dist = (origin->get_lat() - destination->get_lat()) * (origin->get_lat() - destination->get_lat());
	dist += (origin->get_lng() - destination->get_lng()) * (origin->get_lng() - destination->get_lng());
	dist = sqrt(dist);
	dist *= 110.5;
	long double price = dist * (origin->get_traffic() + destination->get_traffic());
	price *= 10000;
	return price;
}

User* DataBase::search_user_by_name(std::string username){
	for (User* user:members)
		if (user->get_username() == username)
			return user;
	return NULL;
}

Location* DataBase::search_location_by_name(std::string name){
	for (Location* location:locations)
		if (location->get_name() == name)
			return location;
	return NULL;
}

Trip* DataBase::search_trip_by_id(int id){
	for (Trip* trip:trips)
		if (trip->get_id() == id)
			return trip;
	return NULL;
}

int DataBase::add_trip(std::string username, std::string origin, std::string destination, std::string in_hurry){
	if (username.size() == 0 || origin.size() == 0 || destination.size() == 0 || in_hurry.size() == 0) 
		throw std::runtime_error(BAD_REQUEST_ERROR);
	if (search_user_by_name(username) == NULL || search_location_by_name(origin) == NULL || search_location_by_name(destination) == NULL)
		throw std::runtime_error(NOT_FOUND_ERROR);
	User* user = search_user_by_name(username);
	user->check_is_passenger();
	if (user->has_trip())
		throw std::runtime_error(BAD_REQUEST_ERROR);
	long double cost = get_cost(username, origin, destination, in_hurry);
	Trip* trip = new Trip((Passenger*)user, origin, destination, ++trip_counter, cost);
	user->set_trip(trip_counter);
	trips.push_back(trip);
	return trip_counter;
}

std::vector<Trip*> DataBase::show_trips_list_to_driver(std::string username, std::string sort_by_cost){
	if (username.size() == 0 || sort_by_cost.size() == 0) 
		throw std::runtime_error(BAD_REQUEST_ERROR);
	if (search_user_by_name(username) == NULL)
		throw std::runtime_error(NOT_FOUND_ERROR);	
	User* user = search_user_by_name(username);
	user->check_is_driver();
	if (trips.size() == 0)
		throw std::runtime_error(EMPTY_ERROR);
	if (sort_by_cost == "yes")
		sort(trips.begin(), trips.end(), cmp_by_cost);
	else if(sort_by_cost == "no")
		sort(trips.begin(), trips.end(), cmp_by_id);
	else 
		throw std::runtime_error(BAD_REQUEST_ERROR);
	return trips;
}

void DataBase::show_trip_to_driver(std::string username, int id){
	if (search_user_by_name(username) == NULL || search_trip_by_id(id) == NULL)
		throw std::runtime_error(NOT_FOUND_ERROR);
	User* user = search_user_by_name(username);
	user->check_is_driver();
	Trip* trip = search_trip_by_id(id);
	trip->show_informations();
}

void DataBase::delete_trip(std::string username, int id){
	if (username.size() == 0)
		throw std::runtime_error(BAD_REQUEST_ERROR);
	if (search_user_by_name(username) == NULL || search_trip_by_id(id) == NULL)
		throw std::runtime_error(NOT_FOUND_ERROR);
	User* user = search_user_by_name(username);
	user->check_is_passenger();
	Trip* trip = search_trip_by_id(id);
	if (trip->compare_passenger(username) == 0)
		throw std::runtime_error(PERMISSION_DENIED_ERROR);
	if (trip->get_status() != WAITING_STATUS)
		throw std::runtime_error(BAD_REQUEST_ERROR);
	std::vector<Trip*> new_trips;
	user->set_trip(-1);
	for (Trip* trip:trips){
		if (trip->get_id() == id) 
			continue;
		new_trips.push_back(trip);
	}
	trips = new_trips;
	return;
}

void DataBase::accept_trip(std::string username, int id){
	if (search_user_by_name(username) == NULL || search_trip_by_id(id) == NULL)
		throw std::runtime_error(NOT_FOUND_ERROR);
	User* user = search_user_by_name(username);
	user->check_is_driver();
	Trip* trip = search_trip_by_id(id);
	if (user->has_trip() == 1 || trip->get_status() != WAITING_STATUS)
		throw std::runtime_error(BAD_REQUEST_ERROR);
	user->set_trip(id);
	trip->set_driver((Driver*)user);
	return;
}

void DataBase::finish_trip(std::string username, int id){
	if (username.size() == 0)
		throw std::runtime_error(BAD_REQUEST_ERROR);
	if (search_user_by_name(username) == NULL || search_trip_by_id(id) == NULL)
		throw std::runtime_error(NOT_FOUND_ERROR);
	User* user = search_user_by_name(username);
	user->check_is_driver();
	Trip* trip = search_trip_by_id(id);
	if (user->get_trip() != id)
		throw std::runtime_error(PERMISSION_DENIED_ERROR);
	trip->finish_trip();
	return;
}

long double DataBase::get_cost(std::string username, std::string origin, std::string destination, std::string in_hurry){
	if (search_user_by_name(username) == NULL || search_location_by_name(origin) == NULL || search_location_by_name(destination) == NULL)
		throw std::runtime_error(NOT_FOUND_ERROR);
	User* user = search_user_by_name(username);
	user->check_is_passenger();
	Location* origin_location = search_location_by_name(origin);
	Location* destination_location = search_location_by_name(destination);
	long double cost = calc_cost(origin_location, destination_location);
	if (in_hurry == "yes")
		cost *= in_hurry_ratio;
	else if(in_hurry != "no")
		throw std::runtime_error(BAD_REQUEST_ERROR);
	return cost;
}

void DataBase::read_locations(const char* address){
	std::ifstream location_file;
	location_file.open(address);
	std::string s;
	getline(location_file, s);
	std::string name;
	long double lat, lng;
	int traffic;
	while (getline(location_file, s)){
		std::string result = "";
		int cnt = 0;
		for (int i = 0; i < s.size(); i++){
			if (s[i] != ',')
				result += s[i];
			else{
				if (cnt == 0)
					name = result;
				else if (cnt == 1)
					lat = stod(result);
				else if(cnt == 2)
					lng = stod(result);
				cnt ++;
				result = "";
			}
		}
		traffic = stoi(result);
		Location* location = new Location(name, lat, lng, traffic);
		locations.push_back(location);
	}
	location_file.close();
}

std::vector<std::string> DataBase::split_by_space(std::string s){
	std::vector<std::string> splited_string;
	std::string res = "";
	for (int i = 0; i < s.size(); i++){
		if (s[i] == ' '){
			splited_string.push_back(res);
			res = "";
		}
		else
			res += s[i];
	}
	splited_string.push_back(res);
	return splited_string;
}

void DataBase::process(const char* address){
	read_locations(address);
	std::string s;
	while (getline(std::cin, s)){
		if (trips.size() != 0)
			sort(trips.begin(), trips.end(), cmp_by_id);
		std::vector<std::string> input = split_by_space(s);
		try{
			handle_input(input);
		}catch (std::runtime_error& ex){
			std::cout << ex.what() << std::endl;
		}
	}
}

void DataBase::handle_input(std::vector<std::string> input){
	if (input.size() < 3 || input[2] != "?")
		throw std::runtime_error(BAD_REQUEST_ERROR);
	if (input[0] == "POST"){
		if (input[1] == "signup")
			handle_signup(input);
		else if (input[1] == "trips")
			handle_add_trip(input);
		else if (input[1] == "accept")
			handle_accept_trip(input);
		else if(input[1] == "finish")
			handle_finish_trip(input);
		else
			throw std::runtime_error(NOT_FOUND_ERROR);
	}else if(input[0] == "GET"){
		if (input[1] == "trips")
			handle_get_trip(input);
		else if(input[1] == "cost")
			handle_get_cost(input);
		else
			throw std::runtime_error(NOT_FOUND_ERROR);
	}else if(input[0] == "DELETE"){
		if (input[1] == "trips")
			handle_delete_trip(input);
		else 
			throw std::runtime_error(NOT_FOUND_ERROR); 
	}else
		throw std::runtime_error(BAD_REQUEST_ERROR);
}

void DataBase::handle_signup(std::vector<std::string> input){
	signup(find_object(input, "username"), find_object(input, "role"));
}

void DataBase::handle_add_trip(std::vector<std::string> input){
	add_trip(find_object(input, "username"), find_object(input, "origin"), find_object(input, "destination"), find_object(input, "in_hurry"));
}

void DataBase::handle_accept_trip(std::vector<std::string> input){
	accept_trip(find_object(input, "username"), stoi(find_object(input, "id")));
}

void DataBase::handle_finish_trip(std::vector<std::string> input){
	finish_trip(find_object(input, "username"), stoi(find_object(input, "id")));
}

void DataBase::handle_get_trip(std::vector<std::string> input){
	for (std::string command:input)
		if (command == "sort_by_cost"){
			show_trips_list_to_driver(find_object(input, "username"), find_object(input, "sort_by_cost"));
			return;
		}
	show_trip_to_driver(find_object(input, "username"), stoi(find_object(input, "id")));
}

void DataBase::handle_delete_trip(std::vector<std::string> input){
	delete_trip(find_object(input, "username"), stoi(find_object(input, "id")));	
}

void DataBase::handle_get_cost(std::vector<std::string> input){
	std:: cout << get_cost(find_object(input, "username"), find_object(input, "origin"), find_object(input, "destination"), find_object(input, "in_hurry")) << '\n'; 
}

