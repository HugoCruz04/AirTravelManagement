
#include "Menu.h"
#include <sstream>

using namespace std;

void Menu::nextPage() {
    for (int i = 0; i < 50; i++) {
        cout << '\n';
    }
}


void Menu::run() {
    Network network;
    network.readAiports("dataset/airports.csv");
    network.readAirlines("dataset/airlines.csv");
    network.readFlights("dataset/flights.csv");

    cout << "╒═════════════════════════════════════════════╕\n"
           "│          Flight management system           │\n"
           "╞═════════════════════════════════════════════╡\n"
           "│ > Look through Network                  [1] │\n"
           "│ > Best flight options                   [2] │\n"
           "│                                             │\n"
           "│                                  > Quit [q] │\n"
           "╘═════════════════════════════════════════════╛\n"
           "                                               \n";

    string cmd;
    getline(cin, cmd);
    if (cmd=="q") quit();

    while(cmd != "q" && cmd!="1" && cmd!="2"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

    int operation = stoi(cmd);

    switch (operation) {
        case 1:
            nextPage();
            statistics(network);
            break;
        case 2:
            nextPage();
            //todo
            break;
    }
}

void Menu::quit() {
    exit(0);
}

void Menu::statistics(Network network) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│             Network Statistics              │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│       Registered airports: " << network.getAirportsNum() << "             │\n"
            "│       Available flights: " << network.getFligthsNum() << "              │\n"
            "│                                             │\n"
            "│ > Check airport statistics              [1] │\n"
            "│ > Check number of flights (w/ filters)  [2] │\n"
            "│ > Number of countries a city flies to   [3] │\n" //iv pt2
            "│ > Flight trip(s) with the most stops    [4] │\n"
            "│                                             │\n"
            "│                                             │\n"
            "│ > Back [0]                       > Quit [q] │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";

    string cmd;
    getline(cin, cmd);
    if (cmd=="q") quit();

    while(cmd !="q" && cmd != "0" && cmd!="1" && cmd!="2" && cmd!="3" && cmd!="4"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

    int operation = stoi(cmd);

    switch (operation) {
        case 0:
            nextPage();
            run();
            break;
        case 1:
            nextPage();
            airportStatistics(network);
            break;
        case 2:
            nextPage();
            flightStatistics(network);
            break;
        case 3:
            nextPage();
            insertCountryAndCityName(network, 2);
            break;
        case 4:
            nextPage();
            flightTripWithMostStops(network);
            break;
    }
}

void Menu::airportStatistics(Network network) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│              Airport Statistics             │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│                                             │\n"
            "│ > Check current available airlines      [1] │\n"
            "│ > Check current number of flights       [2] │\n"
            "│ > Number of available countries         [3] │\n"
            "│ > Number of available destinations      [4] │\n"
            "│ > Reachable destinations (w/ lay-overs) [5] │\n"
            "│ > Top K Airport                         [6] │\n"
            "│ > Essential Airports                    [7] │\n"
            "│                                             │\n"
            "│ > Back [0]                       > Quit [q] │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";

    string cmd;
    getline(cin, cmd);
    if (cmd=="q") quit();

    while(cmd !="q" && cmd != "0" && cmd!="1" && cmd!="2" && cmd!="3"  && cmd!="4" && cmd!="5"  && cmd!="6" && cmd!="7"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

    int operation = stoi(cmd);

    switch (operation) {
        case 0:
            nextPage();
            statistics(network);
            break;
        case 1:
            nextPage();
            insertAirportName(network,1);
            break;
        case 2:
            nextPage();
            insertAirportName(network,2);
            break;
        case 3:
            nextPage();
            insertAirportName(network,3);
            break;
        case 4:
            nextPage();
            insertAirportName(network,4);
            break;
        case 5:
            nextPage();
            insertAirportName(network,5);
            break;
        case 6:
            nextPage();
            insertK(network);
            break;
        case 7:
            nextPage();
            essentialAirports(network);
            break;
    }
}


void Menu::insertAirportName(Network network, int option) {

    cout << "╒═════════════════════════════════════════════╕\n"
            "│                Airport Name                 │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│          > Type the Airport name            │\n"
            "│                                             │\n"
            "│                (e.g: LIS)                   │\n"
            "│                                             │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;

    getline(cin, cmd);
    Airport* airport = network.findAirport(cmd);

    if(airport == nullptr){
        cout<<"ERROR: Airport not found\n\n> Back [0]                       > Retry [r] \n";
        getline(cin, cmd);

        while(cmd!="0" && cmd!="r"){
            cout<<"ERROR: Choose a valid option! \n\n> Back [0]                       > Retry [r] \n";
            getline(cin, cmd);
        }

        if(cmd=="0"){
            nextPage();
            airportStatistics(network);
        }

        if(cmd=="r"){
            nextPage();
            insertAirportName(network, option);
        }

    }

    switch (option){
        case 1:
            nextPage();
            checkAvailableAirlines(network, airport);
            break;
        case 2:
            nextPage();
            flightsPerAirport(network, airport);
            break;
        case 3:
            nextPage();
            availableCountriesForAnAirport(network, airport);
            break;
        case 4:
            nextPage();
            availableDestinations(network,airport);
            break;
        case 5:
            nextPage();
            insertNumberOfStops(network,airport);
            break;
    }

}

void Menu::checkAvailableAirlines(Network network, Airport* airport) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│           Current available airlines        │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ There are currently "<< airport->getAirlinesNum()<<" available airlines   │\n"
            "│                                             │\n"
            "│ > Back [0]                       > Quit [q] │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;
    getline(cin, cmd);

    if (cmd=="q") quit();

    if(cmd == "0"){
        nextPage();
        airportStatistics(network);
    }

    while(cmd !="q" && cmd != "0"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }
}

