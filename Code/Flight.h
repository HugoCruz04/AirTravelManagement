#include <string>
#include "Airport.h"

#ifndef PROJETO_2_FLIGHT_H
#define PROJETO_2_FLIGHT_H

using namespace std;

class Airport;

class Flight{
private:
    string source;      //source airport's IATA
    string target;      //target airport's IATA
    string airline;     //arline ICAO
    Airport* dest;    //destination airport

public:
    Flight(string source, string target, string airline);
    string getSource() const;
    string getTarget() const;
    string getAirline() const;
    Airport* getDest() const;
};

#endif //PROJETO_2_FLIGHT_H
