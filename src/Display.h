#pragma once
#include <Arduino.h>
class Display
{

public:
    void sendDataToDisplay();
    void receive_data_from_display();
    void Refresh_Fans_Screen(String Nextion_Text_Field_f1, float f1_control_voltage, String Nextion_Text_Field_f2, float f2_control_voltage, String ref_fans_screen_cmd);
    void Refresh_Temperature_Screen_1(String t1_Nextion_Text_Field, float t1_temperature, String t2_Nextion_Text_Field, float t2_temperature, String ref_temp1_screen_cmd);
    void Refresh_Temperature_Screen_2(String t3_Nextion_Text_Field, float t3_temperature, String t4_Nextion_Text_Field, float t4_temperature, String ref_temp2_screen_cmd);
    void set_visibility_on_Nextion(String Element_name, uint8_t Visibility_toggle);
    void go_to_page_Nextion(int Page_number);
    void menu_navigation_Nextion();
    //void set_properties_page_temperature_control();
    void refresh_heaters_screen();
void display_settings_menu();
void calculate_auto_off_period();


};
extern Display display_control;
