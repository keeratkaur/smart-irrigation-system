# Smart Irrigation System Makefile

CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./SmartIrrigationSystem -I./SmartIrrigationSystem/sensors -I./SmartIrrigationSystem/controller -I./SmartIrrigationSystem/actuators -I./SmartIrrigationSystem/utils
SRC = \
  SmartIrrigationSystem/main.cpp \
  SmartIrrigationSystem/controller/IrrigationController.cpp \
  SmartIrrigationSystem/sensors/SoilMoistureSensor.cpp \
  SmartIrrigationSystem/sensors/RainSensor.cpp \
  SmartIrrigationSystem/sensors/WaterLevelSensor.cpp \
  SmartIrrigationSystem/sensors/AirTempSensor.cpp \
  SmartIrrigationSystem/sensors/LightSensor.cpp \
  SmartIrrigationSystem/actuators/WaterPump.cpp \
  SmartIrrigationSystem/utils/Logger.cpp

OUT = main.exe

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT) 