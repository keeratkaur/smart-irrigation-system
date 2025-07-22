#pragma once
#include "Sensor.h"

class AirTempSensor : public Sensor {
    float value;
public:
    AirTempSensor();
    AirTempSensor(float initialValue);
    void update() override;
    float getValue() const override;
}; 