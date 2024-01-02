#include <string>
#include <vector>

#ifndef PROJETO_2_AIRPORT_H
#define PROJETO_2_AIRPORT_H

class Flight;

/**
 * @brief The Airport class represents an airport(Vertex) in the network.
 */
class Airport {
private:
    std::string IATA; /**< The International Air Transport Association (IATA) code of the airport. */
    std::string name; /**< The name of the airport. */
    std::string city; /**< The city where the airport is located. */
    std::string country; /**< The country where the airport is located. */
    float latitude; /**< The latitude coordinates of the airport. */
    float longitude; /**< The longitude coordinates of the airport. */

    bool visited; /**< An auxiliary field for traversal algorithms. */
    bool processing; /**< An auxiliary field for traversal algorithms. */

    int num; /**< An auxiliary field for traversal algorithms to store a unique number. */
    int low; /**< An auxiliary field for traversal algorithms to store a low number. */
    int indegree; /**< The indegree of the airport (number of incoming flights). */

    std::vector<Flight> flights; /**< A list of flights departing from the airport. */

public:
    /**
     * @brief Constructor for the Airport class.
     * @param IATA The IATA code of the airport.
     * @param name The name of the airport.
     * @param city The city where the airport is located.
     * @param country The country where the airport is located.
     * @param latitude The latitude coordinates of the airport.
     * @param longitude The longitude coordinates of the airport.
     */
    Airport(std::string IATA, std::string name, std::string city, std::string country, float latitude, float longitude);

    std::string getIATA() const;
    std::string getName() const;
    std::string getCity() const;
    std::string getCountry() const;
    float getLatitude() const;
    float getLongitude() const;
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool v);

    /**
     * @brief Gets the list of flights departing from the airport.
     * @return A reference to the vector of flights.
     */
    const std::vector<Flight>& getFlights() const;

    /**
     * @brief Gets the number of airlines operating at the airport.
     * @return The number of airlines.
     */
    int getAirlinesNum() const;

    /**
     * @brief Adds a flight to the list of flights departing from the airport.
     * @param flight The flight to be added.
     */
    void addFlight(const Flight flight);

    /**
     * @brief Increases the indegree of the airport (number of incoming flights).
     */
    void increaseIndegree();

    /**
     * @brief Gets the indegree of the airport.
     * @return The indegree of the airport.
     */
    int getIndegree();

    /**
     * @brief Gets the unique number assigned to the airport during traversal algorithms.
     * @return The unique number of the airport.
     */
    int getNum() const;

    /**
     * @brief Sets the unique number for the airport during traversal algorithms.
     * @param num The unique number to be set.
     */
    void setNum(int num);

    /**
     * @brief Gets the low number assigned to the airport during traversal algorithms.
     * @return The low number of the airport.
     */
    int getLow() const;

    /**
     * @brief Sets the low number for the airport during traversal algorithms.
     * @param low The low number to be set.
     */
    void setLow(int low);

    /**
     * @brief Gets the traffic of the airport (sum of incoming and outgoing flights).
     * @return The traffic of the airport.
     */
    int getTrafic();
};

#endif // PROJETO_2_AIRPORT_H
