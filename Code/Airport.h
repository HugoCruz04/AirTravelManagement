#include <string>
#include "Flight.h"

#ifndef PROJETO_2_AIRPORT_H
#define PROJETO_2_AIRPORT_H

using namespace std;

class Airport{
private:
    string IATA;
    string name;
    string city;
    string country;
    float latitude;
    float longitude;

    vector<flight> flights; //list of flights departing from an airport


public:
    string getIATA() const;
    string getName() const;
    string getCity() const;
    string getCountry() const;
    float getLatitude() const;
    float getLongitude() const;
    void addFlight(const Flight* flight);
};
#endif //PROJETO_2_AIRPORT_H
