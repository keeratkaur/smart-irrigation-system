@echo off
g++ -std=c++17 -ISmartIrrigationSystem -ISmartIrrigationSystem/sensors -ISmartIrrigationSystem/controller -ISmartIrrigationSystem/actuators -ISmartIrrigationSystem/utils SmartIrrigationSystem/main.cpp SmartIrrigationSystem/controller/IrrigationController.cpp SmartIrrigationSystem/sensors/SoilMoistureSensor.cpp SmartIrrigationSystem/sensors/RainSensor.cpp SmartIrrigationSystem/sensors/WaterLevelSensor.cpp SmartIrrigationSystem/sensors/AirTempSensor.cpp SmartIrrigationSystem/sensors/LightSensor.cpp SmartIrrigationSystem/actuators/WaterPump.cpp SmartIrrigationSystem/utils/Logger.cpp -o main.exe
if %ERRORLEVEL% EQU 0 (
    echo Compilation successful!
    echo Running the program...
    main.exe
) else (
    echo Compilation failed!
)
pause 