#include <iostream>
#include <string>
#include <string_view>
#include <cppnmea.hpp>

int main(int argc, char *argv[])
{
    nmea::Parser p;
    std::string s = "asdfasdfasdf";
    p.setFailureCallback(
        [](std::string_view sv) {
            std::cerr << "failed to parse: " << sv << std::endl;
        });
    p.parse(s);
    
    return 0;
}
