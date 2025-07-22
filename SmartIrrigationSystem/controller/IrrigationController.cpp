#include "IrrigationController.h"

IrrigationController::IrrigationController() : realTimeMode(false), delayMs(1000) {
    // Initial state is fine; sensors and pump default constructors
}

IrrigationController::IrrigationController(SoilMoistureSensor& sm, RainSensor& rain, WaterLevelSensor& wl, WaterPump& pump) 
    : extSoilSensor(&sm), extRainSensor(&rain), extWaterLevelSensor(&wl), extPump(&pump), realTimeMode(false), delayMs(1000) {}

void IrrigationController::setRealTimeMode(bool enabled, int delayMs) {
    this->realTimeMode = enabled;
    this->delayMs = delayMs;
    if (enabled) {
        Logger::info("Real-time mode enabled with " + std::to_string(delayMs) + "ms delay");
    } else {
        Logger::info("Real-time mode disabled");
    }
}

void IrrigationController::tick() {
    // Use external sensors/pump if provided, else use internal
    SoilMoistureSensor& soil = extSoilSensor ? *extSoilSensor : soilSensor;
    RainSensor& rain = extRainSensor ? *extRainSensor : rainSensor;
    WaterLevelSensor& waterLevel = extWaterLevelSensor ? *extWaterLevelSensor : waterLevelSensor;
    WaterPump& pumpRef = extPump ? *extPump : pump;

    // Update sensors
    soil.setPumpState(pumpRef.isRunning());
    waterLevel.setPumpState(pumpRef.isRunning());
    soil.update();
    rain.update();
    waterLevel.update();

    float soilVal = soil.getValue();
    bool raining = rain.isRaining();
    float waterLevelVal = waterLevel.getValue();

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

    // Log state with color coding
    Logger::sensor("Soil: " + std::to_string(soilVal).substr(0, 5) + "% | " +
                   "Rain: " + (raining ? "Yes" : "No") + " | " +
                   "Water: " + std::to_string(waterLevelVal).substr(0, 5) + "% | " +
                   "Pump: " + (pumpRef.isRunning() ? "ON" : "OFF"));
}

void IrrigationController::setupNormalScenario() {
    // Reset to normal conditions
    soilSensor = SoilMoistureSensor(50.0f);  // 50% moisture
    rainSensor = RainSensor(false);           // No rain
    waterLevelSensor = WaterLevelSensor(80.0f); // 80% water level
    pump = WaterPump(false);                 // Pump off
    Logger::success("Normal scenario setup complete - Moderate conditions");
}

void IrrigationController::setupDroughtScenario() {
    // Setup drought conditions
    soilSensor = SoilMoistureSensor(20.0f);  // Very dry soil
    rainSensor = RainSensor(false);           // No rain
    waterLevelSensor = WaterLevelSensor(60.0f); // Moderate water level
    pump = WaterPump(false);                 // Pump off initially
    Logger::warning("Drought scenario setup complete - Very dry conditions");
}

void IrrigationController::setupRainyScenario() {
    // Setup rainy conditions
    soilSensor = SoilMoistureSensor(60.0f);  // Moderate moisture
    rainSensor = RainSensor(true);            // Raining
    waterLevelSensor = WaterLevelSensor(90.0f); // High water level
    pump = WaterPump(false);                 // Pump off (should stay off due to rain)
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
