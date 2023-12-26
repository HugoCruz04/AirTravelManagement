#include "Network.h"
#include "Airport.h"
#include "Flight.h"

#include <unordered_set>
#include <queue>
#include <stack>
#include <cmath>
#include <limits>
#include <list>

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
            dest->increaseIndegree();
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

Airport* Network::findAirportByName(std::string AirportName) {
    for (Airport* airport:Airports) {
        if(airport->getName() == AirportName) {
            return airport;
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
        num+=air->getFlights().size();
    }
    return num;
}

int Network::getFligthsNumPerCity(const string& city, const string& Country) const {
    int num=0;
    for(Airport *airport:Airports) {
        if(airport->getCity()==city && airport->getCountry()==Country) {
            num+=airport->getFlights().size();
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

int Network::numberOfCountriesACityFliesTo(const string& City, const string& Country){
    unordered_set<string> countries;
    vector<Airport*> airports = findAirportsInCity(City, Country);
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

/*void nodesAtDistanceDFSVisit(const Network *g, Airport *v, int k, set<std::string> &airportsIATAs, set<std::string> &citiesNames, set<std::string> &countriesNames) {

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
}*/

void Network::getDestNumFromAtDist(std::string IATA, int distance,int &airports, int &cities, int &countries) {
    std::set<std::string> airportsIATAs;
    std::set<pair<string,string >> citiesNames;
    std::set<std::string> countriesNames;
    for(Airport* airport : Airports) {
        airport->setVisited(false);
    }
    auto airport = findAirport(IATA);
    int size;
    int nivel=0;
    queue<Airport*> q;
    q.push(airport);
    airport->setVisited(true);

    while(!q.empty() && nivel<=distance) {
        size=q.size();

        for (int i=0;i<size;i++) {
            auto v = q.front();
            q.pop();


            airportsIATAs.insert(v->getIATA());
            citiesNames.insert({v->getCity(), v->getCountry()});
            countriesNames.insert(v->getCountry());


            for(auto &nn : v->getFlights()) {
                auto w=nn.getDest();
                if(!w->isVisited()) {
                    q.push(nn.getDest());
                    w->setVisited(true);

                }
            }
        }
        nivel++;
    }

    airports=airportsIATAs.size();
    cities=citiesNames.size();
    countries=countriesNames.size();

}

std::vector<Airport *> Network::findTopKAirports(int k) {
    std::vector<Airport*> sortedAirports;

// Using std::copy with std::back_inserter
    std::copy(Airports.begin(), Airports.end(), std::back_inserter(sortedAirports));
    std::sort(sortedAirports.begin(), sortedAirports.end(), [sortedAirports](const auto& a, const auto& b) {
        return a->getTrafic() > b->getTrafic();
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

int Network::shortestPathNR(std::string start, std::string end) {
    Airport* airport = findAirport(start);
    Airport* endAirp = findAirport(end);
    if (airport == nullptr || endAirp == nullptr) {
        return -1; // Invalid input
    }

    std::unordered_set<Airport*> visited;
    std::queue<Airport*> q;
    int distance = 0;

    q.push(airport);
    visited.insert(airport);

    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            Airport* w = q.front();
            q.pop();
            if (w == endAirp) {
                return distance;
            }

            for (Flight flight : w->getFlights()) {
                Airport* dest = flight.getDest();
                if (visited.find(dest) == visited.end()) {
                    q.push(dest);
                    visited.insert(dest);
                }
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
            int candidate = shortestPathNR(airport->getIATA(), airport2->getIATA());
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

void Network::maxstopsbetweenairportsAuxiliary(int & stops, vector<pair<Airport*, Airport*>> &airports) {
    int stopsNum = 0;
    vector<pair<Airport*, Airport*>> maxTripAirports;

    for (Airport* sourceAirport : Airports) {
        vector<pair<Airport*, Airport*>> aux;
        int stops = calculateStopsBFS(sourceAirport, aux);
        if (stops > stopsNum) {
            stopsNum = stops;
            maxTripAirports = aux;
        } else if (stops == stopsNum) {
            maxTripAirports.insert(maxTripAirports.end(),aux.begin(),aux.end());

        }
    }

    stops = stopsNum;
    airports = maxTripAirports;

}

int Network::calculateStopsBFS(Airport* source, vector<pair<Airport*, Airport*>> &aux) {
    int distmax = 0;
    for(Airport* airport:Airports){
        airport->setVisited(false);
        airport->setProcessing(false);
    }
    std::queue<std::pair<Airport*, int>> q;
    q.push({source, 0});
    source->setProcessing(true);

    while (!q.empty()) {
        Airport* current = q.front().first;
        if(q.front().second > distmax){
            distmax=q.front().second;
            vector<pair<Airport*, Airport*>> ve;
            ve.push_back({source,current});
            aux = ve;
        }else if(q.front().second == distmax){
            aux.push_back({source,current});
        }

        for (const Flight& flight : current->getFlights()) {
            if(flight.getDest()->isVisited()) continue;
            if(flight.getDest()->isProcessing()) continue;
            q.push({flight.getDest(), q.front().second + 1});
            flight.getDest()->setProcessing(true);
        }
        q.pop();
        current->setVisited(true);
        current->setProcessing(false);
    }

    return distmax;
}

std::vector<std::vector<Airport*>> Network::shortestPathsIATA(const std::string& startIATA, const std::string& endIATA) {
    Airport* airport = findAirport(startIATA);
    Airport* endAirp = findAirport(endIATA);
    if (airport == nullptr || endAirp == nullptr) {
        return {}; // Invalid input, return an empty vector
    }

    std::vector<std::vector<Airport*>> paths; // Vector to store the paths
    std::queue<std::vector<Airport*>> q; // Queue of paths
    std::unordered_set<Airport*> visited;

    q.push({airport}); // Start with a path containing only the starting airport
    visited.insert(airport);

    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            std::vector<Airport*> currentPath = q.front();
            Airport* w = currentPath.back();
            q.pop();

            if (w == endAirp) {
                paths.push_back(currentPath); // Found a path to the destination
            }

            for (Flight flight : w->getFlights()) {
                Airport* dest = flight.getDest();
                if (visited.find(dest) == visited.end()) {
                    std::vector<Airport*> newPath = currentPath;
                    newPath.push_back(dest);
                    q.push(newPath);
                    visited.insert(dest);
                }
            }
        }
    }

    return paths;
}

std::vector<std::vector<Airport *>>Network::shortestPathsName(const string &airportNameStart, const string &airportNameEnd) {
    vector<Airport*> airportsStart={findAirportByName(airportNameStart)};
    vector<Airport*> airportsEnd={findAirportByName(airportNameEnd)};

    return shortestPathsAuxiliary(airportsStart, airportsEnd);
}

vector<Airport*> Network::findAirportsInCity(const string CityName, const std::string countryName) {
    vector<Airport*> res;
    for(Airport* airport: Airports) {
        if (airport->getCity() == CityName && airport->getCountry()==countryName){
            res.push_back(airport);
        }
    }
    return res;
}

std::vector<std::vector<Airport*>> Network::shortestPathsCitys(std::string CityNameStart, std::string countrystart, std::string CityNameEnd, std::string countryEnd) {
    std::vector<Airport*> airportsStart = findAirportsInCity(CityNameStart, countrystart);
    std::vector<Airport*> airportsEnd = findAirportsInCity(CityNameEnd, countryEnd);


    return shortestPathsAuxiliary(airportsStart, airportsEnd);
}

std::vector<Airport*> Network::findClosestAirports(float latitudedeg, float longitudedeg) {
    float latitude = latitudedeg * M_PI /180;
    float longitude = longitudedeg * M_PI /180;
    float min = std::numeric_limits<float>::max();
    vector<Airport*> res;
    for(Airport* airport: Airports) {
        float airlat = airport->getLatitude() * M_PI /180;
        float airlong = airport->getLongitude() * M_PI /180;
        float candidate = 2*6367.5165* asin(sqrt(sin((latitude-airlat)/2)*sin((latitude-airlat)/2)+cos(airlat)*cos(latitude)*sin((longitude-airlong)/2)*sin((longitude-airlong)/2)));
        if(min>candidate || res.empty()) {
            min=candidate;
            res.clear();
        }
        if(min==candidate) {
            res.push_back(airport);
        }
    }
    return res;
}
std::vector<std::vector<Airport *>> Network::shortestPathsAuxiliary(std::vector<Airport*> airportsStart, std::vector<Airport*> airportsEnd) {
    std::vector<std::vector<Airport*>> res;

    for (Airport* startAirport : airportsStart) {
        for (Airport* endAirport : airportsEnd) {
            std::vector<std::vector<Airport*>> temp = shortestPathsIATA(startAirport->getIATA(), endAirport->getIATA());

            if (temp.empty()) {
                continue;  // Skip empty paths
            }

            if (res.empty() || temp[0].size() < res[0].size()) {
                res = temp;  // Replace existing value in res
            } else if (temp[0].size() == res[0].size()) {
                // If sizes are equal, append paths from temp to res
                res.insert(res.end(), temp.begin(), temp.end());
            }
        }
    }

    return res;
}
std::vector<std::vector<Airport *>> Network::shortestPathsCoordinates(float latitudeStart, float longitudeStart, float latitudeEnd, float longitudeEnd) {
    std::vector<Airport*> airportsStart = findClosestAirports(latitudeStart, longitudeStart);
    std::vector<Airport*> airportsEnd = findClosestAirports(latitudeEnd, longitudeEnd);

    return shortestPathsAuxiliary(airportsStart, airportsEnd);
}

std::vector<std::vector<Airport *>>
Network::shortestPathsIATAtoName(const string &startIATA, const string &airportNameEnd) {
    vector<Airport*> airportsStart={findAirport(startIATA)};
    vector<Airport*> airportsEnd={findAirportByName(airportNameEnd)};

    return shortestPathsAuxiliary(airportsStart, airportsEnd);
}

std::vector<std::vector<Airport *>>
Network::shortestPathsNametoIATA(const string &airportNameStart, const string &endIATA) {
    Airport* airport = findAirportByName(airportNameStart);
    Airport* endAirp = findAirport(endIATA);
    if (airport == nullptr || endAirp == nullptr) {
        return {}; // Invalid input, return an empty vector
    }
    vector<Airport*> airportsStart={airport};
    vector<Airport*> airportsEnd={endAirp};
    return shortestPathsAuxiliary(airportsStart, airportsEnd);
}

std::vector<std::vector<Airport *>>
Network::shortestPathsIATAtoCity(const string &startIATA, const string &cityNameEnd, const std::string& countryEnd) {
    vector<Airport*> airportsStart = {findAirport(startIATA)};
    vector<Airport*> airportsEnd = findAirportsInCity(cityNameEnd, countryEnd);

    return shortestPathsAuxiliary(airportsStart, airportsEnd);
}

std::vector<std::vector<Airport *>>
Network::shortestPathsIATAtoCoord(const string &startIATA, float latitudeEnd, float longitudeEnd) {
    vector<Airport*> airportsStart = {findAirport(startIATA)};
    vector<Airport*> airportsEnd = findClosestAirports(latitudeEnd,longitudeEnd);

    return shortestPathsAuxiliary(airportsStart, airportsEnd);
}

std::vector<std::vector<Airport *>>
Network::shortestPathsNametoCity(const string &airportNameStart, const std::string CityNameEnd, const std::string countryEnd) {
    vector<Airport*> airportsStart = {findAirportByName(airportNameStart)};
    vector<Airport*> airportsEnd = findAirportsInCity(CityNameEnd, countryEnd);

    return shortestPathsAuxiliary(airportsStart, airportsEnd);
}

std::vector<std::vector<Airport *>>
Network::shortestPathsNametoCoord(const string &airportNameStart, float latitudeEnd, float longitudeEnd) {
    vector<Airport*> airportsStart = {findAirportByName(airportNameStart)};
    vector<Airport*> airportsEnd = findClosestAirports(latitudeEnd,longitudeEnd);

    return shortestPathsAuxiliary(airportsStart, airportsEnd);
}

std::vector<std::vector<Airport *>>
Network::shortestPathsCityToIATA(std::string CityNameStart, std::string countrystart, const std::string &endIATA) {
    vector<Airport*> airportsStart = findAirportsInCity(CityNameStart,countrystart);
    vector<Airport*> airportsEnd = {findAirport(endIATA)};

    return shortestPathsAuxiliary(airportsStart, airportsEnd);
}

std::vector<std::vector<Airport *>>
Network::shortestPathsCityToName(std::string CityNameStart, std::string countrystart, const std::string& airportNameEnd) {
    vector<Airport*> airportsStart = findAirportsInCity(CityNameStart,countrystart);
    vector<Airport*> airportsEnd = {findAirportByName(airportNameEnd)};

    return shortestPathsAuxiliary(airportsStart, airportsEnd);
}

std::vector<std::vector<Airport *>>
Network::shortestPathsCityToCoord(std::string CityNameStart, std::string countrystart, float latitudeEnd, float longitudeEnd) {
    vector<Airport*> airportsStart = findAirportsInCity(CityNameStart,countrystart);
    vector<Airport*> airportsEnd = findClosestAirports(latitudeEnd, longitudeEnd);

    return shortestPathsAuxiliary(airportsStart, airportsEnd);
}

std::vector<std::vector<Airport *>>
Network::shortestPathsCoordinateToIATA(float latitudeStart, float longitudeStart, const string &endIATA) {
    vector<Airport*> airportsStart = findClosestAirports(latitudeStart, longitudeStart);
    vector<Airport*> airportsEnd = {findAirport(endIATA)};

    return shortestPathsAuxiliary(airportsStart, airportsEnd);
}

std::vector<std::vector<Airport *>>
Network::shortestPathsCoordinateToName(float latitudeStart, float longitudeStart, const string &airportNameEnd) {
    vector<Airport*> airportsStart = findClosestAirports(latitudeStart, longitudeStart);
    vector<Airport*> airportsEnd = {findAirportByName(airportNameEnd)};

    return shortestPathsAuxiliary(airportsStart, airportsEnd);
}

std::vector<std::vector<Airport *>>
Network::shortestPathsCoordinateToName(float latitudeStart, float longitudeStart, std::string CityNameEnd, std::string countryEnd) {
    vector<Airport*> airportsStart = findClosestAirports(latitudeStart, longitudeStart);
    vector<Airport*> airportsEnd = findAirportsInCity(CityNameEnd, countryEnd);

    return shortestPathsAuxiliary(airportsStart, airportsEnd);
}

