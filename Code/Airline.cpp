//
// Created by antero on 19-12-2023.
//

#include "Airline.h"

Airline::Airline(std::string code, std::string name, std::string callsign, std::string country) {
    this->code=code;
    this->name=name;
    this->callsign=callsign;
    this->country=country;
}

std::string Airline::getName() {
    return name;
}

std::string Airline::getcode() {
    return code;
}

std::string Airline::getCallsign() {
    return callsign;
}

std::string Airline::getCountry() {
    return country;
}
