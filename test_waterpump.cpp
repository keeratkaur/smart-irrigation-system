#include <cassert>
#include "SmartIrrigationSystem/actuators/WaterPump.h"

int main() {
    WaterPump pump;
    pump.turnOn();
    assert(pump.isRunning() == true);
    pump.turnOff();
    assert(pump.isRunning() == false);
    return 0;
} 