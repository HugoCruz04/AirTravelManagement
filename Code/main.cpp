#include "Network.h"
using namespace std;

using namespace std;
int main(int argc, char* argv[]){
    Network network;
    network.readAiports("dataset/airports.csv");
    for(auto a: network.getAirports()){
        cout<<a.getIATA()<<a.getName()<<a.getCountry()<<a.getCity()<<endl;
    }
}