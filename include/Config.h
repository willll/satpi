#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>

struct Config {
    
    std::string modem_port = "/dev/ttyUSB0";
    int baud_rate = 115200;
    std::vector<std::string> pppd_options;
    std::string lan_interface = "wlan0";
    std::string ppp_interface = "ppp0";

    Config(const std::string& filename = "config.json");
    static Config load(const std::string& path);
private:
    void setDefaults();
};

#endif // CONFIG_H
