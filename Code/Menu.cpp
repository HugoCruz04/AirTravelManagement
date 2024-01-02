
#include "Menu.h"
#include <sstream>
#include <iomanip>

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
            bestFlightOption(network);
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
            "│       Registered airports: " << setw(5)<<left<<network.getAirportsNum() << "            │\n"
            "│       Available flights: " << setw(5)<<left<<network.getFligthsNum() << "              │\n"
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
            "│                Airport IATA                 │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│          > Type the Airport code            │\n"
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
            "│ There are currently "<< setw(3)<<left<<airport->getAirlinesNum()<<" available airlines  │\n"
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
            "│ " <<airport->getIATA()<<" has currently "<< setw(3)<<left<<airport->getFlights().size()<<" outgoing flights      │\n"
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
            "│ "<< setw(3)<<left<<network.numberOfCountriesAnAirportFliesTo(airport->getIATA()) <<" countries                               │\n"
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

    cout <<std::setw(12)<< "╒═════════════════════════════════════════════╕\n"
            <<std::setw(12)<<"│             Available destinations          │\n"
            <<std::setw(12)<<"╞═════════════════════════════════════════════╡\n"
            <<"│ " <<setw(3)<<airport->getIATA()<<setw(7)<<" has available flights to:               │\n"
            <<std::setw(3)<<"│ "<<setw(4)<<cities<<setw(6)<<" cities                                 │\n"
            <<std::setw(3)<<"│ "<<setw(4)<<countries<<setw(6)<<" countries                              │\n"
            <<std::setw(3)<<"│ "<<setw(4)<<airports<<setw(6)<<" airports                               │\n"
            <<std::setw(12)<<"│                                             │\n"
            <<std::setw(12)<<"│ > Back [0]                       > Quit [q] │\n"
            <<std::setw(12)<<"╘═════════════════════════════════════════════╛\n"
            <<std::setw(12)<<"                                               \n";
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

    cout <<std::setw(12)<< "╒═════════════════════════════════════════════╕\n"
         <<std::setw(12)<<"│             Available destinations          │\n"
         <<std::setw(12)<<"╞═════════════════════════════════════════════╡\n"
         <<"│ " <<setw(3)<<airport->getIATA()<<setw(7)<<" has available flights to:               │\n"
         <<std::setw(3)<<"│ "<<setw(4)<<cities<<setw(6)<<" cities                                 │\n"
         <<std::setw(3)<<"│ "<<setw(4)<<countries<<setw(6)<<" countries                              │\n"
         <<std::setw(3)<<"│ "<<setw(4)<<airports<<setw(6)<<" airports                               │\n"
         <<std::setw(12)<<"│                                             │\n"
         <<std::setw(12)<<"│ > Back [0]                       > Quit [q] │\n"
         <<std::setw(12)<<"╘═════════════════════════════════════════════╛\n"
         <<std::setw(12)<<"                                               \n";
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
            "│ number of flights, with k = "<< setw(4)<<left<<k <<"            │\n"
            "│                                             │\n"
            "│  Airport: "<< setw(3)<<kAirport->getIATA() << "                               │\n"
            "│  Number of flights: "<<setw(4)<<left<<kAirport->getTrafic() <<"                    │\n"
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
    Network temp;
    temp.readAiports("dataset/airports.csv");
    temp.readFlights("dataset/flights.csv");
    std::unordered_set<Airport*> airportList = temp.articulationAirports();

    cout << "╒═════════════════════════════════════════════╕\n"
            "│              Essential Airports             │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ Here's a list of all the essential Airports │\n"
            "│                                             │\n";

    for(auto airport: airportList) {
        cout <<"│ "<<setw(44)<<std::left <<airport->getName()<<"│\n";
    }

    cout << "│                                             │\n"
            "│ Number of essential airports: "<< setw(6)<<left<<airportList.size() << "        │\n"
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

    while(cmd !="q" && cmd != "0" && cmd!="1" && cmd!="2"){
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
            //todo;
            break;
    }
}

