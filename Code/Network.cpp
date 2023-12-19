#include "Network.h"
#include "Airport.h"
#include <iostream>

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
}



std::vector<Airport> Network::getAirports() {return Airports;}


int Network::getAirportsNum() {
    int num = Airports.size();
    return num;
}

int Network::getFligthsNum() {
    int num=0;
    for(const Airport& air: Airports) {
        num+=air.getFlightsNum();
    }
    return num;
}
