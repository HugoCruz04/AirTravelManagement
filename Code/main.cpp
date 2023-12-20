#include "Network.h"
#include <iostream>
using namespace std;

using namespace std;
int main(int argc, char* argv[]){
    Network network;
    network.readAiports("dataset/airports.csv");
    network.readAirlines("dataset/airlines.csv");
    network.readFlights("dataset/flights.csv");
    Airport* airport= network.findAirport("GKA");
    cout<<network.numberOfCountriesAnAirportFliesTo("LJA")<<endl;
    cout<<network.numberOfCountriesAnAirportFliesTo("JFK")<<endl;

    cout<<network.numberOfCountriesACityFliesTo("New York");
    return 0;
}