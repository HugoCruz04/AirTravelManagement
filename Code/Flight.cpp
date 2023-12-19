#include <utility>
#include "Flight.h"
#include "Network.h"
#include "Airport.h"

 using namespace std;

 Flight::Flight(std::string _source, std::string _target, std::string _airline):source(std::move(_source)),
                target(std::move(_target)),airline(std::move(_airline)){}

string Flight::getSource() const {return source;}
string Flight::getTarget() const {return target;}
string Flight::getAirline() const {return airline;}
Airport* Flight::getDest() const {return dest;}