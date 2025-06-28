#ifndef MODEM_PPP_HANDLER_H
#define MODEM_PPP_HANDLER_H

#include <boost/asio.hpp>
#include <string>
#include <vector>

#include "Config.h"

class ModemPPPHandler {
public:
    ModemPPPHandler(boost::asio::io_context& io, const Config& config);

    bool openPort();
    void waitForDialInAndLaunchPPPD();

private:
    boost::asio::serial_port serial;
    std::string portName;
    int baudRate;
    std::vector<std::string> pppdOptions;

    std::string readLine();
    void sendCommand(const std::string& cmd);
    void launchPPPD();
};

#endif // MODEM_PPP_HANDLER_H
