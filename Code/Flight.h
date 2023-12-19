#include <string>
#include "Airport.h"

#ifndef PROJETO_2_FLIGHT_H
#define PROJETO_2_FLIGHT_H


class Airport;

class Flight{
private:
    std::string source;      //source airport's IATA
    std::string target;      //target airport's IATA
    std::string airline;     //arline ICAO
    Airport* dest;    //destination airport

public:
    Flight(std::string source, std::string target, std::string airline);
    std::string getSource() const;
    std::string getTarget() const;
    std::string getAirline() const;
    Airport* getDest() const;
};

#endif //PROJETO_2_FLIGHT_H
