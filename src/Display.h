#pragma once
#include<Arduino.h>
class Display
{

public:
    void endNextionCommand();
    void sendDataToDisplay();
    void receive_data_from_display();
    void Refresh_Fans_Screen(String Nextion_Text_Field_f1, float f1_control_voltage, String Nextion_Text_Field_f2, float f2_control_voltage );
    void Refresh_Temperature_Screens();
};
extern Display display_control;
