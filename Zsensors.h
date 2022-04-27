#pragma once
#include "Zdht22.h"
#include "Zb20.h"
#include "Zrecord.h"
#include "Zntp.h"
#include "Zscale.h"

class Zsensors{
  Zdht22 zdht22{};
  Zb20 zb20_4{B20_PIN_4};
  Zb20 zb20_5{B20_PIN_5};
  Zscale zscale_4{DT_4, SCK_4, calibration_factor_4, offset_4};
  Zscale zscale_5{DT_5, SCK_5, calibration_factor_5, offset_5};
  Zntp zntp{};

  Record lastDataRecord;

  public: 
  
  void updateMeasures(){
    lastDataRecord = {
      zntp.getTimeStamp(),
      zdht22.getTemperature(),
      zdht22.getHumidity(),
      zb20_4.getTemperature(),
      zb20_5.getTemperature(),
      zscale_4.getWeight(),
      zscale_5.getWeight()
    };
  }

  Record getMeasuresRecord(){
    return lastDataRecord;
  }
};