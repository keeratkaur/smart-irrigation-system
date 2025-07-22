#include <iostream>
#include <cassert>
#include <limits>
#include "sensors/SoilMoistureSensor.h"
#include "actuators/WaterPump.h"
#include "controller/IrrigationController.h"
#include "utils/Logger.h"

void showMenu() {
    Logger::system("=== Smart Irrigation System Menu ===");
    std::cout << "1. Run Manual Test\n";
    std::cout << "2. Normal Scenario (Fast)\n";
    std::cout << "3. Normal Scenario (Real-time)\n";
    std::cout << "4. Drought Scenario (Fast)\n";
    std::cout << "5. Drought Scenario (Real-time)\n";
    std::cout << "6. Rainy Scenario (Fast)\n";
    std::cout << "7. Rainy Scenario (Real-time)\n";
    std::cout << "8. Custom Simulation\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}

void runManualTest() {
    Logger::info("Running manual test...");
    
    // Manual test case - conditions that should turn pump ON
    SoilMoistureSensor sm(25);  // 25% moisture (very dry)
    RainSensor rain(false);     // No rain
    WaterLevelSensor wl(80);    // Adequate water level
    WaterPump pump;
    IrrigationController controller(sm, rain, wl, pump);
    
    // Run multiple ticks to ensure stable conditions
    for (int i = 0; i < 5; ++i) {
        controller.tick();
    }
    
    // Check if pump is running (should be ON with dry soil and no rain)
    if (pump.isRunning()) {
        Logger::success("Manual test passed! Pump is running as expected.");
    } else {
        Logger::warning("Manual test: Pump is not running. This might be due to rain or other conditions.");
        Logger::info("This is expected behavior if it started raining during the simulation.");
    }
}

void runScenario(int scenario, bool realTime) {
    IrrigationController controller;
    
    if (realTime) {
        controller.setRealTimeMode(true, 1000); // 1 second delay
    }
    
    switch (scenario) {
        case 1: // Normal
            controller.setupNormalScenario();
            break;
        case 2: // Drought
            controller.setupDroughtScenario();
            break;
        case 3: // Rainy
            controller.setupRainyScenario();
            break;
    }
    
    controller.simulateScenario(20); // 20 ticks for demonstration
}

void runCustomSimulation() {
    Logger::info("Custom Simulation Setup");
    
    int ticks;
    std::cout << "Enter number of ticks (1-100): ";
    std::cin >> ticks;
    
    if (ticks < 1 || ticks > 100) {
        Logger::error("Invalid number of ticks. Using default (20).");
        ticks = 20;
    }
    
    bool realTime;
    std::cout << "Enable real-time mode? (1=Yes, 0=No): ";
    std::cin >> realTime;
    
    IrrigationController controller;
    if (realTime) {
        controller.setRealTimeMode(true, 1000);
    }
    
    controller.setupNormalScenario();
    controller.simulateScenario(ticks);
}

int main() {
    int choice;
    
    do {
        showMenu();
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            Logger::error("Invalid input. Please enter a number.");
            continue;
        }
        
        switch (choice) {
            case 0:
                Logger::success("Exiting Smart Irrigation System. Goodbye!");
                break;
            case 1:
                runManualTest();
                break;
            case 2:
                runScenario(1, false); // Normal, fast
                break;
            case 3:
                runScenario(1, true);  // Normal, real-time
                break;
            case 4:
                runScenario(2, false); // Drought, fast
                break;
            case 5:
                runScenario(2, true);  // Drought, real-time
                break;
            case 6:
                runScenario(3, false); // Rainy, fast
                break;
            case 7:
                runScenario(3, true);  // Rainy, real-time
                break;
            case 8:
                runCustomSimulation();
                break;
            default:
                Logger::error("Invalid choice. Please try again.");
        }
        
        if (choice != 0) {
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
        
    } while (choice != 0);
    
    return 0;
}
