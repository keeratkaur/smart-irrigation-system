#pragma once
#include "../sensors/SoilMoistureSensor.h"
#include "../sensors/RainSensor.h"
#include "../sensors/WaterLevelSensor.h"
#include "../actuators/WaterPump.h"
#include "../utils/Logger.h"
#include <iostream>
#include <chrono>
#include <thread>

class IrrigationController {
    SoilMoistureSensor soilSensor;
    RainSensor rainSensor;
    WaterLevelSensor waterLevelSensor;
    WaterPump pump;
    bool realTimeMode;
    int delayMs;
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
};
