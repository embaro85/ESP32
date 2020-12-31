#pragma once

class Fans
{

public:
    void fan1_control_voltage_up(String Nextion_Text_Field_f1, float f1_control_voltage, String cmd);
    void fan1_control_voltage_down(String Nextion_Text_Field_f1, float f1_control_voltage, String cmd);
    void fan1_control_on_off();
    //void f1_calculate_pwm_value();
    void fan2_control_voltage_up(String Nextion_Text_Field_f2, float f2_control_voltage, String cmd);
    void fan2_control_voltage_down(String Nextion_Text_Field_f2, float f2_control_voltage, String cmd);
    void fan2_control_on_off();
    //void f2_calculate_pwm_value();
};

extern Fans fans_control;