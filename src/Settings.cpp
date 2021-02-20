#include "Settings.h"
#include "definitions.h"
#include "Nextion_commands.h"
#include "Display.h"

void Settings::working_stream()
{
    settings_control.show_info_text();
    settings_control.hide_info_text();
    settings_control.toggle_button_set_h1_power();
    settings_control.toggle_button_set_h2_power();
    settings_control.toggle_button_set_h3_power();
}

void Settings::show_info_text()
{
    if (inData == p14_t7_info_button)
    {
        nextion_commands.set_visibility_on_Nextion(p14_t0, 1);
        nextion_commands.set_visibility_on_Nextion("b2", 1);
    }
}
void Settings::hide_info_text()
{
    if (inData == p14_b2)
    {
        nextion_commands.set_visibility_on_Nextion("b2", 0);
        nextion_commands.set_visibility_on_Nextion(p14_t0, 0);
        display_control.refresh_heaters_settings_screen();
    }
}
bool Settings::toggle_button_set_h1_power()
{
    if (inData == p14_c0_on)
    {
        h1_available = true;
    }
    if (inData == p14_c0_off)
    {
        h1_available = false;
        h1_power = 0.00;
        outData = "t3.txt=\"" + String(h1_power) + "kW" + "\"";
        nextion_commands.send_data_to_display();
        Serial.println("Heater 1 is unavailable");
    }
    return h1_available;
}
bool Settings::toggle_button_set_h2_power()
{
    if (inData == p14_c1_on)
    {
        h2_available = true;
    }
    if (inData == p14_c1_off)
    {
        h2_available = false;
        h2_power = 0.00;
        outData = "t4.txt=\"" + String(h2_power) + "kW" + "\"";
        nextion_commands.send_data_to_display();
        Serial.println("Heater 2 is unavailable");
    }
    return h2_available;
}
bool Settings::toggle_button_set_h3_power()
{
    if (inData == p14_c2_on)
    {
        h3_available = true;
    }
    if (inData == p14_c2_off)
    {
        h3_available = false;
        h3_power = 0.00;
        outData = "t5.txt=\"" + String(h3_power) + "kW" + "\"";
        nextion_commands.send_data_to_display();
        Serial.println("Heater 3 is unavailable");
    }
    return h3_available;
}
void Settings::increase_decrease_heater_1_power()
{
    if (h1_available)
    {
        if (inData == p14_b5)
        {
            h1_power = h1_power + 0.1;
        }
        if (inData == p14_b6)
        {
            h1_power = h1_power - 0.1;
        }
    }
}
void Settings::increase_decrease_heater_2_power()
{
    if (h2_available)
    {
        if (inData == p14_b1)
        {
            h2_power = h2_power + 0.1;
        }
        if (inData == p14_b0)
        {
            h2_power = h2_power - 0.1;
        }
    }
}
void Settings::increase_decrease_heater_3_power()
{
    if (h3_available)
    {
        if (inData == p14_b7)
        {
            h3_power = h3_power + 0.1;
        }
        if (inData == p14_b3)
        {
            h3_power = h3_power - 0.1;
        }
    }
}

Settings settings_control;