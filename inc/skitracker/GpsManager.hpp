#include <string>
#include <skitracker/io/SerialManager.hpp>
#include <cppnmea.hpp>

class GpsManager
{
public:
    GpsManager();

private:
    void parse(const std::string&);
    
    SerialManager ser;
    nmea::parser p;

}; // class GpsManager
