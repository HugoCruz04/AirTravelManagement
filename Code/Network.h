#include <set>
#include <map>
#include <unordered_set>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <list>
#include "Airport.h"
#include "Flight.h"
#include "Airline.h"

#ifndef PROJETO_2_NETWORK_H
#define PROJETO_2_NETWORK_H

/**
 * @brief Hash function for std::pair used in unordered_set.
 */
struct PairHash {
    /**
    * @brief Operator overload for hashing std::pair.
    *
    * @tparam T1 Type of the first element.
    * @tparam T2 Type of the second element.
    * @param p The std::pair to be hashed.
    * @return std::size_t The hash value.
    */
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // A simple hash combination function
        return h1 ^ h2;
    }
};


/**
 * @brief The Network class represents a network, that is a Graph, of airports (Vertices) and flights (Edges).
 *
 * This class provides various functionalities related to airports, flights, and airlines.
 */
class Network{
private:
    std::vector<Airport*> Airports; /**< Vector containing pointers to Airport objects. */
    std::vector<Airline> Airlines; /**< Vector containing Airline objects. */
public:
    void setAirports(const std::vector<Airport *> &airports);
    void setAirlines(const std::vector<Airline> &airlines);
    std::vector<Airport*> getAirports();
    std::vector<Airline> getAirlines();

    /**
     * @brief Adds a Airport(Vertex) to the Network
     *
     * @param IATA
     * @param name
     * @param city
     * @param country
     * @param latitude
     * @param longitude
     */
    void addAirport(std::string IATA, std::string name, std::string city, std::string country, float latitude, float longitude);
    /**
     * @brief Reads and parses the Airports.csv file
     *
     * @param fileName
     */
    void readAiports(std::string fileName);

    /**
     * @brief Reads and parses the Flights.csv file
     *
     * @param fileName
     */
    void readFlights(const std::string fileName);

    /**
     * @brief Reads and parses the Airlines.csv file
     *
     * @param fileName
     */
    void readAirlines(const std::string fileName);
    void loadNetwork(const std::string aiportsFileName, const std::string flightsFileName);

    /**
     * @brief 3.i Method that return the number of Airports in a Network (size of the Airports vector)
     *
     * @return
     */
    int getAirportsNum() const; //3.i

    /**
     * @brief 3.i Method that return the number of Flights in a Network (sum of sizes of each Airport Flights vector inside Airports)
     *
     * @return
     */
    int getFligthsNum() const;  //3.i

    /**
     * @brief 3.iii Method that returns the number of flights that are outgoing from a given city
     *
     * @param city
     * @param Country
     * @return number of flights that are outgoing from a given city
     */
    int getFligthsNumPerCity(const std::string& city, const std::string& Country) const;           //3.iii

    /**
     * @brief 3.iii Method that returns the number of flights that are outgoing from a given Airline
     *
     * @param airlinecode
     * @return number of flights that are outgoing from a given Airline
     */
    int getFligthsNumPerAirline(const std::string& airlinecode) const; //3.iii

    /**
     * @brief 3.iv Method that returns the number of Countries that can be reached from a given Airport,
     * using an unordered_set to count.
     *
     * @param AirportIATA
     * @return
     */
    int numberOfCountriesAnAirportFliesTo(const std::string& AirportIATA); //3.iv a)

    /**
     * @brief 3.iv Method that returns the number of Countries that can be reached from a given City,
     * using an unordered_set to count.
     *
     * @param City
     * @param Country
     * @return
     */
    int numberOfCountriesACityFliesTo(const std::string& City, const std::string& Country); //3.iv b)

    void dfsVisit(Airport* v,std::unordered_set<std::string> &airports, std::unordered_set<std::pair<std::string,std::string>, PairHash> &cities, std::unordered_set<std::string> &countries) const;
    void getDestNumFrom(std::string IATA, int &airports, int &cities, int &countries);//3.v

    void getDestNumFromAtDist(std::string IATA, int distance,int &airports, int &cities, int &countries); //3.vi

    int shortestPathNR(std::string start, std::string end);
    std::unordered_set<std::pair< std::string, std::string>, PairHash> findDiameter();//extra... n é pedido

