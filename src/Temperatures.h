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
    uint8_t set_threshold_temperature_for_heaters_control();
    uint8_t set_everything_off_threshold_temperature();
    boolean handle_threshold_temperature();
    boolean handle_everything_off_threshold_temperature();
};

extern Temperatures temperatures_control;
