#pragma once
#include <Arduino.h>

class Screen_saver
{

public:
    void working_stream();
    void show_hide_indicators();
    void refresh_screen();
    void load_screen();
    void commands_from_display();
};

extern Screen_saver screen_saver_control;