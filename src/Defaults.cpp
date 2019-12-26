#include <skitracker/config/Defaults.hpp>
#include <string>
#include <map>

namespace config::defaults {

namespace {
std::map<std::string, std::string> settings =
{
    {"gps.serialport", "/dev/ttyS0"}
}; // std::map settings
} // anonymous namespace

const std::string& get(const std::string& settingName)
{
    try {
        return settings.at(settingName);
    } catch (std::out_of_range&) {
        throw std::runtime_error("Default setting not found: " + settingName);
    }
}

} // namespace config::defaults
