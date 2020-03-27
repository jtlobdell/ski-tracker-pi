#include <skitracker/conf/config.hpp>
#include <skitracker/conf/defaults.hpp>

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <exception>

namespace pt = boost::property_tree;

namespace conf {

config::config(const std::string& filename)
{
    pt::ini_parser::read_ini(filename, settings);
}

std::string config::get(const std::string& setting) const
{
    return settings.get(setting, conf::defaults::get(setting));
}

} // namespace conf
