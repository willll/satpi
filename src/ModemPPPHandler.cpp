#include "ModemPPPHandler.h"
#include "Logger.h"

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <thread>
#include <iostream>
#include <unistd.h>  // for fork, execlp

using namespace boost::asio;

ModemPPPHandler::ModemPPPHandler(boost::asio::io_context& io, const Config& config)
    : serial(io), portName(config.modem_port), baudRate(config.baud_rate), pppdOptions(config.pppd_options) {}

bool ModemPPPHandler::openPort() {
    boost::system::error_code ec;
    serial.open(portName, ec);
    if (ec) {
        Logger::error("Failed to open serial port: " + ec.message());
        return false;
    }

    serial.set_option(serial_port_base::baud_rate(115200));
    serial.set_option(serial_port_base::character_size(8));
    serial.set_option(serial_port_base::parity(serial_port_base::parity::none));
    serial.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));
    serial.set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));

    Logger::info("Serial port " + portName + " opened.");
    return true;
}

void ModemPPPHandler::waitForDialInAndLaunchPPPD() {
    Logger::info("Waiting for RING...");

    while (true) {
        std::string line = readLine();
        Logger::debug("Modem: " + line);

        if (line.find("RING") != std::string::npos) {
            Logger::info("Incoming call detected. Answering...");
            sendCommand("ATA\r");
            std::string response = readLine();

            if (response.find("CONNECT") != std::string::npos) {
                Logger::info("CONNECT received. Launching pppd...");
                launchPPPD();
                break;
            } else {
                Logger::warn("Modem did not respond with CONNECT.");
            }
        }
    }
}

std::string ModemPPPHandler::readLine() {
    char c;
    std::string result;
    while (true) {
        boost::asio::read(serial, boost::asio::buffer(&c, 1));
        if (c == '\n' || c == '\r') {
            if (!result.empty()) break;
            else continue;
        }
        result += c;
    }
    return result;
}

void ModemPPPHandler::sendCommand(const std::string& cmd) {
    boost::asio::write(serial, boost::asio::buffer(cmd.c_str(), cmd.size()));
}

void ModemPPPHandler::launchPPPD() {
    pid_t pid = fork();
    if (pid == 0) {
        std::vector<const char*> args = {
            "pppd", portName.c_str(), std::to_string(baudRate).c_str()
        };

        for (const auto& opt : pppdOptions) {
            args.push_back(opt.c_str());
        }
        args.push_back(nullptr); // end marker

        execvp("pppd", const_cast<char* const*>(args.data()));
        perror("Failed to exec pppd");
        exit(1);
    }
}
