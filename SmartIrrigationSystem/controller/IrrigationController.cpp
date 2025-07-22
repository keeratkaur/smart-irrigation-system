#include "IrrigationController.h"

IrrigationController::IrrigationController() : realTimeMode(false), delayMs(1000), hour(8), minute(0), tickStep(30) {
    // Initial state is fine; sensors and pump default constructors
}

IrrigationController::IrrigationController(SoilMoistureSensor& sm, RainSensor& rain, WaterLevelSensor& wl, WaterPump& pump) 
    : extSoilSensor(&sm), extRainSensor(&rain), extWaterLevelSensor(&wl), extPump(&pump), realTimeMode(false), delayMs(1000), hour(8), minute(0), tickStep(30) {}

void IrrigationController::setRealTimeMode(bool enabled, int delayMs) {
    this->realTimeMode = enabled;
    this->delayMs = delayMs;
    if (enabled) {
        Logger::info("Real-time mode enabled with " + std::to_string(delayMs) + "ms delay");
    } else {
        Logger::info("Real-time mode disabled");
    }
}

void IrrigationController::advanceTime() {
    minute += tickStep;
    if (minute >= 60) {
        hour += minute / 60;
        minute = minute % 60;
    }
    if (hour >= 24) hour = hour % 24;
}

std::string IrrigationController::getTimeString() const {
    std::ostringstream oss;
    oss << "[" << std::setw(2) << std::setfill('0') << hour << ":"
        << std::setw(2) << std::setfill('0') << minute << "]";
    return oss.str();
}

void IrrigationController::tick() {
    // Use external sensors/pump if provided, else use internal
    SoilMoistureSensor& soil = extSoilSensor ? *extSoilSensor : soilSensor;
    RainSensor& rain = extRainSensor ? *extRainSensor : rainSensor;
    WaterLevelSensor& waterLevel = extWaterLevelSensor ? *extWaterLevelSensor : waterLevelSensor;
    WaterPump& pumpRef = extPump ? *extPump : pump;
    AirTempSensor& airTemp = airTempSensor;
    LightSensor& light = lightSensor;

    // Update sensors
    soil.setPumpState(pumpRef.isRunning());
    waterLevel.setPumpState(pumpRef.isRunning());
    soil.update();
    rain.update();
    waterLevel.update();
    airTemp.update();
    light.update();

    float soilVal = soil.getValue();
    bool raining = rain.isRaining();
    float waterLevelVal = waterLevel.getValue();
    float airTempVal = airTemp.getValue();
    float lightVal = light.getValue();

    // Irrigation logic
    if (soilVal < 40.0f && !raining && waterLevelVal > 10.0f) {
        if (!pumpRef.isRunning()) {
            pumpRef.turnOn();
            Logger::pump("Pump turned ON - Soil dry, no rain, water available");
        }
    } else if (soilVal >= 70.0f || raining || waterLevelVal <= 10.0f) {
        if (pumpRef.isRunning()) {
            pumpRef.turnOff();
            std::string reason = soilVal >= 70.0f ? "Soil saturated" : 
                               raining ? "Raining" : "Low water level";
            Logger::pump("Pump turned OFF - " + reason);
        }
    }

    // Log state in requested format
    std::ostringstream oss;
    oss << getTimeString() << " SoilMoisture: " << int(soilVal) << "% | "
        << "AirTemp: " << int(airTempVal) << " C | "
        << "Rain: " << (raining ? "Yes" : "No") << " | "
        << "Light: " << int(lightVal) << "lx | "
        << "WaterLevel: " << int(waterLevelVal) << "% | "
        << "Pump: " << (pumpRef.isRunning() ? "ON" : "OFF");
    Logger::sensor(oss.str());

    advanceTime();
}

void IrrigationController::setupNormalScenario() {
    // Reset to normal conditions
    soilSensor = SoilMoistureSensor(50.0f);  // 50% moisture
    rainSensor = RainSensor(false);           // No rain
    waterLevelSensor = WaterLevelSensor(80.0f); // 80% water level
    airTempSensor = AirTempSensor(24.0f);     // 24°C
    lightSensor = LightSensor(800.0f);        // 800lx
    pump = WaterPump(false);                 // Pump off
    hour = 8; minute = 0;
    Logger::success("Normal scenario setup complete - Moderate conditions");
}

void IrrigationController::setupDroughtScenario() {
    // Setup drought conditions
    soilSensor = SoilMoistureSensor(20.0f);  // Very dry soil
    rainSensor = RainSensor(false);           // No rain
    waterLevelSensor = WaterLevelSensor(60.0f); // Moderate water level
    airTempSensor = AirTempSensor(32.0f);     // Hot
    lightSensor = LightSensor(1000.0f);       // Bright
    pump = WaterPump(false);                 // Pump off initially
    hour = 8; minute = 0;
    Logger::warning("Drought scenario setup complete - Very dry conditions");
}

void IrrigationController::setupRainyScenario() {
    // Setup rainy conditions
    soilSensor = SoilMoistureSensor(60.0f);  // Moderate moisture
    rainSensor = RainSensor(true);            // Raining
    waterLevelSensor = WaterLevelSensor(90.0f); // High water level
    airTempSensor = AirTempSensor(18.0f);     // Cool
    lightSensor = LightSensor(300.0f);        // Dim
    pump = WaterPump(false);                 // Pump off (should stay off due to rain)
    hour = 8; minute = 0;
    Logger::info("Rainy scenario setup complete - Wet conditions");
}

void IrrigationController::simulateScenario(int steps) {
    Logger::system("Starting simulation for " + std::to_string(steps) + " ticks...");
    for (int i = 0; i < steps; ++i) {
        Logger::info("Tick " + std::to_string(i+1) + ": ");
        tick();
        // Add real-time delay if enabled
        if (realTimeMode) {
            std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
        }
    }
    Logger::success("Simulation complete!");
}
