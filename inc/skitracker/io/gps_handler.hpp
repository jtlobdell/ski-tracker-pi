#ifndef SKI_TRACKER_GPS_HANDLER_HPP
#define SKI_TRACKER_GPS_HANDLER_HPP

#include <string>
#include <skitracker/conf/config.hpp>
#include <cppnmea.hpp>
#include <string>
#include <boost/asio.hpp>

namespace io {

class gps_handler
{
public:
    gps_handler(boost::asio::io_context&, const conf::config&);
    void start();

private:
    void handle_serial_receive(const boost::system::error_code&, std::size_t);

    boost::asio::io_context& ioc;
    const conf::config& config;
    boost::asio::serial_port ser;
    boost::asio::streambuf data;
    nmea::Parser p;
    
}; // class gps_handler

} // namespace io

#endif
