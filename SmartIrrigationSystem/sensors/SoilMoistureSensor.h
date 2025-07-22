#pragma once
#include "Sensor.h"

class SoilMoistureSensor : public Sensor {
    float value;
    float dryRate;
    float wetRate;
    bool pumpOn;
public:
    SoilMoistureSensor();
    SoilMoistureSensor(float initialValue);
    void setPumpState(bool on);
    void update() override;
    float getValue() const override;
};
