#include "Config.h"
#include "Logger.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <fstream>

Config::Config(const std::string& filename) {
    namespace pt = boost::property_tree;
    pt::ptree tree;
    std::ifstream file(filename);
    if (file.good()) {
        try {
            pt::read_json(filename, tree);

            this->modem_port = tree.get<std::string>("modem_port", "/dev/ttyUSB0");
            LOG_INFO("Config: modem_port = " + this->modem_port);

            this->baud_rate = tree.get<int>("baud_rate", 115200);
            LOG_INFO("Config: baud_rate = " + std::to_string(this->baud_rate));

            this->pppd_options.clear();
            for (const auto& item : tree.get_child("pppd_options")) {
                std::string opt = item.second.get_value<std::string>();
                this->pppd_options.push_back(opt);
                LOG_INFO("Config: pppd_option = " + opt);
            }

            this->lan_interface = tree.get<std::string>("lan_interface", "wlan0");
            LOG_INFO("Config: lan_interface = " + this->lan_interface);

            this->ppp_interface = tree.get<std::string>("ppp_interface", "ppp0");
            LOG_INFO("Config: ppp_interface = " + this->ppp_interface);

        } catch (const std::exception& e) {
            LOG_ERROR(std::string("Error parsing config.json: ") + e.what());
            setDefaults();
        }
    } else {
        LOG_ERROR("Warning: config.json not found, using default configuration.");
        setDefaults();
    }
}

void Config::setDefaults() {
    this->modem_port = "/dev/ttyUSB0";
    this->baud_rate = 115200;
    this->pppd_options = {
        "local",
        "noauth",
        "nodetach",
        "proxyarp",
        "debug"
    };
    this->lan_interface = "wlan0";
    this->ppp_interface = "ppp0";
}
