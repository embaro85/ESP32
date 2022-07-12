#pragma once

class Fans
{

public:
    void working_stream();
    float fan1_control_voltage_up();
    float fan1_control_voltage_down();
    void fan1_control_on_off();
    float fan2_control_voltage_up();
    float fan2_control_voltage_down();
    void fan2_control_on_off();
    void turn_fans_off();
    void fan1_turn_on();
    void fan1_turn_off();
    void fan2_turn_on();
    void fan2_turn_off();
    void save_settings();
    void Load_Saved_Settings_Fans();
    void Refresh_Screen();
    void commands_from_display();
    void fans_start_routine(); // should be implemented before loading the settings
    void load_screen();
};

extern Fans fans_control;