    void getMaxStopsBetweenAirports(int & stops, std::vector <std::pair<Airport *, Airport *>> &airports);//3.vii
    int calculateStopsBFSAux(Airport* source, std::vector<std::pair<Airport*, Airport*>> &aux);

    std::vector<Airport*> findTopKAirports(int k); //3.viii
    std::unordered_set<Airport*> articulationAirports();//3.ix

    Airport* findAirport(std::string IATA);
    Airport* findAirportByName(std::string AirportName);
    std::vector<Airport*> findAirportsInCity(std::string CityName, std::string countryName);
    std::vector<Airport*> findClosestAirports(float latitude, float longitude);

    Airline findAirline(std::string code);

    //**4**
    std::vector<std::vector<Airport *>> shortestPathsAuxiliary(std::vector<Airport*> airportsStart, std::vector<Airport*> airportsEnd);

    std::vector<std::vector<Airport*>> shortestPathsIATA(const std::string& startIATA, const std::string& endIATA);//4.i airportsIAT
    std::vector<std::vector<Airport*>> shortestPathsIATAtoName(const std::string& startIATA, const std::string& airportNameEnd);
    std::vector<std::vector<Airport*>> shortestPathsIATAtoCity(const std::string& startIATA, const std::string& cityNameEnd, const std::string& countryEnd);
    std::vector<std::vector<Airport*>> shortestPathsIATAtoCoord(const std::string& startIATA, float latitudeEnd, float longitudeEnd);

    std::vector<std::vector<Airport*>> shortestPathsName(const std::string& airportNameStart, const std::string& airportNameEnd);//4.i airportsName
    std::vector<std::vector<Airport*>> shortestPathsNametoIATA(const std::string& airportNameStart, const std::string& endIATA);
    std::vector<std::vector<Airport*>> shortestPathsNametoCity(const std::string& airportNameStart, std::string CityNameEnd, std::string countryEnd);
    std::vector<std::vector<Airport*>> shortestPathsNametoCoord(const std::string& airportNameStart, float latitudeEnd, float longitudeEnd);



    std::vector<std::vector<Airport*>> shortestPathsCityToIATA(std::string CityNameStart, std::string countrystart, const std::string &endIATA);
    std::vector<std::vector<Airport*>> shortestPathsCityToName(std::string CityNameStart, std::string countrystart, const std::string& airportNameEnd);
    std::vector<std::vector<Airport*>> shortestPathsCitys(std::string CityNameStart, std::string countrystart, std::string CityNameEnd, std::string countryEnd);//4.ii city names
    std::vector<std::vector<Airport*>> shortestPathsCityToCoord(std::string CityNameStart, std::string countrystart, float latitudeEnd, float longitudeEnd);


    std::vector<std::vector<Airport*>> shortestPathsCoordinates(float latitudeStart, float longitudeStart, float latitudeEnd, float longitudeEnd);//4.iii
    std::vector<std::vector<Airport*>> shortestPathsCoordinateToIATA(float latitudeStart, float longitudeStart, const std::string& endIATA);
    std::vector<std::vector<Airport*>> shortestPathsCoordinateToName(float latitudeStart, float longitudeStart, const std::string& airportNameEnd);
    std::vector<std::vector<Airport*>> shortestPathsCoordinateToName(float latitudeStart, float longitudeStart, std::string CityNameEnd, std::string countryEnd);

    // 5

    Network filterByAirlines(std::vector<Airline> airlines);       /*  Parameters:
                                                                -set of chosen airlines
                                                    Returns new Network with flights filtered
                                                    by the chosen airlines.*/
    std::vector<std::vector<Flight>> minAirline(std::string startIATA, std::string destIATA); // return the flights in path
                                                                            //using the minimum amount of airlines
                                                                            //parameteres should be the output of fucntions in ex 4//
    void airlineDFS(Airport* start, Airport* current, Airport* dest, std::vector<std::vector<Flight>>& paths, std::vector<Flight>& currentPath);
 };





#endif //PROJETO_2_NETWORK_H
