#include <skitracker/conf/config.hpp>
#include <skitracker/io/gps_handler.hpp>
#include <cppnmea.hpp>
#include <boost/asio.hpp>

/*
namespace {
boost::asio::serial_port *ser;
boost::asio::streambuf data;
nmea::Parser p;

std::map<nmea::direction_t, std::string> direction_to_string = {
    {nmea::direction_t::north, "north"},
    {nmea::direction_t::south, "south"},
    {nmea::direction_t::east, "east"},
    {nmea::direction_t::west, "west"}
};

std::map<nmea::fix_quality_t, std::string> fix_quality_to_string = {
    {nmea::fix_quality_t::invalid, "invalid fix"},
    {nmea::fix_quality_t::gps_fix, "gps fix"},
    {nmea::fix_quality_t::dgps_fix, "dgps fix"},
    {nmea::fix_quality_t::pps_fix, "pps fix"},
    {nmea::fix_quality_t::real_time_kinematic, "real time kinematic"},
    {nmea::fix_quality_t::float_rtk, "float real time kinematic"},
    {nmea::fix_quality_t::dead_reckoning, "dead reckoning"},
    {nmea::fix_quality_t::manual_input_mode, "manual input mode"},
    {nmea::fix_quality_t::simulation_mode, "simulation mode"}
};

void print_position_2d(const nmea::position_2d_t& pos2d)
{
    auto& lat = pos2d.latitude;
    auto& lon = pos2d.longitude;
            
    std::cout << "latitude: " << lat.degrees << " degrees, " << lat.minutes << " minutes, " <<
        direction_to_string[lat.dir] <<
        std::endl;

    std::cout << "longitude: " << lon.degrees << " degrees, " << lon.minutes << " minutes, " <<
        direction_to_string[lon.dir] <<
        std::endl;
}

void print_line()
{
    std::cout << "-------------------------------------------" << std::endl;
}

void print_time(const nmea::utc_time_t& time)
{
    std::cout << "time (utc): " <<
        time.hours << ":" << time.minutes << ":" << time.seconds <<
        std::endl;
}

template <typename T>
void print_optional(const boost::optional<T>& opt)
{
    if (opt == boost::none) {
        std::cout << "null";
    } else {
        std::cout << *opt;
    }    
}

void print_checksum(unsigned int checksum)
{
    std::cout << "checksum: " << checksum <<
        " (0x" << std::hex << checksum << ")" << std::dec <<
        std::endl;
}

void print_gpgga(const nmea::gpgga& gga)
{
    std::cout << "$GPGGA" << std::endl;
    
    std::cout << fix_quality_to_string[gga.fix_quality] << std::endl;
    print_time(gga.time);
    print_position_2d(gga.pos_2d);

    std::cout << "num sats tracked: " << gga.sats_tracked << std::endl;
    std::cout << "horizontal degree of precision: " << gga.hdop << std::endl;
    std::cout << "altitude (MSL): " << gga.msl_altitude << std::endl;
    std::cout << "geoid separation (M): " << gga.geoid_separation << std::endl;

    std::cout << "time since last dgps update: ";
    print_optional(gga.time_since_dgps_update);
    std::cout << std::endl;

    std::cout << "station id: ";
    print_optional(gga.dgps_station_id);
    std::cout << std::endl;

    print_checksum(gga.checksum);

    print_line();
}

} // anonymous namespace
*/

int main(int argc, char *argv[])
{
    conf::config config("config.ini");
    boost::asio::io_context ioc;
    io::gps_handler gps(ioc, config);
    //io::imu_handler imu = io::imu_handler(ioc, conf);

    gps.start();
    //imu.start();
    
    ioc.run();
    
    /*
    boost::asio::io_context ioc;
    ser = new boost::asio::serial_port(ioc, config::get("gps.serialport"));

    p.setCallback<nmea::gpgga>(&print_gpgga);
    
    p.setFailureCallback(
        [](std::string_view sv) {
            std::cerr << "failed to parse: " << sv << std::endl;
        });

    start_serial_receive();
    ioc.run();
    
    delete ser;
    */
    return 0;
}
