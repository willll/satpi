#pragma once 

#include <string>

class NetTunnel {
public:
    NetTunnel(const std::string& lanIf = "eth0", const std::string& pppIf = "ppp0");

    void setupNAT();
    void cleanupNAT();

private:
    std::string lanInterface;
    std::string pppInterface;

    void runCommand(const std::string& cmd, const std::string& context);
};

