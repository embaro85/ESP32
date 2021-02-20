#pragma once
#include <Arduino.h>
class Display
{

public:
    void Refresh_Fans_Screen();
    void Refresh_Temperature_Screen_1(String t1_Nextion_Text_Field, float t1_temperature, String t2_Nextion_Text_Field, float t2_temperature, String ref_temp1_screen_cmd);
    void Refresh_Temperature_Screen_2(String t3_Nextion_Text_Field, float t3_temperature, String t4_Nextion_Text_Field, float t4_temperature, String ref_temp2_screen_cmd);
    void load_display_screen_settings();
    void compare_screen_lock_pin();
    void menu_navigation_Nextion();
    void refresh_heaters_screen();
    void display_settings_menu();
    void calculate_auto_off_period();
    void unlock_screen_with_master_pin();
    void send_threshold_temperature_to_screen_field();
    void send_everything_off_threshold_temperature_to_screen_field();
    //void refresh_temperature_settings_screen();
    void send_h1_power_to_screen_field();
    void send_h2_power_to_screen_field();
    void send_h3_power_to_screen_field();
    void refresh_heaters_settings_screen();

    void working_stream();
};
extern Display display_control;