void Menu::flightsPerAirport(Network network, Airport* airport) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│             Flights per Airport             │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ " <<airport->getIATA()<<" has currently "<< airport->getFlights().size()<<" outgoing flights      │\n"
            "│                                             │\n"
            "│ > Back [0]                       > Quit [q] │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;
    getline(cin, cmd);

    if (cmd=="q") quit();

    if(cmd == "0"){
        nextPage();
        airportStatistics(network);
    }

    while(cmd !="q" && cmd != "0"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

}
void Menu::availableCountriesForAnAirport(Network network, Airport *airport) {

    cout << "╒═════════════════════════════════════════════╕\n"
            "│             Available destinations          │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ " <<airport->getIATA()<<" has available flights to:               │\n"
            "│ "<< network.numberOfCountriesAnAirportFliesTo(airport->getIATA()) <<" countries                                │\n"
            "│                                             │\n"
            "│ > Back [0]                       > Quit [q] │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;
    getline(cin, cmd);

    if (cmd=="q") quit();

    if(cmd == "0"){
        nextPage();
        airportStatistics(network);
    }

    while(cmd !="q" && cmd != "0"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }
}

void Menu::availableDestinations(Network network, Airport *airport) {

    int cities, airports, countries;
    network.getDestNumFrom(airport->getIATA(),airports,cities,countries);

    cout << "╒═════════════════════════════════════════════╕\n"
            "│             Available destinations          │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ " <<airport->getIATA()<<" has available flights to:               │\n"
            "│ "<<cities<<" cities                                 │\n"
            "│ "<<countries<<" countries                               │\n"
            "│ "<<airports<<"  airports                              │\n"
            "│                                             │\n"
            "│ > Back [0]                       > Quit [q] │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;
    getline(cin, cmd);

    if (cmd=="q") quit();

    if(cmd == "0"){
        nextPage();
        airportStatistics(network);
    }

    while(cmd !="q" && cmd != "0"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }
}

void Menu::insertNumberOfStops(Network network, Airport *airport) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│                Number of Stops              │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ > Type the max number of stops in your trip │\n"
            "│                                             │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;

    getline(cin, cmd);

    while( stoi(cmd) < 0){
        cout<<"ERROR: Choose a valid number \n";
        getline(cin, cmd);
    }

    nextPage();
    reachableDestinationsWithXStops(network, airport, stoi(cmd));
}

