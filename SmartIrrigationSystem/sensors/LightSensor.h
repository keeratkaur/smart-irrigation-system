#pragma once
#include "Sensor.h"

class LightSensor : public Sensor {
    float value;
    bool isDay;
public:
    LightSensor();
    LightSensor(float initialValue);
    void setDay(bool day);
    void update() override;
    float getValue() const override;
}; 