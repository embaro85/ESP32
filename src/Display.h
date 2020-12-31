#pragma once
#include<Arduino.h>
class Display
{

public:
    
    void sendDataToDisplay();
    void receive_data_from_display();
    void Refresh_Fans_Screen(String Nextion_Text_Field_f1, float f1_control_voltage, String Nextion_Text_Field_f2, float f2_control_voltage, String ref_fans_screen_cmd);
    void Refresh_Temperature_Screen_1(String t1_Nextion_Text_Field, float t1_temperature, String t2_Nextion_Text_Field, float t2_temperature, String ref_temp1_screen_cmd);
    void Refresh_Temperature_Screen_2(String t3_Nextion_Text_Field, float t3_temperature, String t4_Nextion_Text_Field, float t4_temperature, String ref_temp2_screen_cmd);
};
extern Display display_control;
