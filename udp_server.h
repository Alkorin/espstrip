#pragma once

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "genericStrip.h"

class UdpLedServer
{
public:
    UdpLedServer(GenericStrip &s);

    void begin(unsigned int port)
    {
        udpServer.begin(port);
    }

    bool handle();

private:
    WiFiUDP udpServer;
    GenericStrip &s;
    unsigned long lastPacketTime;
};