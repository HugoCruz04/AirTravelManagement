#include "Network.h"


class Menu{

public:

    void nextPage();
    void run();
    void quit();

    //------------------------------- network statistics---------------------
    void statistics(Network network);


    void airportStatistics(Network network);
    void insertAirportName(Network network, int option);
    void checkAvailableAirlines(Network network, Airport *airport);//ii pt2
    void flightsPerAirport(Network network, Airport *airport);//ii pt1
    void availableCountriesForAnAirport(Network network, Airport *airport); //iv pt1
    void availableDestinations(Network network, Airport *airport); //v
    void insertNumberOfStops(Network network, Airport *airport);
    void reachableDestinationsWithXStops(Network network, Airport *airport, int stops); //vi
    void insertK(Network network);
    void topKAirport(Network network); //viii
    void essentialAirports(Network network); // ix


    void flightStatistics(Network network);
    void insertAirlineName(Network network);
    void flightsPerAirline(Network network, std::string airlineName); //iii pt1
    void insertCountryAndCityName(Network network, int option);
    void flightsPerCity(Network network, std::string cityName, std::string countryName); //iii pt2


    void availableCountriesForACity(Network network, std::string cityName, std::string countryName); //iv pt2
    void flightTripsWithMostStops(Network network); //vii
    //------------------------------------------------------------------------

};