#include "WaterPump.h"

WaterPump::WaterPump() : isOn(false) {}

WaterPump::WaterPump(bool isOn) : isOn(isOn) {}

void WaterPump::turnOn() {
    isOn = true;
}

void WaterPump::turnOff() {
    isOn = false;
}

bool WaterPump::isRunning() const {
    return isOn;
}
