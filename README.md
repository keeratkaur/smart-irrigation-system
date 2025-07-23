# Smart Irrigation System Simulation

A C++ simulation of a smart irrigation system with:
- Soil moisture, rain, water level, air temperature, and light sensors
- Water pump actuator
- Realistic irrigation logic
- Real-time and fast simulation modes
- Color-coded, human-readable logs
- Interactive scenario menu

## Features
- **Sensors:** Soil moisture, rain, water level, air temperature, light
- **Actuator:** Water pump
- **Irrigation Logic:**
  - Pump ON if soil < 40%, not raining, water level OK
  - Pump OFF if soil ≥ 70%, raining, or water level low
- **Simulation:**
  - Real-time (with delays) or fast mode
  - Simulated clock (e.g., [08:00], [08:30], ...)
  - Scenario selection (normal, drought, rainy, custom)
- **Logging:**
  - Color-coded output (ANSI, works in most terminals)
  - All sensor values and pump state in one line

## Build & Run

| Environment              | Recommended Build Command   |
|-------------------------|----------------------------|
| Linux/macOS             | `make` or `./compile.sh`   |
| Windows (MSYS2/Git Bash)| `./compile.sh`             |
| Windows (cmd/PowerShell)| `compile.bat`              |

### Linux/macOS (Recommended: Makefile)
```sh
make        # Build
make run    # Build and run
make clean  # Remove executable
```

### Linux/macOS (Alternative: Shell Script)
```sh
chmod +x compile.sh
./compile.sh
```

### Windows (MSYS2 MinGW recommended)
```sh
./compile.sh
```

### Windows (cmd/PowerShell)

```sh
compile.bat
```

- The batch script will:
  - Automatically install MSYS2 (if not already installed) using winget.
  - Install or update the GCC (g++) compiler inside MSYS2.
  - Add the MSYS2 MinGW-w64 bin directory to your PATH.
  - Attempt to delete any locked `main.exe` before compiling.
- If you see a warning about `main.exe` being locked, ensure it is not running and try again.
- After the first run, you may need to restart your terminal for PATH changes to take effect.

- Requires a C++17 compiler (g++ 7+, clang 6+, MSVC 2017+)
- No external dependencies

## Usage
- Follow the interactive menu to select scenarios or run custom simulations
- Real-time mode simulates real-world delays (1s per tick)
- All logs are printed to the terminal

## Example Output
```
[SENSOR] [08:00] SoilMoisture: 49% | AirTemp: 23 C | Rain: No | Light: 781lx | WaterLevel: 80% | Pump: OFF
[SENSOR] [08:30] SoilMoisture: 48% | AirTemp: 23 C | Rain: No | Light: 774lx | WaterLevel: 80% | Pump: OFF
...
```


<img width="519" height="264" alt="image" src="https://github.com/user-attachments/assets/29b2ac10-2bb7-484a-961f-636a1329d2fd" />


<img width="1086" height="939" alt="image" src="https://github.com/user-attachments/assets/0e24eca5-9665-4508-bdcb-760b768e2752" />


## Notes
- For best color support, use a modern terminal (Linux/macOS Terminal, Windows Terminal, or MSYS2 MinGW shell)
- If you see strange characters for the degree symbol, the code uses `C` for compatibility
- All code is standard C++17 and portable

## License
MIT 
