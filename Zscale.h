#pragma once

#include "HX711.h"

class Zscale{
  HX711 scale;
  public:

  Zscale(int DT_PIN, int SCK_PIN, float calibration_factor, float offset){
    scale.begin(DT_PIN, SCK_PIN);
    scale.set_scale(calibration_factor);
    scale.set_offset(offset);
  }

  float getWeight(){
    scale.power_up();
    delay(10);
    float weight = (scale.get_units(5));
    scale.power_down();
    return weight;
  }
};