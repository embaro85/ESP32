#pragma once

class Fans
{

public:
    void fan1_control();
    void f1_calculate_pwm_value();
    void fan2_control();
    void f2_calculate_pwm_value();
};

extern Fans fans_control;