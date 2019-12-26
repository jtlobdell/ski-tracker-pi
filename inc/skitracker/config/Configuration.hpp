#ifndef SKI_TRACKER_CONFIG_HPP
#define SKI_TRACKER_CONFIG_HPP

#include <string>

namespace config
{

// Read configuration from file
void init(const std::string&);

// Read setting from config
std::string get(const std::string&);

} // namespace conf

#endif
