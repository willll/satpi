#include "NetTunnel.h"
#include "Logger.h"

#include <cstdlib>  // system()
#include <iostream>

NetTunnel::NetTunnel(const std::string& lanIf, const std::string& pppIf)
    : lanInterface(lanIf), pppInterface(pppIf) {}

void NetTunnel::setupNAT() {
    LOG_INFO("Setting up NAT between " + pppInterface + " and " + lanInterface);

    runCommand("sysctl -w net.ipv4.ip_forward=1", "Enable IP forwarding");

    runCommand("iptables -t nat -A POSTROUTING -o " + lanInterface + " -j MASQUERADE", "MASQUERADE setup");
    runCommand("iptables -A FORWARD -i " + pppInterface + " -j ACCEPT", "Forward in");
    runCommand("iptables -A FORWARD -o " + pppInterface + " -j ACCEPT", "Forward out");

    LOG_INFO("NAT setup complete.");
}

void NetTunnel::cleanupNAT() {
    LOG_INFO("Cleaning up iptables NAT rules...");

    runCommand("iptables -t nat -D POSTROUTING -o " + lanInterface + " -j MASQUERADE", "Remove MASQUERADE");
    runCommand("iptables -D FORWARD -i " + pppInterface + " -j ACCEPT", "Remove forward in");
    runCommand("iptables -D FORWARD -o " + pppInterface + " -j ACCEPT", "Remove forward out");

    LOG_INFO("NAT cleanup done.");
}

void NetTunnel::runCommand(const std::string& cmd, const std::string& context) {
    int code = system(cmd.c_str());
    if (code != 0) {
        LOG_ERROR("Command failed (" + context + "): " + cmd);
    } else {
        LOG_DEBUG("Command succeeded (" + context + "): " + cmd);
    }
}
