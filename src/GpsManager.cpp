#include <skitracker/GpsManager.hpp>
#include <skitracker/io/SerialManager.hpp>
#include <cppnmea.hpp>

GpsManager::GpsManager()
{
    ser.setCallback(parse);
}

GpsManager::start()
{
    ser.start();
}

void GpsManager::parse(const std::string& line)
{
    p.parse(line);
}
