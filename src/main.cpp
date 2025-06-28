#include "Config.h"
#include "ModemPPPHandler.h"
#include "Logger.h"

int main() {
    Logger::init(true);

    Config config("config.json");

    boost::asio::io_context io;
    ModemPPPHandler modem(io, config);

    if (!modem.openPort()) return 1;

    modem.waitForDialInAndLaunchPPPD();

    return 0;
}
