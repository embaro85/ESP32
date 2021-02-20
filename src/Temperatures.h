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
    void save_temperature_settings_heaters_control();
    void save_temperature_settings_turn_everything_on_off();
    void working_stream();
    void hide_start_info_text_t0();
    void clean_temperature_fields();
    void refresh_screen();
    void exit_page();
};

extern Temperatures temperatures_control;
