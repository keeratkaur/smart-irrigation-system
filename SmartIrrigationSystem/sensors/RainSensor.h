#pragma once
#include "Sensor.h"

class RainSensor : public Sensor {
    bool raining;
public:
    RainSensor();
    RainSensor(bool raining);
    void update() override;
    float getValue() const override; // 1.0 for rain, 0.0 for no rain
    bool isRaining() const;
};