void Menu::insertAirlineName(Network network) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│                    Airline                  │\n"
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
            "│ "<<airlineName<<" has currently "<< setw(3)<<left<<network.getFligthsNumPerAirline(airlineName)<<" flights               │\n"
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
            "│                   City                      │\n"
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
            "│ The referred city has currently " << setw(4)<<left<<network.getFligthsNumPerCity(cityName,countryName) <<"flights │\n"
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
            "│        " << setw(3)<<left<<network.numberOfCountriesACityFliesTo(cityName, countryName) << " different countries              │\n"
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
            "│     Flight trip(s) with the most stops      │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ Max number of stops: "<<setw(3)<<left <<stops << "                    │\n";

    for(auto airportsPair: airportsSourceAndDest) {
       cout << "│                                             │\n";
        cout <<"│ Source: "<<setw(36)<<std::left<<airportsPair.first->getName() <<"│\n";
        cout <<"│ Dest: "<<setw(38)<<std::left<<airportsPair.second->getName() <<"│\n";
    }

    cout << "│                                             │\n"
            "│ > Back [0]                       > Quit [q] │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;
    getline(cin, cmd);

    while(cmd !="q" && cmd != "0"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }
    if (cmd=="q") quit();

    if(cmd == "0"){
        nextPage();
        statistics(network);
    }
}

void Menu::bestFlightOption(Network network) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│             Best flight options             │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ > Best flight (w/o filters)             [1] │\n"
            "│ > Best flight (w/ filters)              [2] │\n"
            "│                                             │\n"
            "│ > Back [0]                       > Quit [q] │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";

    string cmd;
    getline(cin, cmd);
    if (cmd=="q") quit();

    while(cmd !="q" && cmd != "0" && cmd!="1" && cmd!="2"){
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
            sourceCriteria(network);
            break;
        case 2:
            nextPage();
            bestFlightOptionWithFilters(network);
            break;
    }
}

void Menu::sourceCriteria(Network network) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│                Source criteria              │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ Choose a criteria for source airport:       │\n"
            "│ > Airport code/name                     [1] │\n"
            "│ > City name                             [2] │\n"
            "│ > Geographical coordinates              [3] │\n"
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
            bestFlightOption(network);
            break;
        case 1:
            nextPage();
            insertSourceAirportNameOrCode(network);
            break;
        case 2:
            nextPage();
            insertSourceAirportCityAndCountry(network);
            break;
        case 3:
            nextPage();
            insertSourceAirportCoordinates(network);
            break;
    }

}

void Menu::insertSourceAirportNameOrCode(Network network) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│         Source airport's name or code       │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│   > Type the airport's Name or Code         │\n"
            "│                                             │\n"
            "│          [name] (e.g: Lisboa )              │\n"
            "│          [code] (e.g: LIS )                 │\n"
            "│                                             │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;

    getline(cin, cmd);
    Airport* airport = network.findAirport(cmd);

    if(airport == nullptr){
        airport = network.findAirportByName(cmd);
    }

    if(airport == nullptr){
        cout<<"ERROR: Airport not found\n\n> Back [0]                       > Retry [r] \n";
        getline(cin, cmd);

        while(cmd!="0" && cmd!="r"){
            cout<<"ERROR: Choose a valid option! \n\n> Back [0]                       > Retry [r] \n";
            getline(cin, cmd);
        }

        if(cmd=="0"){
            nextPage();
            sourceCriteria(network);

        }

        if(cmd=="r"){
            nextPage();
            insertSourceAirportNameOrCode(network);
        }

    }

    std::vector<Airport*> sourceAirportList;
    sourceAirportList.push_back(airport);

    nextPage();
    destCriteria(network, sourceAirportList);

}
void Menu::insertSourceAirportCityAndCountry(Network network) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│                    City                     │\n"
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
            nextPage();
            sourceCriteria(network);
        }

        if(cmd=="r"){
            nextPage();
            insertSourceAirportCityAndCountry(network);
        }
    }
    vector <Airport*> sourceAirportList = network.findAirportsInCity(city,country);

    nextPage();
    destCriteria(network, sourceAirportList);

}

