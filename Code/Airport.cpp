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

const std::vector<Flight> &Airport::getFlights() const {return flights;}


void  Airport::addFlight(Flight flight){flights.push_back(flight);}

int Airport::getFlightsNum() const {
    std::set<pair<string,string>> uniqueCombinations;
    for (Flight flight : flights) {
        pair<string, string> p = {flight.getSource(), flight.getTarget()};
        uniqueCombinations.insert(p);
    }
    return uniqueCombinations.size();
}

int Airport::getAirlinesNum() const {
    std::set<string> uniqueCombinations;
    for (Flight flight : flights) {
        uniqueCombinations.insert(flight.getAirline());
    }
    return uniqueCombinations.size();
}

bool Airport::isVisited() const {
    return visited;
}

void Airport::setVisited(bool v) {
    visited=v;
}

int Airport::getNum() const {
    return num;
}

void Airport::setNum(int num) {
    Airport::num = num;
}

int Airport::getLow() const {
    return low;
}

void Airport::setLow(int low) {
    Airport::low = low;
}

