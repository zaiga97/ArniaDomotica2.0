#pragma once

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

class Zwifi{
  public:

  const char* ssid = "NETGEAR60";
  const char* password = "exoticcartoon025";

  unsigned long startConnectionTime;
  const int maxTimeToConnectWifi = 60 * 1000;

  bool connect() {
    startConnectionTime = millis();
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED && (millis()-startConnectionTime) < maxTimeToConnectWifi) delay(500);
    return (WiFi.status()==WL_CONNECTED) ? true : false;
  }

  void setup(){
    WiFi.mode(WIFI_STA);
    wifi_set_sleep_type(NONE_SLEEP_T);
  }

  void sleep(int sleepTime){
    WiFi.disconnect();
    WiFi.forceSleepBegin();
    delay(sleepTime + 1);
    WiFi.forceSleepWake();
  }
};