void Menu::insertSourceAirportCoordinates(Network network) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│           Geographical coordinates          │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│    > Type the Latitude and Longitude        │\n"
            "│                                             │\n"
            "│            [Format: LAT,LONG]               │\n"
            "│          (e.g  49.012779,2.550000)          │\n"
            "│                                             │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;

    getline(cin, cmd);

    std::istringstream iss (cmd);

    string latitudeStr, longitudeStr;

    std::getline(iss, latitudeStr, ',');
    std::getline(iss, longitudeStr);

    float latitude = stof(latitudeStr);
    float longitude = stof(longitudeStr);

    std::vector<Airport*> sourceAirportList = network.findClosestAirports(latitude, longitude);

    if(sourceAirportList.empty()){
        cout<<"ERROR: The provided coordinates are invalid or no airport was found\n\n> Back [0]                       > Retry [r] \n";
        getline(cin, cmd);

        while(cmd!="0" && cmd!="r"){
            cout<<"ERROR: Choose a valid option! \n\n> Back [0]                       > Retry [r] \n";
            getline(cin, cmd);
        }

        if(cmd=="0"){
            nextPage();
            sourceCriteria(network);
        }

        if(cmd=="r"){
            nextPage();
            insertSourceAirportCoordinates(network);
        }

    }

    nextPage();
    destCriteria(network, sourceAirportList);

}

void Menu::destCriteria(Network network, std::vector<Airport*> sourceAirportList) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│                Dest criteria                │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ Choose a criteria for dest airport:         │\n"
            "│ > Airport code/name                     [1] │\n"
            "│ > City name                             [2] │\n"
            "│ > Geographical coordinates              [3] │\n"
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
            sourceCriteria(network);
            break;
        case 1:
            nextPage();
            insertDestAirportNameOrCode(network, sourceAirportList);
            break;
        case 2:
            nextPage();
            insertDestAirportCityAndCountry(network, sourceAirportList);
            break;
        case 3:
            nextPage();
            insertDestAirportCoordinates(network, sourceAirportList);
            break;
    }

}

void Menu::insertDestAirportNameOrCode(Network network, std::vector<Airport *> sourceAirportList) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│          Dest airport's name or code        │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│   > Type the airport's Name or Code         │\n"
            "│                                             │\n"
            "│          [name] (e.g: Thule Air Base )      │\n"
            "│          [code] (e.g: THU )                 │\n"
            "│                                             │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;

    getline(cin, cmd);
    Airport* airport = network.findAirport(cmd);

    if(airport == nullptr){
        airport = network.findAirportByName(cmd);
    }

    if(airport == nullptr){
        cout<<"ERROR: Airport not found\n\n> Back [0]                       > Retry [r] \n";
        getline(cin, cmd);

        while(cmd!="0" && cmd!="r"){
            cout<<"ERROR: Choose a valid option! \n\n> Back [0]                       > Retry [r] \n";
            getline(cin, cmd);
        }

        if(cmd=="0"){
            nextPage();
            destCriteria(network, sourceAirportList);

        }

        if(cmd=="r"){
            nextPage();
            insertDestAirportNameOrCode(network, sourceAirportList);
        }

    }

    std::vector<Airport*> destAirportList;
    destAirportList.push_back(airport);

    nextPage();
    createBestFlightOption(network, sourceAirportList, destAirportList);
}

void Menu::insertDestAirportCityAndCountry(Network network, std::vector<Airport *> sourceAirportList) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│                    City                     │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│    > Type the city and its country          │\n"
            "│                                             │\n"
            "│           (e.g: Thule,Greenland)            │\n"
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
            nextPage();
            destCriteria(network, sourceAirportList);
        }

        if(cmd=="r"){
            nextPage();
            insertDestAirportCityAndCountry(network, sourceAirportList);
        }
    }
    vector <Airport*> destAirportList = network.findAirportsInCity(city,country);

    nextPage();
    createBestFlightOption(network, sourceAirportList, destAirportList);
}

