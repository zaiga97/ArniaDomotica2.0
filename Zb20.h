#pragma once

#include <OneWire.h>
#include <DallasTemperature.h>

class Zb20{
  float lastTemperature = -120; 
  OneWire oneWire{}; 
  DallasTemperature sensors{};

  public:

  Zb20(int pin){
    oneWire.begin(pin);
    sensors.setOneWire(&oneWire);
  }

  float getTemperature(){
    int i = 0;
    float newTemperature = -120;
    while(i < 5){
      sensors.requestTemperatures();
      newTemperature = sensors.getTempCByIndex(0);
      if (newTemperature > -100){
        lastTemperature = newTemperature;
        return lastTemperature; 
      }
      i++;
      delay(10);
    } 
    return lastTemperature;
  }
};