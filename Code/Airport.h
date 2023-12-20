#include <string>
#include <vector>

#ifndef PROJETO_2_AIRPORT_H
#define PROJETO_2_AIRPORT_H


class Flight;

class Airport{
private:
    std::string IATA;
    std::string name;
    std::string city;
    std::string country;
    float latitude;
    float longitude;

    std::vector<Flight> flights; //list of flights departing from an airport


public:
    Airport(std::string IATA, std::string name, std::string city, std::string country, float latitude, float longitude);
    std::string getIATA() const;
    std::string getName() const;
    std::string getCity() const;
    std::string getCountry() const;
    float getLatitude() const;
    float getLongitude() const;
    const std::vector<Flight> &getFlights() const;
    int getFlightsNum() const;  //3.ii(tambem é usada na 3.i)
    int getAirlinesNum() const; //3.ii
    void addFlight(const Flight flight);
};
#endif //PROJETO_2_AIRPORT_H