void Menu::insertDestAirportCoordinates(Network network, std::vector<Airport *> sourceAirportList) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│           Geographical coordinates          │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│    > Type the Latitude and Longitude        │\n"
            "│                                             │\n"
            "│            [Format: LAT,LONG]               │\n"
            "│          (e.g  76.531203,-68.703161)        │\n"
            "│                                             │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;

    getline(cin, cmd);

    std::istringstream iss (cmd);

    string latitudeStr, longitudeStr;

    std::getline(iss, latitudeStr, ',');
    std::getline(iss, longitudeStr);

    float latitude = stof(latitudeStr);
    float longitude = stof(longitudeStr);

    std::vector<Airport*> destAirportList = network.findClosestAirports(latitude, longitude);

    if(sourceAirportList.empty()){
        cout<<"ERROR: The provided coordinates are invalid or no airport was found\n\n> Back [0]                       > Retry [r] \n";
        getline(cin, cmd);

        while(cmd!="0" && cmd!="r"){
            cout<<"ERROR: Choose a valid option! \n\n> Back [0]                       > Retry [r] \n";
            getline(cin, cmd);
        }

        if(cmd=="0"){
            nextPage();
            destCriteria(network, sourceAirportList);
        }

        if(cmd=="r"){
            nextPage();
            insertDestAirportCoordinates(network,sourceAirportList);
        }

    }
    nextPage();
    createBestFlightOption(network, sourceAirportList, destAirportList);
}

void Menu::createBestFlightOption(Network network, std::vector<Airport *> sourceAirportList, std::vector<Airport *> destAirportList) {
    std::vector<std::vector<Airport *>> shortestPathList = network.shortestPathsAuxiliary(sourceAirportList,destAirportList);


    cout << "╒═════════════════════════════════════════════╕\n"
            "│             Best flight options             │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ The best flight options between the given   │\n"
            "│ locations is:                               │\n"
            ;

    int i = 1;

    for(std::vector<Airport *> trip : shortestPathList){

        cout << "│                                             │\n"
                "│ Trip option # "<<setw(2)<<left<<i<<":                           │\n";

        int j = 0;
        int size = trip.size();

        for(Airport* airport : trip){
           if(j == 0){
               cout << "│   Starting at: " << airport->getIATA() << "                          │\n"
                       "│                                             │\n";

           }

           else if(j == size - 1){
               cout << "│                                             │\n"
                       "│   Arriving at: " << airport->getIATA() << "                          │\n";

           }

           else{
               cout << "│   Stopping at: " << airport->getIATA() << "                          │\n";
           }


           j++;
        }

        cout << "│                                             │\n";
        i++;
    }

    cout << "│                                             │\n"
            "│ > Back [0]                       > Quit [q] │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";

    string cmd;
    getline(cin, cmd);
    if (cmd=="q") quit();

    while(cmd !="q" && cmd != "0" && cmd!="1" && cmd!="2"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

    if (stoi(cmd) == 0){
        nextPage();
        bestFlightOption(network);
    }

}


void Menu::bestFlightOptionWithFilters(Network network) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│         Best flight option (w/ filters)     │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ Available filters:                          │\n"
            "│ > User provided airlines                [1] │\n"
            "│                                             │\n"
            "│ > Back [0]                       > Quit [q] │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;
    getline(cin, cmd);
    if (cmd=="q") quit();

    while(cmd !="q" && cmd != "0" && cmd!="1" && cmd!="2"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

    int operation = stoi(cmd);
    std::vector<Airline> airlines;

    switch (operation) {
        case 0:
            nextPage();
            bestFlightOption(network);
            break;
        case 1:
            nextPage();
            insertAirlineList(network,airlines);
            break;
    }
}

void Menu::insertAirlineList(Network network, std::vector<Airline> airlines) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│                 Add Airline                 │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│     > Type the airline you want to add      │\n"
            "│                                             │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;

    getline(cin, cmd);
    string airlineCode = cmd;


    if(network.getFligthsNumPerAirline(airlineCode) == 0){
        cout<<"ERROR: The provided airline has no flights or was not found\n"
              "\n> Back [0]                       > Retry [r] \n";
        getline(cin, cmd);

        while(cmd!="0" && cmd!="r"){
            cout<<"ERROR: Choose a valid option! \n\n> Back [0]                       > Retry [r] \n";
            getline(cin, cmd);
        }

        if(cmd=="0"){
            nextPage();
            bestFlightOptionWithFilters(network);
        }

        if(cmd=="r"){
            nextPage();
            insertAirlineList(network,airlines);
        }

    }

    for(auto airline : airlines){
        if( airline.getcode() == airlineCode){
            cout<<"ERROR: The provided airline has already been added\n"
                  "\n> Back [0]                       > Retry [r] \n";
            getline(cin, cmd);

            while(cmd!="0" && cmd!="r"){
                cout<<"ERROR: Choose a valid option! \n\n> Back [0]                       > Retry [r] \n";
                getline(cin, cmd);
            }

            if(cmd=="0"){
                nextPage();
                bestFlightOptionWithFilters(network);
            }

            if(cmd=="r"){
                nextPage();
                insertAirlineList(network,airlines);
            }


        }


    }


    Airline newAirline = Airline(cmd);
    airlines.push_back(newAirline);

    nextPage();
    checkAddedAirlines(network,airlines);


}

