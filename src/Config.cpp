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
            this->baud_rate = tree.get<int>("baud_rate", 115200);
            this->pppd_options.clear();
            for (const auto& item : tree.get_child("pppd_options")) {
                this->pppd_options.push_back(item.second.get_value<std::string>());
            }
        } catch (const std::exception& e) {
            Logger::error(std::string("Error parsing config.json: ") + e.what());
            setDefaults();
        }
    } else {
        Logger::error("Warning: config.json not found, using default configuration.");
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
}
