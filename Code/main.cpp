#include "Network.h"
using namespace std;

using namespace std;
int main(int argc, char* argv[]){
    Network network;
    network.readAiports("dataset/airports.csv");
    //network.readFlights("dataset/flights.csv");
    for(auto a: network.getAirports()){
        cout<<a.getIATA()<<" "<<a.getName()<<" "<<a.getCountry()<<" "<<a.getCity()<<" "<<a.getLatitude()<<" "<<a.getLongitude()<<endl;
    }
    cout<<"Num of airports: "<<network.getAirportsNum()<<endl;
    cout<<"Num of flights: "<<network.getFligthsNum();
}