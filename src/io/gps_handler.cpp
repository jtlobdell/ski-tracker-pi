#include <skitracker/io/gps_handler.hpp>
#include <skitracker/conf/config.hpp>
#include <cppnmea.hpp>
#include <iostream>
#include <string>
#include <string_view>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

namespace io {

gps_handler::gps_handler(boost::asio::io_context& ioc_, const conf::config& config_)
    : ioc(ioc_),
      config(config_),
      ser(ioc, config.get("gps.serialport"))
{
    // set callbacks for nmea parser
    p.setFailureCallback([](std::string_view sv) {
                             std::cerr << "failed to parse: " << sv << std::endl;
                         });
}

void gps_handler::start()
{
    boost::asio::async_read_until(ser, data, '\n',
                                  boost::bind(
                                      &gps_handler::handle_serial_receive, this,
                                      boost::asio::placeholders::error,
                                      boost::asio::placeholders::bytes_transferred
                                  ));
}

void gps_handler::handle_serial_receive(const boost::system::error_code&, std::size_t)
{
    // handle errors...
    std::string line(std::istreambuf_iterator<char>{&data}, std::istreambuf_iterator<char>());
    p.parse(line);
    start();
}

} // namespace io
