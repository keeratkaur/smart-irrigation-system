#include "SoilMoistureSensor.h"
#include <random>

SoilMoistureSensor::SoilMoistureSensor() : value(50.0f), dryRate(0.5f), wetRate(2.0f), pumpOn(false) {}

SoilMoistureSensor::SoilMoistureSensor(float initialValue) : value(initialValue), dryRate(0.5f), wetRate(2.0f), pumpOn(false) {}

void SoilMoistureSensor::setPumpState(bool on) {
    pumpOn = on;
}

void SoilMoistureSensor::update() {
    static std::default_random_engine eng(std::random_device{}());
    static std::uniform_real_distribution<float> noise(-0.2f, 0.2f);
    if (pumpOn) {
        value += wetRate + noise(eng);
    } else {
        value -= dryRate + noise(eng);
    }
    if (value > 100.0f) value = 100.0f;
    if (value < 0.0f) value = 0.0f;
}

float SoilMoistureSensor::getValue() const {
    return value;
}
