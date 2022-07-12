#pragma once
#include <Arduino.h>
class Display
{

public:
    void Refresh_Fans_Screen();
    void Refresh_Temperature_Screen_1(String t1_Nextion_Text_Field, float t1_temperature, String t2_Nextion_Text_Field, float t2_temperature, String ref_temp1_screen_cmd);
    void Refresh_Temperature_Screen_2(String t3_Nextion_Text_Field, float t3_temperature, String t4_Nextion_Text_Field, float t4_temperature, String ref_temp2_screen_cmd);
    void refresh_display_screen_settings();
    void compare_screen_lock_pin();
    void menu_navigation_Nextion();
    void commands_from_display();
    void unlock_screen_with_master_pin();
    void working_stream();
    void turn_screen_sleep_mode_on_or_off();
    void lock_screen();
    void unlock_screen(); // compare pin and unlock the screen the scree lock if input is correct
    void idle();    // if the display is idle and screen sleep and screen lock are off, go to the start screen
    void load_screen();
};
extern Display display_control;
