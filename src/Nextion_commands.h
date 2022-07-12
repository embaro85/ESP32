#pragma once
#include "definitions.h"
#include <Arduino.h>

class Nextion_commands
{
public:
    void receive_data_from_display();
    void send_data_to_display();
    void set_visibility_on_Nextion(String Element_name, uint8_t Visibility_toggle);
    void set_value_of_screen_component(String nextion_component, uint8_t variable);
    void set_text_of_screen_component(String nextion_component, String variable);
    void go_to_page_Nextion(int Page_number);
    void set_touch_enable_or_disable_on_Nextion(String Element_name, uint8_t touch_enable_or_disable);
    void on_page (uint8_t on_page_number);
};

extern Nextion_commands nextion_commands;