#include <string>
#include "Airport.h"
#include "Flight.h"

#ifndef PROJETO_2_NETWORK_H
#define PROJETO_2_NETWORK_H

using namespace std;

class Network{
private:
    vector<Airport>* Airports;

public:
    static Airport* findAirport(string IATA);
    void readAiports(const string fileName);
    void readFlights(const string fileName);
    void loadNetwork(const string aiportsFileName, const string flightsFileName);
};

#endif //PROJETO_2_NETWORK_H
