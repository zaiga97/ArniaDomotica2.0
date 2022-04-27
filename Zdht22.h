#pragma once
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>  

class Zdht22{
  DHT_Unified dht{DHT_PIN, DHT22};
  sensors_event_t event;
  const int MAXTRIES = 5;
  const int ERROR = -100;

  public:
  
  Zdht22(){
    dht.begin();
  }

  float getTemperature(){
    int Ntries = 0;
    while (Ntries < MAXTRIES){
      dht.temperature().getEvent(&event);
      if (!isnan(event.temperature)) return event.temperature;
      delay(10);
    }
    return ERROR;
  }

  float getHumidity(){
    int Ntries = 0;
    while (Ntries < MAXTRIES){
      dht.humidity().getEvent(&event);
      if (!isnan(event.temperature)) return event.relative_humidity;
      delay(10);
    }
    return ERROR;
  }
};