void Menu::reachableDestinationsWithXStops(Network network, Airport *airport, int stops) {
    int cities, airports, countries;

    network.getDestNumFromAtDist(airport->getIATA(), stops, airports,cities,countries);

    cout << "╒═════════════════════════════════════════════╕\n"
            "│             Available destinations          │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ Given a maximum of " << stops << " stops:                 │\n"
            "│ " <<airport->getIATA()<<" has available flights to:               │\n"
            "│                                             │\n"
            "│ "<<cities<<" cities                                 │\n"
            "│ "<<countries<<" countries                               │\n"
            "│ "<<airports<<"  airports                              │\n"
            "│                                             │\n"
            "│ > Back [0]                       > Quit [q] │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;
    getline(cin, cmd);

    if (cmd=="q") quit();

    if(cmd == "0"){
        nextPage();
        airportStatistics(network);
    }

    while(cmd !="q" && cmd != "0"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }
}

void Menu::insertK(Network network) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│                Top k airport                │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ > Insert the ranking number of the airport  │\n"
            "│                                             │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;

    getline(cin, cmd);

    while( stoi(cmd) <= 0 || stoi(cmd) > 3019 ){
        cout<<"ERROR: Choose a valid number \n";
        getline(cin, cmd);
    }

    nextPage();
    topKAirport(network,stoi(cmd));
}
void Menu::topKAirport(Network network, int k) {

    vector<Airport*> airpList = network.findTopKAirports(k);

    Airport* kAirport = airpList[k-1];

    cout << "╒═════════════════════════════════════════════╕\n"
            "│                Top k airport                │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ Here's the top k airport with the greatest  │\n"
            "│ number of flights, with k = "<< k <<":              │\n"
            "│                                             │\n"
            "│  Airport: "<< kAirport->getIATA() << "                               │\n"
            "│  Number of flights: "<<kAirport->getTrafic() <<"                    │\n"
            "│                                             │\n"
            "│ > Back [0]                       > Quit [q] │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;
    getline(cin, cmd);

    if (cmd=="q") quit();

    if(cmd == "0"){
        nextPage();
        airportStatistics(network);
    }

    while(cmd !="q" && cmd != "0"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

}

void Menu::essentialAirports(Network network) {
    std::unordered_set<Airport*> airportList = network.articulationAirports();
    int counter = 0;

    cout << "╒═════════════════════════════════════════════╕\n"
            "│              Essential Airports             │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ Here's a list of all the essential Airports │\n"
            "│                                             │\n";

    for(auto airport: airportList) {
        cout <<"| "<<airport->getName() <<"                   │\n";
        counter++;
    }

    cout << "│                                             │\n"
            "│ Number of essential airports: "<< counter << "           │\n"
            "│                                             │\n"
            "│ > Back [0]                       > Quit [q] │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;
    getline(cin, cmd);

    if (cmd=="q") quit();

    if(cmd == "0"){
        nextPage();
        airportStatistics(network);
    }

    while(cmd !="q" && cmd != "0"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

}

void Menu::flightStatistics(Network network) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│        Number of flights (w/ filters)       │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ Check flights per:                          │\n"
            "│ > Airline                               [1] │\n"
            "│ > City                                  [2] │\n"
            "│                                             │\n"
            "│ > Back [0]                       > Quit [q] │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";

    string cmd;
    getline(cin, cmd);
    if (cmd=="q") quit();

    while(cmd !="q" && cmd != "0" && cmd!="1" && cmd!="2" && cmd!="3"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

    int operation = stoi(cmd);

    switch (operation) {
        case 0:
            nextPage();
            statistics(network);
            break;
        case 1:
            nextPage();
            insertAirlineName(network);
            break;
        case 2:
            nextPage();
            insertCountryAndCityName(network,1);
            break;
        case 3:
           //todo
            break;
    }
}

void Menu::insertAirlineName(Network network) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│              Flights per Airline            │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│          > Type the Airline name            │\n"
            "│                                             │\n"
            "│                (e.g: TAP)                   │\n"
            "│                                             │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;

    getline(cin, cmd);
    string airlineName = cmd;

    if(network.getFligthsNumPerAirline(airlineName) == 0){ //
        cout<<"ERROR: The provided airline has no flights or was not found\n\n> Back [0]                       > Retry [r] \n";
        getline(cin, cmd);

        while(cmd!="0" && cmd!="r"){
            cout<<"ERROR: Choose a valid option! \n\n> Back [0]                       > Retry [r] \n";
            getline(cin, cmd);
        }

        if(cmd=="0"){
            nextPage();
            flightStatistics(network);
        }

        if(cmd=="r"){
            nextPage();
            insertAirlineName(network);
        }

    }

    nextPage();
    flightsPerAirline(network,airlineName);
}

void Menu::flightsPerAirline(Network network, std::string airlineName) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│             Flights per Airline             │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ "<<airlineName<<" has currently "<< network.getFligthsNumPerAirline(airlineName)<<" flights               │\n"
            "│                                             │\n"
            "│ > Back [0]                       > Quit [q] │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;
    getline(cin, cmd);

    if (cmd=="q") quit();

    if(cmd == "0"){
        nextPage();
        flightStatistics(network);
    }

    while(cmd !="q" && cmd != "0"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

}

void Menu::insertCountryAndCityName(Network network, int option) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│              Flights per City               │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│    > Type the city and its country          │\n"
            "│                                             │\n"
            "│           (e.g: Lisbon,Portugal)            │\n"
            "│                                             │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;

    getline(cin, cmd);

    std::istringstream iss (cmd);

    string city, country;

    std::getline(iss, city, ',');
    std::getline(iss, country);

    if(network.getFligthsNumPerCity(city,country) == 0){
        cout<<"ERROR: The provided city has no flights or was not found\n\n> Back [0]                       > Retry [r] \n";
        getline(cin, cmd);

        while(cmd!="0" && cmd!="r"){
            cout<<"ERROR: Choose a valid option! \n\n> Back [0]                       > Retry [r] \n";
            getline(cin, cmd);
        }

        if(cmd=="0"){
            switch (option){
                case 1:
                    nextPage();
                    flightStatistics(network);
                    break;
                case 2:
                    nextPage();
                    statistics(network);
                    break;
            }
        }

        if(cmd=="r"){
            nextPage();
            insertCountryAndCityName(network,option);
        }

    }
    switch (option){
        case 1:
            nextPage();
            flightsPerCity(network,city,country);
            break;
        case 2:
            nextPage();
            availableCountriesForACity(network,city,country);
            break;

    }


}

