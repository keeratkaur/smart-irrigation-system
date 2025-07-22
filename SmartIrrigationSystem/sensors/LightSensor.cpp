#include "LightSensor.h"
#include <random>

LightSensor::LightSensor() : value(800.0f), isDay(true) {}
LightSensor::LightSensor(float initialValue) : value(initialValue), isDay(true) {}

void LightSensor::setDay(bool day) {
    isDay = day;
}

void LightSensor::update() {
    static std::default_random_engine eng(std::random_device{}());
    static std::uniform_real_distribution<float> noise(-50.0f, 50.0f);
    if (isDay) {
        value = 800.0f + noise(eng); // Simulate daylight
    } else {
        value = 50.0f + noise(eng);  // Simulate night
    }
    if (value < 0.0f) value = 0.0f;
}

float LightSensor::getValue() const {
    return value;
} 