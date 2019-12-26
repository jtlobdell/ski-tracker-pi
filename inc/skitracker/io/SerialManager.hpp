#ifndef SKI_TRACKER_IO_SERIAL_MANAGER_HPP
#define SKI_TRACKER_IO_SERIAL_MANAGER_HPP

#include <functional>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

class SerialManager
{
public:
    SerialManager(boost::asio::io_context&);
    void setCallback(const std::function<void(const std::string&)>&);
    start();
    
private:
    void handle_serial_receive(const boost::system::error_code&, std::size_t);
    
    boost::asio::io_context& ioc;
    boost::asio::serial_port ser;
    boost::asio::streambuf data;
    std::function<void(const std::string&)> callback;
    
}; // class SerialManager

#endif
