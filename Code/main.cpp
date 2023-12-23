#include "Network.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    Network network;
    network.readAiports("dataset/airports.csv");
    network.readAirlines("dataset/airlines.csv");
    network.readFlights("dataset/flights.csv");/*
    Airport *airport = network.findAirport("GKA");
    cout << network.numberOfCountriesAnAirportFliesTo("LJA") << endl;
    cout << network.numberOfCountriesAnAirportFliesTo("JFK") << endl;

    for (auto a: network.getAirports()) {
        cout << a->getIATA() << "\nairport country: " << a->getCountry() << "\nairport city: " << a->getCity()
             << "\nflights num: " << a->getFlightsNum() << "\nairlines num: " << a->getAirlinesNum() << endl;

        for (auto f: a->getFlights()) {
            cout << f.getSource() << " " << f.getTarget() << " " << f.getAirline() << endl;
        }
    }

    cout << endl;

    cout << "nr of airports: " << network.getAirportsNum() << endl;
    cout << "nr of flights: " << network.getFligthsNum() << endl;

    cout << "num flights in Aberdeen: " << network.getFligthsNumPerCity("Aberdeen") << endl;
    cout << "num flights of TAP: " << network.getFligthsNumPerAirline("TAP") << endl;

    int countries = 0;
    int cities = 0;
    int airports = 0;
    network.getDestNumFrom("GKA", airports, cities, countries);
    cout << "\nairports: " << airports << "\ncities: " << cities << "\ncountrie: " << countries << endl;


    cout << network.numberOfCountriesACityFliesTo("New York")<<endl;
    network.getDestNumFromAtDist("GKA", 2, airports, cities, countries);
    cout<<"airports: "<<airports<<"\ncities: "<<cities<<"\ncountries: "<<countries<<endl;

    for(auto n:network.findTopKAirports(3)) {
        cout<<n->getFlightsNum()<<endl;
    }
    unordered_set<Airport*> s=network.articulationAirports();
    for(auto a:s) {
        cout<<a->getIATA()<<endl;
    }

    for(auto a:network.findDiameter()) {
        cout<<a.first<<" "<<a.second<<endl;
    }*/
    for(auto a: network.shortestPathsIATA("LIS", "MAD")) {
        for(auto aa:a) {
            cout<<aa->getIATA()<<endl;
        }
    }
    cout<<endl;
    for(auto a: network.shortestPathsName("Lisboa", "Barajas")) {
        for(auto aa:a) {
            cout<<aa->getIATA()<<endl;
        }
    }

    return 0;
}
