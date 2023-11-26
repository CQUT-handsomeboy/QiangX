#include "qxWifi.h"

void qxWifiInit(char *ssid,char *password) {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}