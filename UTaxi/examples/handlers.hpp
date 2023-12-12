#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "../backend/DataBase.hpp"
#include "../server/server.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

class SignUpHandler : public TemplateHandler{
public:
    SignUpHandler(std::string filePath, DataBase* _utaxi);
    std::map<std::string, std::string> handle(Request *req);
private:
    DataBase* utaxi;
};

class AddTripHandler : public TemplateHandler{
public:
    AddTripHandler(std::string filePath, DataBase* _utaxi);
    std::map<std::string, std::string> handle(Request *req);
private:
    DataBase* utaxi;
};

class CalcCostHandler : public TemplateHandler{
public:
    CalcCostHandler(std::string filePath, DataBase* _utaxi);
    std::map<std::string, std::string> handle(Request *req);
private:
    DataBase* utaxi;
};

class DeleteTripHandler : public TemplateHandler{
public:
    DeleteTripHandler(std::string filePath, DataBase* _utaxi);
    std::map<std::string, std::string> handle(Request* req);
private:
    DataBase* utaxi;
};

class ShowTripsHandler : public RequestHandler{
public:
    ShowTripsHandler(DataBase* _utaxi);
    Response* callback(Request *);
private:
    DataBase* utaxi;
};

class FinishTripHandler:public TemplateHandler{
public:
    FinishTripHandler(std::string filePath, DataBase* _utaxi);
    std::map<std::string, std::string> handle(Request *req);
private:
    DataBase* utaxi;
};

class AcceptTripHandler:public TemplateHandler{
public:
    AcceptTripHandler(std::string filePath, DataBase* _utaxi);
    std::map<std::string, std::string> handle(Request *req);
private:
    DataBase* utaxi;
};

#endif
