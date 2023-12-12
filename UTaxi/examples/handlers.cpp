#include "handlers.hpp"

using namespace std;


SignUpHandler::SignUpHandler(string filePath, DataBase* _utaxi) : TemplateHandler(filePath){utaxi = _utaxi;}

map<string, string> SignUpHandler::handle(Request *req){
	map<string, string> context;
	try{
		utaxi->signup(req->getBodyParam("username"), req->getBodyParam("role"));
		context["name"] = "OK";
	}catch(runtime_error& ex){
		context["name"] = ex.what();
	}
	return context;
}

AddTripHandler::AddTripHandler(string filePath, DataBase* _utaxi) : TemplateHandler(filePath){utaxi = _utaxi;}

map<string, string> AddTripHandler::handle(Request *req){
	map<string, string> context;
	try{
		int x = utaxi->add_trip(req->getBodyParam("username"), req->getBodyParam("origin"), req->getBodyParam("destination"), req->getBodyParam("in_hurry"));
		context["name"] = "Trip ID: " + to_string(x);
	}catch(runtime_error& ex){
		context["name"] = ex.what();
	}
	return context;
}

CalcCostHandler::CalcCostHandler(string filePath, DataBase* _utaxi) : TemplateHandler(filePath){utaxi = _utaxi;}

map<string, string> CalcCostHandler::handle(Request *req){
	map<string, string> context;
	try{
		long double x = utaxi->get_cost(req->getQueryParam("username"), req->getQueryParam("origin"), req->getQueryParam("destination"), req->getQueryParam("in_hurry"));
		stringstream s;
		s << fixed << setprecision(2) << x;
		context["name"] = s.str();
	}catch(runtime_error& ex){
		context["name"] = ex.what();
	}
	return context;
}

DeleteTripHandler::DeleteTripHandler(string filePath, DataBase* _utaxi) : TemplateHandler(filePath){utaxi = _utaxi;}

map<string, string> DeleteTripHandler::handle(Request *req){
	map<string, string> context;
	try{
		if (req->getBodyParam("id").size() == 0)
			throw runtime_error(BAD_REQUEST_ERROR);
		utaxi->delete_trip(req->getBodyParam("username"), stoi(req->getBodyParam("id")));
		context["name"] = "OK";
	}catch(runtime_error& ex){
		context["name"] = ex.what();
	}
	return context;
}

ShowTripsHandler::ShowTripsHandler(DataBase* _utaxi){utaxi = _utaxi;}

Response *ShowTripsHandler::callback(Request *req){
	Response *res = new Response;
  	res->setHeader("Content-Type", "text/html");
  	string body;
  	body += "<!DOCTYPE html>";
	body += "<html>";
	body += "<head><style>table, th, td {border: 1px solid black;} body {margin: 0;font-family: Arial, Helvetica, sans-serif;}.topnav {overflow: hidden;background-color: #333;}.topnav a {float: left;color: #f2f2f2;text-align: center;padding: 14px 16px;text-decoration: none;font-size: 17px;}.topnav a:hover {background-color: #ddd;color: black;}.topnav a.active {background-color: #04AA6D;color: white;}</style></head>";
	body += "<body style=\"text-align: center; background-color: #eec12ec5;\">";
 	body += "<div style=\"text-align: left;\" class=\"topnav\"><a href=\"/\">Home</a>&nbsp&nbsp&nbsp&nbsp<a href=\"/sign_up\">Sign Up</a>&nbsp&nbsp&nbsp&nbsp<a href=\"/ask_trip\">Ask/Delete Trip</a>&nbsp&nbsp&nbsp&nbsp<a class=\"active\" href=\"/trips_info\">Trips Info</a>&nbsp&nbsp&nbsp&nbsp</div>";
	try{
		vector<Trip*> trips = utaxi->show_trips_list_to_driver(req->getQueryParam("username"), req->getQueryParam("sort_by_cost"));
		body += "<h1>Utaxi</h1>";
		body += "<h2>Trips Info</h2>";
		body += "<table style=\"width:100%\">";
		body += "<tr> <th> id </th> <th>username</th><th>origin</th><th>destination</th><th>cost</th><th>statue</th><th>&nbsp</th></tr>";
		for (Trip* trip:trips){
			vector<string> res = trip->show_informations();
			body += "<tr>";
			for (string u:res){
				body += "<td>"+u+"</td>";
			}
			body += "<td><form action=\"/finish_trip\" method=\"post\"><input type=\"hidden\" name=\"username\" value=\"" + req->getQueryParam("username") + "\">";
			stringstream s;
			s << trip->get_id();
			body += "<input type=\"hidden\" name=\"id\" value=\"" + s.str() + "\">";
			body += "<button type=\"submit\">Finish</button>";
			body += "<button type=\"submit\" formaction=\"/accept_trip\">Accept</button>";
			body += "</tr>";
			body += "</form>";
			body += "</td>";
		}
	}catch(runtime_error& ex){
		body += "<h1>";
		body += ex.what();
		body += "</h1>";
	}
	body += "</body>";
	body += "</html>";
	res->setBody(body);
	return res;
}

FinishTripHandler::FinishTripHandler(string filePath, DataBase* _utaxi):TemplateHandler(filePath){
	utaxi = _utaxi;
}

map<string, string> FinishTripHandler::handle(Request *req){
	map<string, string> context;
	try{
		if (req->getBodyParam("id").size() == 0)
			throw runtime_error(BAD_REQUEST_ERROR);
		utaxi->finish_trip(req->getBodyParam("username"), stoi(req->getBodyParam("id")));
		context["name"] = OK_COMMAND;
	}catch(runtime_error& ex){
		context["name"] = ex.what();
	}
	return context;
}

AcceptTripHandler::AcceptTripHandler(string filePath, DataBase* _utaxi):TemplateHandler(filePath){
	utaxi = _utaxi;
}

map<string, string> AcceptTripHandler::handle(Request *req){
	map<string, string> context;
	try{
		if (req->getBodyParam("id").size() == 0)
			throw runtime_error(BAD_REQUEST_ERROR);
		utaxi->accept_trip(req->getBodyParam("username"), stoi(req->getBodyParam("id")));
		context["name"] = OK_COMMAND;
	}catch(runtime_error& ex){
		context["name"] = ex.what();
	}
	return context;
}