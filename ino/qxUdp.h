#ifndef __QX_UDP__
#define __QX_UDP__

#include <Arduino.h>
#include <AsyncUDP.h>

typedef void (*PacketEventCallbackPtr)(AsyncUDPPacket);
void qxUdpServerInit(PacketEventCallbackPtr PacketEventCallback,int port);

#endif