#pragma once
#include <Arduino.h>

class Settings
{
private:
    /* data */
public:
   
void working_stream();
void show_info_text();
void hide_info_text();
bool toggle_button_set_h1_power();
bool toggle_button_set_h2_power();
bool toggle_button_set_h3_power();
void increase_decrease_heater_1_power();
void increase_decrease_heater_2_power();
void increase_decrease_heater_3_power();







};

extern Settings settings_control;
