#include "qxUdp.h"

AsyncUDP udp;

void qxUdpServerInit(PacketEventCallbackPtr PacketEventCallback,int port)
{
  if(udp.listen(port)){
    udp.onPacket(PacketEventCallback);
  }
}