void Menu::checkAddedAirlines(Network network, std::vector<Airline> airlines) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│               Added Airlines                │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ These are the currently selected airlines:  │\n";

    for( auto airline : airlines){
        cout <<  "│   ->"<<airline.getcode()<<"                                     │\n";

    }

    cout << "│                                             │\n"
            "│ > Add airline                           [1] │\n"
            "│ > Remove airline                        [2] │\n"
            "│                                             │\n"
            "│ Back[0]                             Next[9] │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";

    string cmd;
    getline(cin, cmd);
    if (cmd=="q") quit();

    while(cmd !="q" && cmd != "0" && cmd!="1" && cmd!="2" && cmd!="9"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

    int operation = stoi(cmd);

    switch (operation) {
        case 0:
            nextPage();
            bestFlightOptionWithFilters(network);
            break;
        case 1:
            nextPage();
            insertAirlineList(network,airlines);
            break;
        case 2:
            nextPage();
            removeAirline(network,airlines);
            break;
        case 9:
            nextPage();
            Network newNetwork = network.filterByAirlines(airlines);
            sourceCriteria(network,newNetwork,airlines);
            break;
    }

}

void Menu::removeAirline(Network network, std::vector<Airline> airlines) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│                 Remove Airline              │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│  > Type the airline you want to remove      │\n"
            "│                                             │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;

    getline(cin, cmd);
    string airlineCode = cmd;

    if(network.getFligthsNumPerAirline(airlineCode) == 0){ //
        cout<<"ERROR: The provided airline has no flights or was not found\n\n> Back [0]                       > Retry [r] \n";
        getline(cin, cmd);

        while(cmd!="0" && cmd!="r"){
            cout<<"ERROR: Choose a valid option! \n\n> Back [0]                       > Retry [r] \n";
            getline(cin, cmd);
        }

        if(cmd=="0"){
            nextPage();
            bestFlightOptionWithFilters(network);
        }

        if(cmd=="r"){
            nextPage();
            insertAirlineList(network,airlines);
        }

    }

    auto it = airlines.begin();

    while (it != airlines.end()){
        if(it->getcode() == airlineCode){
            it = airlines.erase(it);
            break;
        }
        it++;
    }

    nextPage();
    checkAddedAirlines(network,airlines);

}

