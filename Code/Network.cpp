#include "Network.h"
#include "Airport.h"
#include "Flight.h"
#include <iostream>
#include <algorithm>

using namespace std;

void Network::readAiports(const std::string fileName) {
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
            Airport airport= Airport(iata, name, city, country, stof(sLatitude), stof(sLongitude));
            Airports.push_back(airport);
        }else{
            cerr << "Error parsing line: " << line << endl;
            continue;
        }
    }
    std::sort(Airports.begin(), Airports.end(), [](const Airport& a, const Airport& b) {
        return a.getIATA() < b.getIATA();
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

            if (sourceAirport) {
                Flight flight(source, target, airline);
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


Airport* Network::findAirport(std::string IATA) {
    int left = 0;
    int right = Airports.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (Airports[mid].getIATA() == IATA) {
            return &Airports[mid]; // Found the airport, return a pointer to it
        } else if (Airports[mid].getIATA() < IATA) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return nullptr;
}

std::vector<Airport> Network::getAirports() {return Airports;}

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
    for(const Airport& air: Airports) {
        num+=air.getFlightsNum();
    }
    return num;
}