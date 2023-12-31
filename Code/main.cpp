#include "Network.h"
#include "Menu.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
  /*
    Network network;
    network.readAiports("dataset/airports.csv");
    network.readAirlines("dataset/airlines.csv");
    network.readFlights("dataset/flights.csv");


    //4 é simples. Percebe se nas funçoes

     //5
    Airline tap= network.findAirline("1QA");
    vector<Airline> v ;
    v.push_back(tap);
    Network newNetwork= network.filterByAirlines(v);
    for(auto a: newNetwork.getAirports()){
        for(auto f: a->getFlights()){
            cout<<f.getSource()<<"\n"<<endl;
        }
    }

    */

    Menu menu;
    menu.run();

    return 0;
}