void Menu::sourceCriteria(Network network, Network newNetwork, std::vector<Airline> airlines) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│                Source criteria              │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ Choose a criteria for source airport:       │\n"
            "│ > Airport code/name                     [1] │\n"
            "│ > City name                             [2] │\n"
            "│ > Geographical coordinates              [3] │\n"
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
            checkAddedAirlines(network, airlines);
            break;
        case 1:
            nextPage();
            insertSourceAirportNameOrCode(network, newNetwork, airlines);
            break;
        case 2:
            nextPage();
            insertSourceAirportCityAndCountry(network,newNetwork, airlines);
            break;
        case 3:
            nextPage();
            insertSourceAirportCoordinates(network,newNetwork, airlines);
            break;
    }

}


void Menu::insertSourceAirportNameOrCode(Network network, Network newNetwork, std::vector<Airline> airlines) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│         Source airport's name or code       │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│   > Type the airport's Name or Code         │\n"
            "│                                             │\n"
            "│          [name] (e.g: Lisboa )              │\n"
            "│          [code] (e.g: LIS )                 │\n"
            "│                                             │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;

    getline(cin, cmd);
    Airport* airport = newNetwork.findAirport(cmd);

    if(airport == nullptr){
        airport = newNetwork.findAirportByName(cmd);
    }

    if(airport == nullptr){
        cout<<"ERROR: Airport not found\n\n> Back [0]                       > Retry [r] \n";
        getline(cin, cmd);

        while(cmd!="0" && cmd!="r"){
            cout<<"ERROR: Choose a valid option! \n\n> Back [0]                       > Retry [r] \n";
            getline(cin, cmd);
        }

        if(cmd=="0"){
            nextPage();
            sourceCriteria(network,newNetwork,airlines);

        }

        if(cmd=="r"){
            nextPage();
            insertSourceAirportNameOrCode(network,newNetwork, airlines);
        }

    }

    std::vector<Airport*> sourceAirportList;
    sourceAirportList.push_back(airport);

    nextPage();
    destCriteria(network, newNetwork, airlines, sourceAirportList);

}

void Menu::insertSourceAirportCityAndCountry(Network network, Network newNetwork, std::vector<Airline> airlines) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│                    City                     │\n"
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

    if(newNetwork.getFligthsNumPerCity(city,country) == 0){
        cout<<"ERROR: The provided city has no flights or was not found\n\n> Back [0]                       > Retry [r] \n";
        getline(cin, cmd);

        while(cmd!="0" && cmd!="r"){
            cout<<"ERROR: Choose a valid option! \n\n> Back [0]                       > Retry [r] \n";
            getline(cin, cmd);
        }

        if(cmd=="0"){
            nextPage();
            sourceCriteria(network, newNetwork, airlines);
        }

        if(cmd=="r"){
            nextPage();
            insertSourceAirportCityAndCountry(network, newNetwork,airlines);
        }
    }
    vector <Airport*> sourceAirportList = newNetwork.findAirportsInCity(city,country);

    nextPage();
    destCriteria(network, newNetwork, airlines, sourceAirportList);
}

void Menu::insertSourceAirportCoordinates(Network network, Network newNetwork, std::vector<Airline> airlines) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│           Geographical coordinates          │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│    > Type the Latitude and Longitude        │\n"
            "│                                             │\n"
            "│            [Format: LAT,LONG]               │\n"
            "│          (e.g  49.012779,2.550000)          │\n"
            "│                                             │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;

    getline(cin, cmd);

    std::istringstream iss (cmd);

    string latitudeStr, longitudeStr;

    std::getline(iss, latitudeStr, ',');
    std::getline(iss, longitudeStr);

    float latitude = stof(latitudeStr);
    float longitude = stof(longitudeStr);

    std::vector<Airport*> sourceAirportList = newNetwork.findClosestAirports(latitude, longitude);

    if(sourceAirportList.empty()){
        cout<<"ERROR: The provided coordinates are invalid or no airport was found\n\n> Back [0]                       > Retry [r] \n";
        getline(cin, cmd);

        while(cmd!="0" && cmd!="r"){
            cout<<"ERROR: Choose a valid option! \n\n> Back [0]                       > Retry [r] \n";
            getline(cin, cmd);
        }

        if(cmd=="0"){
            nextPage();
            sourceCriteria(network, newNetwork, airlines);
        }

        if(cmd=="r"){
            nextPage();
            insertSourceAirportCoordinates(network, newNetwork, airlines);
        }

    }

    nextPage();
    destCriteria(network, newNetwork, airlines ,sourceAirportList);

}



