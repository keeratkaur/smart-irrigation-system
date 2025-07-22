#include "AirTempSensor.h"
#include <random>

AirTempSensor::AirTempSensor() : value(24.0f) {}
AirTempSensor::AirTempSensor(float initialValue) : value(initialValue) {}

void AirTempSensor::update() {
    static std::default_random_engine eng(std::random_device{}());
    static std::uniform_real_distribution<float> noise(-0.5f, 0.5f);
    value += noise(eng);
    if (value < 10.0f) value = 10.0f;
    if (value > 40.0f) value = 40.0f;
}

float AirTempSensor::getValue() const {
    return value;
} 