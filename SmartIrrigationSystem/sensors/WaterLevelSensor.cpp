#include "WaterLevelSensor.h"
#include <random>

WaterLevelSensor::WaterLevelSensor() : value(100.0f), decreaseRate(1.0f), pumpOn(false) {}

WaterLevelSensor::WaterLevelSensor(float initialValue) : value(initialValue), decreaseRate(1.0f), pumpOn(false) {}

void WaterLevelSensor::setPumpState(bool on) {
    pumpOn = on;
}

void WaterLevelSensor::update() {
    static std::default_random_engine eng(std::random_device{}());
    static std::uniform_real_distribution<float> noise(-0.2f, 0.2f);
    if (pumpOn) {
        value -= decreaseRate + noise(eng);
    }
    if (value > 100.0f) value = 100.0f;
    if (value < 0.0f) value = 0.0f;
}

float WaterLevelSensor::getValue() const {
    return value;
} 