void Menu::destCriteria(Network network, Network newNetwork, std::vector<Airline> airlines, std::vector<Airport *> sourceAirportList) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│                Dest criteria                │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ Choose a criteria for dest airport:         │\n"
            "│ > Airport code/name                     [1] │\n"
            "│ > City name                             [2] │\n"
            "│ > Geographical coordinates              [3] │\n"
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
            sourceCriteria(network,newNetwork, airlines);
            break;
        case 1:
            nextPage();
            insertDestAirportNameOrCode(network,newNetwork, airlines ,sourceAirportList);
            break;
        case 2:
            nextPage();
            insertDestAirportCityAndCountry(network,newNetwork, airlines ,sourceAirportList);
            break;
        case 3:
            nextPage();
            insertDestAirportCoordinates(network,newNetwork, airlines ,sourceAirportList);
            break;
    }

}

void Menu::insertDestAirportNameOrCode(Network network, Network newNetwork, std::vector<Airline> airlines,std::vector<Airport *> sourceAirportList) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│          Dest airport's name or code        │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│   > Type the airport's Name or Code         │\n"
            "│                                             │\n"
            "│          [name] (e.g: Thule Air Base )      │\n"
            "│          [code] (e.g: THU )                 │\n"
            "│                                             │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;

    getline(cin, cmd);
    Airport* airport = newNetwork.findAirport(cmd);

    if(airport == nullptr){
        airport = newNetwork.findAirportByName(cmd);
    }

    if(airport == nullptr){
        cout<<"ERROR: Airport not found\n\n> Back [0]                       > Retry [r] \n";
        getline(cin, cmd);

        while(cmd!="0" && cmd!="r"){
            cout<<"ERROR: Choose a valid option! \n\n> Back [0]                       > Retry [r] \n";
            getline(cin, cmd);
        }

        if(cmd=="0"){
            nextPage();
            destCriteria(network, newNetwork, airlines, sourceAirportList);

        }

        if(cmd=="r"){
            nextPage();
            insertDestAirportNameOrCode(network, newNetwork, airlines, sourceAirportList);
        }

    }

    std::vector<Airport*> destAirportList;
    destAirportList.push_back(airport);

    nextPage();
    createBestFlightOption(network, newNetwork, airlines,sourceAirportList, destAirportList);
}

void Menu::insertDestAirportCityAndCountry(Network network, Network newNetwork, std::vector<Airline> airlines,std::vector<Airport *> sourceAirportList) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│                    City                     │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│    > Type the city and its country          │\n"
            "│                                             │\n"
            "│           (e.g: Thule,Greenland)            │\n"
            "│                                             │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;

    getline(cin, cmd);

    std::istringstream iss (cmd);

    string city, country;

    std::getline(iss, city, ',');
    std::getline(iss, country);

    if(newNetwork.getFligthsNumPerCity(city,country) == 0){
        cout<<"ERROR: The provided city has no flights or was not found\n\n> Back [0]                       > Retry [r] \n";
        getline(cin, cmd);

        while(cmd!="0" && cmd!="r"){
            cout<<"ERROR: Choose a valid option! \n\n> Back [0]                       > Retry [r] \n";
            getline(cin, cmd);
        }

        if(cmd=="0"){
            nextPage();
            destCriteria(network, newNetwork, airlines, sourceAirportList);
        }

        if(cmd=="r"){
            nextPage();
            insertDestAirportCityAndCountry(network, newNetwork, airlines, sourceAirportList);
        }
    }
    vector <Airport*> destAirportList = newNetwork.findAirportsInCity(city,country);

    nextPage();
    createBestFlightOption(network, newNetwork, airlines, sourceAirportList, destAirportList);
}

