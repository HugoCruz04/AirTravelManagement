#include "Network.h"
#include "Airport.h"
#include "Flight.h"

#include <unordered_set>
#include <queue>
#include <stack>

using namespace std;

void Network::readAiports(std::string fileName) {
    ifstream  file(fileName);

    if(!file.is_open()){
        cerr<< "Error opening file: "<< fileName << endl;
        return;
    }

    string line;
    getline(file,line);
    while (getline(file,line)){
        istringstream iss(line);
        string iata, name, city, country;
        string sLatitude, sLongitude;
        if(std::getline(iss, iata, ',') &&
           std::getline(iss, name, ',') &&
           std::getline(iss, city, ',') &&
           std::getline(iss, country, ',') &&
           std::getline(iss,sLatitude,',') &&
           std::getline(iss,sLongitude)){
            addAirport(iata, name, city, country, stof(sLatitude), stof(sLongitude));
        }else{
            cerr << "Error parsing line: " << line << endl;
            continue;
        }
    }
    std::sort(Airports.begin(), Airports.end(), [](Airport *a, Airport *b) {
        return a->getIATA() < b->getIATA();
    });
    file.close();
}

void Network::readFlights(const std::string fileName) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Error opening file: " << fileName << endl;
        return;
    }

    string line;
    getline(file, line); // Skip the header line
    while (getline(file, line)) {
        istringstream iss(line);
        string source, target, airline;

        if (getline(iss, source, ',') &&
            getline(iss, target, ',') &&
            getline(iss, airline, ',')) {

            Airport* sourceAirport = findAirport(source);
            Airport* dest = findAirport(target);
            if (sourceAirport) {
                Flight flight(source, target, airline,dest);
                sourceAirport->addFlight(flight);
            } else {
                cerr << "Error: Source airport not found - " << source << endl;
            }
        } else {
            cerr << "Error parsing line: " << line << endl;
            continue;
        }
    }

    file.close();
}


Airport* Network::findAirport(const std::string IATA) {
    int left = 0;
    int right = Airports.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (Airports[mid]->getIATA() == IATA) {
            return Airports[mid]; // Found the airport, return a pointer to it
        } else if (Airports[mid]->getIATA() < IATA) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return nullptr;
}

std::vector<Airport*> Network::getAirports() {return Airports;}

std::vector<Airline> Network::getAirlines() {return Airlines;}

void Network::readAirlines(const std::string fileName) {
    ifstream  file(fileName);

    if(!file.is_open()){
        cerr<< "Error opening file: "<< fileName << endl;
        return;
    }

    string line;
    getline(file,line);
    string code, name, callsign, country;
    while (getline(file,line)){
        istringstream iss(line);

        if(std::getline(iss, code, ',') &&
           std::getline(iss, name, ',') &&
           std::getline(iss, callsign, ',') &&
           std::getline(iss, country)){
            Airline airline = Airline(code, name, callsign, country);
            Airlines.push_back(airline);
        }else{
            cerr << "Error parsing line: " << line << endl;
            continue;
        }
    }
}
int Network::getAirportsNum() const {
    int num = Airports.size();
    return num;
}

int Network::getFligthsNum() const {
    int num=0;
    for(const Airport* air: Airports) {
        num+=air->getFlightsNum();
    }
    return num;
}

int Network::getFligthsNumPerCity(const string& city) const {
    int num=0;
    for(Airport *airport:Airports) {
        if(airport->getCity()==city) {
            num+=airport->getFlightsNum();
        }
    }
    return num;
}

int Network::getFligthsNumPerAirline(const string& airlinecode) const {
    int num=0;
    for(Airport* airport:Airports) {
        for(Flight flight: airport->getFlights()) {
            if(flight.getAirline()==airlinecode) {
                num++;
            }
        }
    }
    return num;
}

int Network::numberOfCountriesAnAirportFliesTo(const string& AirportIATA) {
    unordered_set<string> countries;
    Airport* airport = Network::findAirport(AirportIATA);
    for(auto f: airport->getFlights()) countries.insert(f.getDest()->getCountry());
    return countries.size();
}

int Network::numberOfCountriesACityFliesTo(const string& City){
    unordered_set<string> countries;
    vector<Airport*> airports;
    for(auto a : Airports ) if(a->getCity()==City) airports.push_back(a);
    for(auto airport : airports){
        for(auto f: airport->getFlights()) countries.insert(f.getDest()->getCountry());
    }
    return countries.size();
}

void Network::getDestNumFrom(std::string IATA, int &airports, int &cities, int &countries) {
    Airport* airport = findAirport(IATA);

    if (airport== nullptr) {
        // Handle the case where the airport is not found
        airports = cities = countries = 0;
        return;
    }

    std::unordered_set<std::string> airportsIATAs;
    std::unordered_set<std::string> citiesNames;
    std::unordered_set<std::string> countriesNames;
    for (const Flight& flight: airport->getFlights()) {
        Airport* w= flight.getDest();
        airportsIATAs.insert(w->getIATA());

        citiesNames.insert(w->getCity());
        countriesNames.insert(w->getCountry());

    }
    airports=airportsIATAs.size();
    cities=citiesNames.size();
    countries=countriesNames.size();
}

