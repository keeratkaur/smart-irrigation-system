#pragma once
#include "Sensor.h"

class LightSensor : public Sensor {
    float value;
    bool isDay;
public:
    LightSensor();
    void setDay(bool day);
    void update() override;
    float getValue() const override;
}; 