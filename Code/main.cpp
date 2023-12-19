#include "Network.h"
using namespace std;

using namespace std;
int main(int argc, char* argv[]){
    Network network;
    network.readAiports("dataset/airports.csv");

    network.readFlights("dataset/flights.csv");

    for(auto a: network.getAirports()){
        cout<<a.getName()<<' ';
        for(auto f: a.getFlights()){
            cout<<f.getAirline();
        }
        cout<< endl;

    }
    cout<<"Num of airports: "<<network.getAirportsNum()<<endl;
    cout<<"Num of flights: "<<network.getFligthsNum();
}