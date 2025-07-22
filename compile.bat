@echo off
where g++ >nul 2>nul
if %ERRORLEVEL%==0 (
    goto compile
)

echo g++ not found. Installing MSYS2 (which provides g++) using winget...
winget install -e --id MSYS2.MSYS2

echo.
echo MSYS2 has been installed.
echo To install g++ (mingw-w64), please run the following in the MSYS2 MinGW terminal:
echo     pacman -S --noconfirm mingw-w64-x86_64-gcc
echo.
echo After installation, restart your terminal or add the MSYS2 MinGW bin directory to your PATH.
pause
exit /b 1

:compile
g++ -std=c++17 -ISmartIrrigationSystem -ISmartIrrigationSystem/sensors -ISmartIrrigationSystem/controller -ISmartIrrigationSystem/actuators -ISmartIrrigationSystem/utils SmartIrrigationSystem/main.cpp SmartIrrigationSystem/controller/IrrigationController.cpp SmartIrrigationSystem/sensors/SoilMoistureSensor.cpp SmartIrrigationSystem/sensors/RainSensor.cpp SmartIrrigationSystem/sensors/WaterLevelSensor.cpp SmartIrrigationSystem/sensors/AirTempSensor.cpp SmartIrrigationSystem/sensors/LightSensor.cpp SmartIrrigationSystem/actuators/WaterPump.cpp SmartIrrigationSystem/utils/Logger.cpp -o main.exe
if %ERRORLEVEL% EQU 0 (
    echo Compilation successful!
    echo Running the program...
    main.exe
) else (
    echo Compilation failed!
)
pause