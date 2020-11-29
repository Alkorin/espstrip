#include "udp_server.h"

UdpLedServer::UdpLedServer(GenericStrip &s) : s(s)
{
}

bool UdpLedServer::handle()
{
    // Some pending packet to handle?
    int packetSize = udpServer.parsePacket();
    if (packetSize)
    {
        // Read it
        auto pBuffer = malloc(packetSize);
        if (pBuffer)
        {
            udpServer.read((unsigned char *)pBuffer, packetSize);
            // Write it to the strip
            memcpy(s.Pixels(), pBuffer, min(s.PixelsSize(), (size_t)packetSize));
            s.Dirty();
            s.Show();
        }

        // Restart backoff counter
        lastPacketTime = millis();
    }

    // If less than 500ms since last packet, we keep the handle
    if (millis() - lastPacketTime < 500)
    {
        return true;
    }

    return false;
}