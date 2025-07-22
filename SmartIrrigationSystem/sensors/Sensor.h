#pragma once
#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
public:
    virtual void update() = 0;
    virtual float getValue() const = 0;
    virtual ~Sensor() {}
};

#endif // SENSOR_H 