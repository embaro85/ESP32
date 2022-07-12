#pragma once

class Dampers
{
private:
    /* data */
public:
    void working_stream();
    void commands_from_display();
    void damper_1_control();
    void damper_2_control();
    void damper_3_control();
    void damper_4_control();
    void refresh_screen();
    void save_settings();
    void load_settings();
    int maximum_delay();
    int minimum_delay();
    void dampers_start_routine(); //should be started after loading the saved settings
    void turn_damper_1_on();      //switches the controller pin and sets the state to true on DAMPER 1
    void turn_damper_1_off();     //switches the controller pin and sets the state to false on DAMPER 1
    void turn_damper_2_on();      //switches the controller pin and sets the state to true on DAMPER 2
    void turn_damper_2_off();     //switches the controller pin and sets the state to false on DAMPER 2
    void turn_damper_3_on();      //switches the controller pin and sets the state to true on DAMPER 3
    void turn_damper_3_off();     //switches the controller pin and sets the state to false on DAMPER 3
    void turn_damper_4_on();      //switches the controller pin and sets the state to true on DAMPER 4
    void turn_damper_4_off();     //switches the controller pin and sets the state to false on DAMPER 4
};

extern Dampers dampers_control;