void Menu::flightsPerCity(Network network, std::string cityName, std::string countryName) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│             Flights per City                │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ The referred city has currently " << network.getFligthsNumPerCity(cityName,countryName) <<" flights │\n"
            "│                                             │\n"
            "│ > Back [0]                       > Quit [q] │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;
    getline(cin, cmd);

    if (cmd=="q") quit();

    if(cmd == "0"){
        nextPage();
        flightStatistics(network);
    }

    while(cmd !="q" && cmd != "0"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

}

void Menu::availableCountriesForACity(Network network, std::string cityName, std::string countryName) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│             Flights per City                │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ The referred city has currently flights to  │\n"
            "│ " << network.numberOfCountriesACityFliesTo(cityName, countryName) << " different countries                      │\n"
            "│                                             │\n"
            "│ > Back [0]                       > Quit [q] │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;
    getline(cin, cmd);

    if (cmd=="q") quit();

    if(cmd == "0"){
        nextPage();
        flightStatistics(network);
    }

    while(cmd !="q" && cmd != "0"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }
}

void Menu::flightTripWithMostStops(Network network) {
    int stops;
    vector<pair<Airport*,Airport*>> airportsSourceAndDest;
    network.getMaxStopsBetweenAirports(stops, airportsSourceAndDest);


    cout << "╒═════════════════════════════════════════════╕\n"
            "│       Flight trip(s) with the most stops    │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ Max number of stops: "<< stops << "                     │\n";

    for(auto airportsPair: airportsSourceAndDest) {
       cout << "│                                             │\n";
        cout <<"| Source:"<<airportsPair.first->getName() <<"                   │\n";
        cout <<"| Dest:"<<airportsPair.second->getName() <<"                    │\n";
    }

    cout << "│                                             │\n"
            "│ > Back [0]                       > Quit [q] │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;
    getline(cin, cmd);

    if (cmd=="q") quit();

    if(cmd == "0"){
        nextPage();
        flightStatistics(network);
    }

    while(cmd !="q" && cmd != "0"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }
}

















