#include "RainSensor.h"
#include <random>

RainSensor::RainSensor() : raining(false) {}
RainSensor::RainSensor(bool raining) : raining(raining) {}

void RainSensor::update() {
    static std::default_random_engine eng(std::random_device{}());
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    if (dist(eng) < 0.1f) { // 10% chance to toggle
        raining = !raining;
    }
}

float RainSensor::getValue() const {
    return raining ? 1.0f : 0.0f;
}

bool RainSensor::isRaining() const {
    return raining;
}
