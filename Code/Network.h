#include <set>
#include <unordered_set>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "Airport.h"
#include "Flight.h"
#include "Airline.h"

#ifndef PROJETO_2_NETWORK_H
#define PROJETO_2_NETWORK_H


struct PairHash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // A simple hash combination function
        return h1 ^ h2;
    }
};

class Network{
private:
    std::vector<Airport*> Airports;
    std::vector<Airline> Airlines;
public:
    Airport* findAirport(std::string IATA);
    Airport* findAirportByName(std::string AirportName);
    std::vector<Airport*> getAirports();
    std::vector<Airline> getAirlines();
    void addAirport(std::string IATA, std::string name, std::string city, std::string country, float latitude, float longitude);
    void readAiports(std::string fileName);
    void readFlights(const std::string fileName);
    void readAirlines(const std::string fileName);
    void loadNetwork(const std::string aiportsFileName, const std::string flightsFileName);
    int getAirportsNum() const; //3.i
    int getFligthsNum() const;  //3.i
    int getFligthsNumPerCity(const std::string& city) const;           //3.iii eu pelo menos interpretei q eram funçoes assim q pediam
    int getFligthsNumPerAirline(const std::string& airlinecode) const; //3.iii
    int numberOfCountriesAnAirportFliesTo(const std::string& AirportIATA); //3.iv a)
    int numberOfCountriesACityFliesTo(const std::string& City); //3.iv b)
    void getDestNumFrom(std::string IATA, int &airports, int &cities, int &countries);//3.v
    void getDestNumFromAtDist(std::string IATA, int distance,int &airports, int &cities, int &countries); //3.vi

    int shortestPath(std::string start, std::string end);
    std::unordered_set<std::pair< std::string, std::string>, PairHash> findDiameter();//3.vii //saber se pede mesmo o diametro

    std::vector<Airport*> findTopKAirports(int k); //3.viii
    std::unordered_set<Airport*> articulationAirports();//3.ix


    std::vector<std::vector<Airport*>> shortestPathsIATA(const std::string& startIATA, const std::string& endIATA);//4.i airportsIATA
    std::vector<std::vector<Airport*>> shortestPathsName(const std::string& airportNameStart, const std::string& airportNameEnd);//4.i airportsName

    std::vector<Airport*> findAirportsInCity(const std::string CityName, const std::string countryName);
    std::vector<std::vector<Airport*>> shortestPathsCityNames(const std::string CityNameStart, const std::string countrystart, const std::string CityNameEnd, const std::string countryEnd);//4.ii city names

    std::vector<Airport*> findClosestAirports(float latitude, float longitude);
    std::vector<std::vector<Airport*>> shortestPathsCoordinates(float latitudeStart, float longitudeStart, float latitudeEnd, float longitudeEnd);//4.iii

};

#endif //PROJETO_2_NETWORK_H
