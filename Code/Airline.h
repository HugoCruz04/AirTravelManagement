// Airline.h

#ifndef INC_2NPROJAED_AIRLINE_H
#define INC_2NPROJAED_AIRLINE_H

#include <string>

/**
 * @brief The Airline class represents an airline entity with code, name, callsign, and country.
 */
class Airline {
private:
    std::string code;       /**< Airline code. */
    std::string name;       /**< Airline name. */
    std::string callsign;   /**< Callsign associated with the airline. */
    std::string country;    /**< Country where the airline is based. */

public:
    /**
     * @brief Constructor for the Airline class.
     * @param code Airline code.
     * @param name Airline name.
     * @param callsign Callsign associated with the airline.
     * @param country Country where the airline is based.
     */
    Airline(std::string code, std::string name, std::string callsign, std::string country);
    Airline(std::string code);

    /**
     * @brief Getter for the airline name.
     * @return The airline name.
     */
    std::string getName();

    /**
     * @brief Getter for the airline code.
     * @return The airline code.
     */
    std::string getcode();

    /**
     * @brief Getter for the callsign associated with the airline.
     * @return The callsign.
     */
    std::string getCallsign();

    /**
     * @brief Getter for the country where the airline is based.
     * @return The country.
     */
    std::string getCountry();
};

#endif //INC_2NPROJAED_AIRLINE_H
