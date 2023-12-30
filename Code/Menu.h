#include "Network.h"


class Menu{

public:

    void nextPage();
    void run();
    void quit();

    //------------------------------- network statistics---------------------
    void statistics(Network network); // tem o 3.i


    void airportStatistics(Network network);
    void insertAirportName(Network network, int option);
    void checkAvailableAirlines(Network network, Airport *airport);//3.ii pt2
    void flightsPerAirport(Network network, Airport *airport);//3.ii pt1
    void availableCountriesForAnAirport(Network network, Airport *airport); //3.iv pt1
    void availableDestinations(Network network, Airport *airport); //3.v
    void insertNumberOfStops(Network network, Airport *airport);
    void reachableDestinationsWithXStops(Network network, Airport *airport, int stops); //3.vi
    void insertK(Network network);
    void topKAirport(Network network, int k); //3.viii
    void essentialAirports(Network network); //3.ix


    void flightStatistics(Network network);
    void insertAirlineName(Network network);
    void flightsPerAirline(Network network, std::string airlineName); //3.iii pt1
    void insertCountryAndCityName(Network network, int option);
    void flightsPerCity(Network network, std::string cityName, std::string countryName); //3.iii pt2


    void availableCountriesForACity(Network network, std::string cityName, std::string countryName); //3.iv pt2
    void flightTripWithMostStops(Network network); //3.vii
    //------------------------------------------------------------------------

};