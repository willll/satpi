#include "Config.h"
#include "ModemPPPHandler.h"
#include "NetTunnel.h"
#include "Logger.h"

int main(int argc, char* argv[]) {
    Logger::init(true);

    // Use first argument as config file, or default to "config.json"
    std::string configFile = (argc > 1) ? argv[1] : "config.json";
    Config config(configFile);

    boost::asio::io_context io;
    ModemPPPHandler modem(io, config);

    if (!modem.openPort()) return 1;

    modem.waitForDialInAndLaunchPPPD();

    NetTunnel tunnel("wlan0", "ppp0");
    tunnel.setupNAT();
    
    return 0;
}
