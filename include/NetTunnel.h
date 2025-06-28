#ifndef NET_TUNNEL_H
#define NET_TUNNEL_H

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

#endif // NET_TUNNEL_H
