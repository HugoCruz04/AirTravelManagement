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
            cout<<f.getSource()<<" "<<f.getTarget()<<" "<<f.getAirline()<<endl;
        }
        cout<< endl;
    }
    cout<<"nr of airports: "<<network.getAirportsNum()<<endl;
    cout<<"nr of flights: "<<network.getFligthsNum()<<endl;

}