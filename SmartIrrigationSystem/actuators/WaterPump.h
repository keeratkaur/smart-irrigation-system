#ifndef WATERPUMP_H
#define WATERPUMP_H

class WaterPump {
    bool isOn;
public:
    WaterPump();
    WaterPump(bool isOn);
    void turnOn();
    void turnOff();
    bool isRunning() const;
};

#endif // WATERPUMP_H
