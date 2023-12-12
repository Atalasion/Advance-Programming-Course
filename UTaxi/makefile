CC=g++
STD=-std=c++11 -Wall -pedantic
BUILD_DIR=build
TEMPLATE_DIR=.template


all: $(BUILD_DIR) utaxi.out

main.o: backend/DataBase.hpp backend/User.hpp backend/defines.hpp backend/Passenger.hpp backend/Driver.hpp backend/Trip.hpp backend/Location.hpp examples/main.cpp 
	$(CC) $(CF) -c main.cpp -o main.o
User.o: backend/User.hpp backend/User.cpp
	$(CC) $(CF) -c backend/User.cpp -o User.o
Passenger.o: backend/Passenger.hpp backend/User.hpp backend/defines.hpp backend/Passenger.cpp
	$(CC) $(CF) -c backend/Passenger.cpp -o Passenger.o
Driver.o: backend/Driver.hpp backend/User.hpp backend/defines.hpp backend/Driver.cpp
	$(CC) $(CF) -c backend/Driver.cpp -o Driver.o
Trip.o: backend/Trip.hpp backend/Passenger.hpp backend/Driver.hpp backend/defines.hpp backend/User.hpp backend/Trip.cpp 
	$(CC) $(CF) -c backend/Trip.cpp -o Trip.o
DataBase.o: backend/DataBase.hpp backend/User.hpp backend/Passenger.hpp backend/Driver.hpp backend/defines.hpp backend/Trip.hpp backend/Location.hpp backend/DataBase.cpp 
	$(CC) $(CF) -c backend/DataBase.cpp -o DataBase.o  
Location.o: backend/Location.hpp backend/defines.hpp backend/Location.cpp
	$(CC) $(CF) -c backend/Location.cpp -o Location.o

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: backend/DataBase.hpp backend/User.hpp backend/Passenger.hpp backend/Driver.hpp backend/defines.hpp backend/Trip.hpp backend/Location.hpp examples/handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c examples/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: examples/my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c examples/my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o: DataBase.o User.o Passenger.o Driver.o Trip.o Location.o examples/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c examples/main.cpp -o $(BUILD_DIR)/main.o

utaxi.out: DataBase.o User.o Passenger.o Driver.o Trip.o Location.o $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o
	$(CC) $(CF) DataBase.o User.o Passenger.o Driver.o Trip.o Location.o $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o  -o utaxi.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
