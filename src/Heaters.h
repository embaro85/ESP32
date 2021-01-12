#pragma once

class Heaters
{

public:
    void set_heaters_manual_control();
    void set_screen_for_manual_control();
    void h1_manual_on_off();
    void h2_manual_on_off();
    void h3_manual_on_off();
    void h1_state();
    void h2_state();
    void h3_state();
    void heaters_temperature_contol(); //unifies the methods for the heaters
    void heaters_manual_control();


};

extern Heaters heaters_control;
