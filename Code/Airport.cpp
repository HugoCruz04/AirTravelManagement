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
vector<const Flight> Airport::getFlights() const {return flights;}
void Airport::addFlight(const Flight flight){flights.push_back(flight);}