#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Airport.h"
#include "Flight.h"
#include "Airline.h"

#ifndef PROJETO_2_NETWORK_H
#define PROJETO_2_NETWORK_H


class Network{
private:
    std::vector<Airport> Airports;
    std::vector<Airline> Airlines;
public:
    static Airport* findAirport(std::string IATA);
    std::vector<Airport> getAirports();
    std::vector<Airline> getAirlines();
    void readAiports(const std::string fileName);
    void readFlights(const std::string fileName);
    void readAirlines(const std::string fileName);
    void loadNetwork(const std::string aiportsFileName, const std::string flightsFileName);
};

#endif //PROJETO_2_NETWORK_H
