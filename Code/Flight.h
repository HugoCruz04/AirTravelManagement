#include <string>
#include "Airport.h"

#ifndef PROJETO_2_FLIGHT_H
#define PROJETO_2_FLIGHT_H

/**
 * @brief The Flight class represents a flight(Edge) between two airports.
 */
class Flight {
private:
    std::string source; /**< The IATA code of the source airport. */
    std::string target; /**< The IATA code of the target airport. */
    std::string airline; /**< The ICAO code of the airline operating the flight. */
    Airport* dest; /**< A pointer to the destination airport object. */

public:
    /**
     * @brief Constructor for the Flight class.
     * @param source The IATA code of the source airport.
     * @param target The IATA code of the target airport.
     * @param airline The ICAO code of the airline operating the flight.
     * @param dest A pointer to the destination airport object.
     */
    Flight(std::string source, std::string target, std::string airline, Airport* dest);

    /**
     * @brief Gets the IATA code of the source airport.
     * @return The IATA code of the source airport.
     */
    std::string getSource() const;

    /**
     * @brief Gets the IATA code of the target airport.
     * @return The IATA code of the target airport.
     */
    std::string getTarget() const;

    /**
     * @brief Gets the ICAO code of the airline operating the flight.
     * @return The ICAO code of the airline.
     */
    std::string getAirline() const;

    /**
     * @brief Gets a pointer to the destination airport object.
     * @return A pointer to the destination airport.
     */
    Airport* getDest() const;
};

#endif // PROJETO_2_FLIGHT_H
