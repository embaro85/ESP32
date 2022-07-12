#pragma once

class Heaters
{

public:
    void working_stream();
    void set_heaters_manual_control();
    void set_screen_for_manual_control();
    void h1_manual_on_off();
    void h2_manual_on_off();
    void h3_manual_on_off();
    void h1_state();
    void h2_state();
    void h3_state();
    void heaters_antifreeze_protection(); //unifies the methods for the heaters
    void heaters_manual_control();
    void turn_heaters_off();
    void resfresh_page_p2();
    void commands_from_display();
    void h1_temperature_control();
    void refresh_page_p3();
    void save_manual_settings_p3();
    void load_manual_settings_p3();
    void h1_PID_control();
    void h2_PID_control();
    void h3_PID_control();
    void h_turn_on(uint8_t heater_number);
    void h_turn_off(uint8_t heater_number);
    void turn_heaters_on_or_off();
};

extern Heaters heaters_control;
