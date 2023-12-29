#include "Network.h"


class Menu{

public:

    void nextPage();
    void run();
    void quit();


    void statistics(Network network);

    void airportStatistics(Network network);

    void insertAirportName(Network network, int option);

    void checkAvailableAirlines(Network network, Airport *airport);

    void flightsPerAirport(Network network, Airport *airport);

    void availableCountriesForAnAirport(Network network, Airport *airport);

    void availableDestinations(Network network, Airport *airport);

    void reachableDestinationsWithXStops(Network network, Airport *airport);

    void topKAirport(Network network);

    void flightStatistics(Network network);

    void insertAirlineName(Network network);

    void flightsPerAirline(Network network, std::string airlineName);

    void insertCountryAndCityName(Network network);

    void flightsPerCity(Network network, std::string cityName, std::string countryName);
};