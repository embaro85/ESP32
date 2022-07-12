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
    void working_stream();
    void clean_temperature_fields();
    void refresh_screen();
    void commands_from_display();
    float calculate_heat_exchanger_efficiency();
    void extract_air_temperature_sensors();
    void supply_air_temperature_sensors();
    void ambient_air_temperature_sensors();
    void exhaust_air_temperature_sensors();
};

extern Temperatures temperatures_control;
