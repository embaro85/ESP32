#pragma once

class Fans
{

public:
    float fan1_control_voltage_up(String Nextion_Text_Field_f1, float f1_control_voltage, String cmd);
    float fan1_control_voltage_down(String Nextion_Text_Field_f1, float f1_control_voltage, String cmd);
    void fan1_control_on_off();
    float fan2_control_voltage_up(String Nextion_Text_Field_f2, float f2_control_voltage, String cmd);
    float fan2_control_voltage_down(String Nextion_Text_Field_f2, float f2_control_voltage, String cmd);
    void fan2_control_on_off();
    void turn_fans_off();
    void turn_fan_1_on();
    void turn_fan_1_off();
    void turn_fan_2_on();
    void turn_fan_2_off();
};

extern Fans fans_control;