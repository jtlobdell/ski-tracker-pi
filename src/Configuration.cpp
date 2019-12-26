#include <skitracker/config/Configuration.hpp>
#include <skitracker/config/Defaults.hpp>

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <exception>

namespace pt = boost::property_tree;

namespace config {

namespace {
pt::ptree settings;
} // anonymous namespace

void init(const std::string& filename)
{
    pt::ini_parser::read_ini(filename, settings);
}

std::string get(const std::string& settingName)
{
    return settings.get(settingName, config::defaults::get(settingName));
}

} // namespace config
