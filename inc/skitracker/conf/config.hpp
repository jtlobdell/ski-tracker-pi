#ifndef SKI_TRACKER_CONF_HPP
#define SKI_TRACKER_CONF_HPP

#include <string>
#include <boost/property_tree/ptree.hpp>

namespace conf {
class config {

public:
    // Read configuration from file
    config(const std::string&);

    // Read setting from config
    std::string get(const std::string&) const;

private:
    boost::property_tree::ptree settings;
    
}; // class config
} // namespace conf

#endif
