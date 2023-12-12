#include "handlers.hpp"
#include "my_server.hpp"
#include "../backend/DataBase.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
  srand(time(NULL)); // for rand
  DataBase* utaxi = new DataBase();
  utaxi->read_locations(argv[1]);
  try {
    MyServer server(5000);
    server.setNotFoundErrPage("static/404.html");
    server.get("/", new ShowPage("static/home.html"));
    server.get("/sign_up", new ShowPage("static/signup.html"));
    server.post("/sign_up", new SignUpHandler("template/output.html", utaxi));
    server.get("/ask_trip", new ShowPage("static/ask_trip.html"));
    server.post("/add_trip", new AddTripHandler("template/output.html", utaxi));
    server.get("/calc_cost", new CalcCostHandler("template/output.html", utaxi));
    server.post("/delete_trip", new DeleteTripHandler("template/output.html", utaxi));
    server.get("/trips_info", new ShowPage("static/trips_info.html"));
    server.get("/show_trips", new ShowTripsHandler(utaxi));
    server.post("/finish_trip", new FinishTripHandler("template/output.html", utaxi));
    server.post("/accept_trip", new AcceptTripHandler("template/output.html", utaxi));
    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}
