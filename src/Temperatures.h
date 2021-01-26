#pragma once
#include "definitions.h"
#include <OneWire.h>
#include <DallasTemperature.h>

class Temperatures
{

public:
    //void printAddress(DeviceAddress deviceAddress);
    void temp_sensor_begin(); // used once in Setup
    void measure_temperatures();
    void set_threshold_temperature_for_heaters_control();
};

extern Temperatures temperatures_control;