void Menu::insertDestAirportCoordinates(Network network, Network newNetwork, std::vector<Airline> airlines,std::vector<Airport *> sourceAirportList) {
    cout << "╒═════════════════════════════════════════════╕\n"
            "│           Geographical coordinates          │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│    > Type the Latitude and Longitude        │\n"
            "│                                             │\n"
            "│            [Format: LAT,LONG]               │\n"
            "│          (e.g  76.531203,-68.703161)        │\n"
            "│                                             │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";
    string cmd;

    getline(cin, cmd);

    std::istringstream iss (cmd);

    string latitudeStr, longitudeStr;

    std::getline(iss, latitudeStr, ',');
    std::getline(iss, longitudeStr);

    float latitude = stof(latitudeStr);
    float longitude = stof(longitudeStr);

    std::vector<Airport*> destAirportList = newNetwork.findClosestAirports(latitude, longitude);

    if(sourceAirportList.empty()){
        cout<<"ERROR: The provided coordinates are invalid or no airport was found\n\n> Back [0]                       > Retry [r] \n";
        getline(cin, cmd);

        while(cmd!="0" && cmd!="r"){
            cout<<"ERROR: Choose a valid option! \n\n> Back [0]                       > Retry [r] \n";
            getline(cin, cmd);
        }

        if(cmd=="0"){
            nextPage();
            destCriteria(network, newNetwork, airlines, sourceAirportList);
        }

        if(cmd=="r"){
            nextPage();
            insertDestAirportCoordinates(network, newNetwork, airlines,sourceAirportList);
        }

    }
    nextPage();
    createBestFlightOption(network, newNetwork, airlines, sourceAirportList, destAirportList);
}

void Menu::createBestFlightOption(Network network, Network newNetwork, std::vector<Airline> airlines,std::vector<Airport *> sourceAirportList, std::vector<Airport *> destAirportList) {
    std::vector<std::vector<Airport *>> shortestPathList = newNetwork.shortestPathsAuxiliary(sourceAirportList,destAirportList);


    cout << "╒═════════════════════════════════════════════╕\n"
            "│             Best flight options             │\n"
            "╞═════════════════════════════════════════════╡\n"
            "│ The best flight options between the given   │\n"
            "│ locations is:                               │\n"
            ;

    int i = 1;

    for(std::vector<Airport *> trip : shortestPathList){

        cout << "│                                             │\n"
                "│ Trip option # "<<setw(2)<<left<<i<<":                           │\n";

        int j = 0;
        int size = trip.size();

        for(Airport* airport : trip){
            if(j == 0){
                cout << "│   Starting at: " << airport->getIATA() << "                          │\n"
                                                                     "│                                             │\n";

            }

            else if(j == size - 1){
                cout << "│                                             │\n"
                        "│   Arriving at: " << airport->getIATA() << "                          │\n";

            }

            else{
                cout << "│   Stopping at: " << airport->getIATA() << "                          │\n";
            }


            j++;
        }

        cout << "│                                             │\n";
        i++;
    }

    cout << "│                                             │\n"
            "│ > Back [0]                       > Quit [q] │\n"
            "╘═════════════════════════════════════════════╛\n"
            "                                               \n";

    string cmd;
    getline(cin, cmd);
    if (cmd=="q") quit();

    while(cmd !="q" && cmd != "0" && cmd!="1" && cmd!="2"){
        cout<<"ERROR: Choose a valid option \n";
        getline(cin, cmd);
    }

    if (stoi(cmd) == 0){
        nextPage();
        checkAddedAirlines(network,airlines);
    }

}





















