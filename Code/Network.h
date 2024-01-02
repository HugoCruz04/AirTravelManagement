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

    /**
     * @brief Method that uses DFS to insert countries, airports and cities in the unordered_sets
     *
     * @param v
     * @param airports
     * @param cities
     * @param countries
     */
    void dfsVisit(Airport* v,std::unordered_set<std::string> &airports, std::unordered_set<std::pair<std::string,std::string>, PairHash> &cities, std::unordered_set<std::string> &countries) const;
    /**
     * @brief Method that takes an Airport code and three integers and returns the number os cities, countries and airports in those integers using dfsVisit()
     *
     * @param IATA
     * @param airports
     * @param cities
     * @param countries
     */
    void getDestNumFrom(std::string IATA, int &airports, int &cities, int &countries);//3.v

    /**
     * @brief Method that takes an Airport code and three integers and returns the number os cities, countries and airports in those integers using a BFS
     *
     * @param IATA
     * @param distance
     * @param airports
     * @param cities
     * @param countries
     */
    void getDestNumFromAtDist(std::string IATA, int distance,int &airports, int &cities, int &countries); //3.vi

    /**
     * @brief Method that returns the max number of stops in the integer input and the pairs <Airport,Airport> that represent the source and destination in the input vector taking advantage of a BFS methos calculateStopsBFSAux()
     *
     * @param stops
     * @param airports
     */
    void getMaxStopsBetweenAirports(int & stops, std::vector <std::pair<Airport *, Airport *>> &airports);//3.vii

    /**
     * @brief Method that return the max number of stops possible using a BFS
     *
     * @param source
     * @param aux
     * @return
     */
    int calculateStopsBFSAux(Airport* source, std::vector<std::pair<Airport*, Airport*>> &aux);

    /**
     * @brief Method that sorts all Airports by their traffic(incoming and accounting edges) and returns a vector with all Airports to index k
     *
     * @param k
     * @return
     */
    std::vector<Airport*> findTopKAirports(int k); //3.viii

    /**
     * @brief Method that returns a unordered_set with all the essential Airports using a dfs auxiliary method. Note that this function makes the Network undirected
     *
     * @return
     */
    std::unordered_set<Airport*> articulationAirports();//3.ix

    /**
     * @brief Method that searches for the airport which has the given code
     * @details Complexity: O(Log(n))
     * @param IATA
     * @return
     */
    Airport* findAirport(std::string IATA);

    /**
     * @brief Method that searches for the airport which has the given name
     * @details Complexity: O(n)
     * @param AirportName
     * @return
     */
    Airport* findAirportByName(std::string AirportName);

    /**
     * @brief Method that searches for the airports which have the given city name and country name
     * @details Complexity: O(n)
     * @param CityName
     * @param countryName
     * @return
     */
    std::vector<Airport*> findAirportsInCity(std::string CityName, std::string countryName);

    /**
     * @brief Method that searches for the closest Airport/s from a givem coordinate using the Haversine formula
     * @details Complexity: O(n)
     * @param latitude
     * @param longitude
     * @return
     */
    std::vector<Airport*> findClosestAirports(float latitude, float longitude);


    //**4**
    /**
     * @brief method that takes two vectors of airports and combine the airports to get the shortest paths between all of them using
     * the shortestPaths4() that uses a dijkstra's algorithm
     * @param airportsStart
     * @param airportsEnd
     * @return
     */
    std::vector<std::vector<Airport *>> shortestPathsAuxiliary(std::vector<Airport*> airportsStart, std::vector<Airport*> airportsEnd);

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


/**
 * \mainpage  Air Travel Management Documentation
 *
 * \section intro_sec Introduction
 * Welcome to the documentation for our project developed for the curricular unit AED 23/24.
 * This project was created by Antero Morgado(up202204971@fe.up.pt), Hugo Cruz(up202205022@fe.up.pt), and Tomás Telmo(up202206091@fe.up.pt).
 * We hope you find this documentation helpful and enjoy exploring the features of our project.
 *
 * \section features_sec Features
 * Our project includes a set of features designed to meet the requirements outlined in the project description.
 *
 * For detailed information, please refer to the specific sections and classes in the documentation.
 */