#include <skitracker/conf/defaults.hpp>
#include <string>
#include <map>

namespace conf::defaults {

namespace {

const std::map<std::string, std::string> settings =
{
    {"gps.serialport", "/dev/ttyS0"}
}; // std::map settings
} // anonymous namespace

const std::string& get(const std::string& setting)
{
    try {
        return settings.at(setting);
    } catch (std::out_of_range&) {
        throw std::runtime_error("Default setting not found: " + setting);
    }
}

} // namespace conf::defaults
