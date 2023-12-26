
#include <unordered_set>
#include <set>
#include "Airport.h"
#include "Flight.h"

using namespace std;

Airport::Airport(std::string IATA, std::string name, std::string city, std::string country, float latitude,
                 float longitude):IATA(std::move(IATA)), name(std::move(name)), city(std::move(city)), country(std::move(country)),
                 latitude(latitude), longitude(longitude) {this->indegree=0;}

string Airport::getIATA() const {return IATA;}
string Airport::getName() const {return name;}
string Airport::getCity() const {return city;}
string Airport::getCountry() const {return country;}
float Airport::getLatitude() const {return latitude;}
float Airport::getLongitude() const {return longitude;}

const std::vector<Flight> &Airport::getFlights() const {return flights;}


void  Airport::addFlight(Flight flight){flights.push_back(flight);}

struct PairHash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // A simple hash combination function
        return h1 ^ h2;
    }
};

/*
int Airport::getFlightsNum() const {
    std::unordered_set<pair<string,string>,PairHash> uniqueCombinations;
    for (Flight flight : flights) {
        pair<string, string> p = {flight.getSource(), flight.getTarget()};
        uniqueCombinations.insert(p);
    }
    return uniqueCombinations.size();
}*/

int Airport::getAirlinesNum() const {
    std::unordered_set<string> uniqueCombinations;
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

bool Airport::isProcessing() const {
    return processing;
}

void Airport::setProcessing(bool v) {
    processing=v;
}

void Airport::increaseIndegree() {
    indegree++;
}

int Airport::getIndegree() {
    return indegree;
}

int Airport::getTrafic() {
    return flights.size()+indegree;
}

