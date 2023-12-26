#include "Network.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    Network network;
    network.readAiports("dataset/airports.csv");
    network.readAirlines("dataset/airlines.csv");
    network.readFlights("dataset/flights.csv");

    cout<<network.getFligthsNum()<<endl;        //3.i
    cout<<network.getAirportsNum()<<endl;

    Airport* airport= network.findAirport("LIS");       //3.ii
    cout<<airport->getAirlinesNum()<<" flightsnum:" << airport->getFlights().size()<<endl;

    cout<<network.getFligthsNumPerCity("Lisbon","Portugal")<<" "<<network.getFligthsNumPerAirline("TAP")<<endl; //3.iii

    cout<<network.numberOfCountriesACityFliesTo("Lisbon","Portugal")<<' '<<network.numberOfCountriesAnAirportFliesTo("GKA")<<endl; //3.iv

    int cities, airports, countries;                                        //3.v
    network.getDestNumFrom("CDG",airports,cities,countries);
    cout<<airports<<' '<<cities<<' '<<countries<<endl;

    network.getDestNumFromAtDist("CDG", 3, airports,cities,countries); //3.vi
    cout<<airports<<' '<<cities<<' '<<countries<<endl;







    return 0;
}
