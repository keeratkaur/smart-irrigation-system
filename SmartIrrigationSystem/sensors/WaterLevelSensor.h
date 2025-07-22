#pragma once
#include "Sensor.h"

class WaterLevelSensor : public Sensor {
    float value;
    float decreaseRate;
    bool pumpOn;
public:
    WaterLevelSensor();
    WaterLevelSensor(float initialValue);
    void setPumpState(bool on);
    void update() override;
    float getValue() const override;
}; 