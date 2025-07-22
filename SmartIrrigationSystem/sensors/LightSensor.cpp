#include "LightSensor.h"
#include <random>

LightSensor::LightSensor() : value(80.0f), isDay(true) {}

void LightSensor::setDay(bool day) {
    isDay = day;
}

void LightSensor::update() {
    static std::default_random_engine eng(std::random_device{}());
    static std::uniform_real_distribution<float> noise(-5.0f, 5.0f);
    if (isDay) {
        value = 80.0f + noise(eng);
    } else {
        value = 10.0f + noise(eng);
    }
    if (value > 100.0f) value = 100.0f;
    if (value < 0.0f) value = 0.0f;
}

float LightSensor::getValue() const {
    return value;
} 