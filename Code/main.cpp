#include "Network.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    Network network;
    network.readAiports("dataset/airports_test.csv");
    network.readAirlines("dataset/airlines_test.csv");
    network.readFlights("dataset/flights_test.csv");


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

    int stops;                                                          //3.vii
    vector<pair<Airport*,Airport*>> airportsSourceAndDest;
    network.getMaxStopsBetweenAirports(stops, airportsSourceAndDest);
    cout<<"max num of stops"<<stops<<endl;
    for(auto airportsPair: airportsSourceAndDest) {
        cout<<"source:"<<airportsPair.first->getName()<<" Dest:"<<airportsPair.second->getName()<<endl;
    }

    vector<Airport*> airp = network.findTopKAirports(5);                //3.viii
    for(auto a: airp) {
        cout<<a->getName() <<"  num of flights departing and arriving:"<< a->getTrafic()<<endl;
    }

    std::unordered_set<Airport*> airpss = network.articulationAirports();  //3.ix
    int counter=0;
    for(auto a: airpss) {
        cout<<a->getName()<<endl;
        counter++;
    }
    cout<<"num of essential airports:"<<counter<<endl;

    //4 é simples. Percebe se nas funçoes


    //5
    Airline tap= network.findAirline("1QA");
    vector<Airline> v ;
    v.push_back(tap);
    Network newNetwork= network.filterByAirlines(v);
    for(auto a: newNetwork.getAirports()){
        for(auto f: a->getFlights()){
            cout<<f.getSource()<<"\\n"<<endl;
        }
    }

/*
    auto v=network.minAirline("LIS","MAD");
    for(auto i:v){
        for(auto f:i) cout<<f.getAirline()<<endl;
    }
    return 0;
    */
}
