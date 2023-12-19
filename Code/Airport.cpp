#include <set>
#include "Airport.h"
#include "Flight.h"

using namespace std;

Airport::Airport(std::string IATA, std::string name, std::string city, std::string country, float latitude,
                 float longitude):IATA(std::move(IATA)), name(std::move(name)), city(std::move(city)), country(std::move(country)),
                 latitude(latitude), longitude(longitude) {}

string Airport::getIATA() const {return IATA;}
string Airport::getName() const {return name;}
string Airport::getCity() const {return city;}
string Airport::getCountry() const {return country;}
float Airport::getLatitude() const {return latitude;}
float Airport::getLongitude() const {return longitude;}

std::vector<Flight> Airport::getFlights() const {return flights;}


void  Airport::addFlight(Flight flight){flights.push_back(flight);}

int Airport::getFlightsNum() const {
    std::set<pair<string,string>> uniqueCombinations;
    for (Flight flight : flights) {
        pair<string, string> p = {flight.getSource(), flight.getTarget()};
        uniqueCombinations.insert(p);
    }
    return uniqueCombinations.size();
}

