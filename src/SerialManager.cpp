#include <skitracker/io/SerialManager.hpp>

SerialManager::SerialManager(boost::asio::io_context& io_context, std::string port)
    : ioc(io_context),
      ser(ioc, port),
      callback([](std::string_view){ })
{}

void SerialManager::setCallback(std::function<void(const std::string&)> func)
{
    callback = func;
}

void SerialManager::start()
{
    boost::asio::async_read_until(ser, data, '\n',
                                  boost::bind(
                                      &SerialManager::handle_serial_receive, this,
                                      boost::asio::placeholders::error,
                                      boost::asio::placeholders::bytes_transferred
                                  ));
}

void SerialManager::handle_serial_receive(const boost::system::error_code&, std::size_t bytes_transferred)
{
    std::string line(std::istreambuf_iterator<char>{&data}, std::istreambuf_iterator<char>());
    callback(line);
    //p.parse(line);
    start();
}
