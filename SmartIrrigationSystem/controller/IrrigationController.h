#pragma once
#include "../sensors/SoilMoistureSensor.h"
#include "../sensors/RainSensor.h"
#include "../sensors/WaterLevelSensor.h"
#include "../sensors/AirTempSensor.h"
#include "../sensors/LightSensor.h"
#include "../actuators/WaterPump.h"
#include "../utils/Logger.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>

class IrrigationController {
    SoilMoistureSensor soilSensor;
    RainSensor rainSensor;
    WaterLevelSensor waterLevelSensor;
    AirTempSensor airTempSensor;
    LightSensor lightSensor;
    WaterPump pump;
    bool realTimeMode;
    int delayMs;
    int hour, minute, tickStep;
public:
    IrrigationController();
    // Dependency injection constructor for testing
    IrrigationController(SoilMoistureSensor& sm, RainSensor& rain, WaterLevelSensor& wl, WaterPump& pump);
    void tick();
    // Simulation functions
    void setupNormalScenario();
    void setupDroughtScenario();
    void setupRainyScenario();
    void simulateScenario(int steps);
    void setRealTimeMode(bool enabled, int delayMs = 1000);
private:
    SoilMoistureSensor* extSoilSensor = nullptr;
    RainSensor* extRainSensor = nullptr;
    WaterLevelSensor* extWaterLevelSensor = nullptr;
    WaterPump* extPump = nullptr;
    void advanceTime();
    std::string getTimeString() const;
};
