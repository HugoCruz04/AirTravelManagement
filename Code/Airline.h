//
// Created by antero on 19-12-2023.
//

#ifndef INC_2NPROJAED_AIRLINE_H
#define INC_2NPROJAED_AIRLINE_H


#include <string>

class Airline {
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;
public:
    Airline(std::string code, std::string name, std::string callsign, std::string country);
    std::string getName();
    std::string getcode();
    std::string getCallsign();
    std::string getCountry();
};



#endif //INC_2NPROJAED_AIRLINE_H