void Network::addAirport(std::string IATA, std::string name, std::string city, std::string country, float latitude,float longitude) {
    Airports.push_back(new Airport(IATA,name, city, country, latitude, longitude));
}

void nodesAtDistanceDFSVisit(const Network *g, Airport *v, int k, set<std::string> &airportsIATAs, set<std::string> &citiesNames, set<std::string> &countriesNames) {

    if(k==0) {
        airportsIATAs.insert(v->getIATA());
        citiesNames.insert(v->getCity());
        countriesNames.insert(v->getCountry());
        return ;
    }
    v->setVisited(true);

    for(auto &e: v->getFlights()) {
        auto w=e.getDest();
        if(!w->isVisited()) nodesAtDistanceDFSVisit(g, w,k-1,airportsIATAs, citiesNames, countriesNames);
    }
}

void Network::getDestNumFromAtDist(std::string IATA, int distance,int &airports, int &cities, int &countries) {
    std::set<std::string> airportsIATAs;
    std::set<std::string> citiesNames;
    std::set<std::string> countriesNames;
    for(Airport* airport : Airports) {
        airport->setVisited(false);
    }
    auto airport = findAirport(IATA);
    nodesAtDistanceDFSVisit(this, airport, distance, airportsIATAs, citiesNames, countriesNames);
    airports=airportsIATAs.size();
    cities=citiesNames.size();
    countries=countriesNames.size();

}

std::vector<Airport *> Network::findTopKAirports(int k) {
    std::vector<Airport*> sortedAirports;

// Using std::copy with std::back_inserter
    std::copy(Airports.begin(), Airports.end(), std::back_inserter(sortedAirports));
    std::sort(sortedAirports.begin(), sortedAirports.end(), [sortedAirports](const auto& a, const auto& b) {
        return a->getFlightsNum() > b->getFlightsNum();
    });
    std::vector<Airport *> res;
    for (int i = 0; i < k && i < sortedAirports.size(); i++) {
        res.push_back(sortedAirports[i]);
    }

    return res;
}

void dfs_art(Network *g, Airport *v, stack<std::string> &s, unordered_set<Airport*> &l, int &i){
    v->setNum(i);
    v->setLow(i);
    i++;
    int children = 0;
    s.push(v->getIATA());
    for (Flight flight : v->getFlights()) {
        if (flight.getDest()->getNum() == 0) {
            children++;
            dfs_art(g, flight.getDest(), s, l, i);
            v->setLow(min(v->getLow(), flight.getDest()->getLow()));
            if (v->getIATA() != g->getAirports()[0]->getIATA() && flight.getDest()->getLow() >= v->getNum())
                l.insert(v);
        }
        else if (flight.getDest()->getNum() > 0)
            v->setLow(min(v->getLow(), flight.getDest()->getNum()));
    }
    s.pop();
    if (v->getIATA() == g->getAirports()[0]->getIATA() && children > 1) {
        l.insert(v);
    }
}

std::unordered_set<Airport *> Network::articulationAirports() {
    unordered_set<Airport*> res;
    stack<std::string> s;
    int i = 0;
    for (Airport* airport : Airports) {
        airport->setNum(i);
    }

    i++;
    for (Airport* airport : Airports) {
        if (airport->getNum() == 0) {
            dfs_art(this, airport, s, res, i);
        }
    }

    return res;
}

int Network::shortestPath(std::string start, std::string end) {
    Airport *airport = findAirport(start);
    Airport *endAirp = findAirport(end);
    if (airport== nullptr || endAirp == nullptr) {
        return -1; // Invalid input
    }
    for (Airport *airport1: Airports) {
        airport1->setVisited(false);
    }

    queue<Airport *> q;
    int distance = 0;

    q.push(airport);
    airport->setVisited(true);

    while (!q.empty()) {
        int size=q.size();
        for(int i=0; i<size; i++) {
            Airport* w = q.front();
            q.pop();
            if(w == endAirp) {
                return distance;
            }

            for(Flight flight : w->getFlights()) {
                q.push(flight.getDest());
                flight.getDest()->setVisited(true);
            }
        }
        distance++;
    }
    return -1;
}



unordered_set<pair<std::string, std::string>, PairHash> Network::findDiameter() {
    int max=0;
    unordered_set<pair<string,string>, PairHash> res;
    for(Airport* airport:Airports) {
        for(Airport* airport2:Airports) {
            int candidate = shortestPath(airport->getIATA(),airport2->getIATA());
            if(candidate>max) {
                max=candidate;
                res.clear();
            }
            if(candidate==max) {
                res.insert({airport->getIATA(),airport2->getIATA()});
            }
        }
    }
    return res;
}
