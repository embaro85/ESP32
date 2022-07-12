#include "Overview.h"
#include "definitions.h"
#include "Nextion_commands.h"
#include "Temperatures.h"

void Overview::working_stream()
{
    overview_control.refresh_screen();
    overview_control.commands_from_display();
}
void Overview::refresh_screen()
{
    if ((millis() > (2000 + timer2)) && on_page_number == overview_1_15)
    {
        timer2 = millis();
        nextion_commands.set_text_of_screen_component(p15_t9, String(T_1, 1));
        nextion_commands.set_text_of_screen_component(p15_t10, String(T_2, 1));
        nextion_commands.set_text_of_screen_component(p15_t11, String(T_3, 1));
        nextion_commands.set_text_of_screen_component(p15_t12, String(T_4, 1));
        if (winter_mode == true)
        {
            nextion_commands.set_text_of_screen_component(p15_t13, "зимен");
            nextion_commands.set_text_of_screen_component(p15_t14, String(threshold_temperature_heating));
            nextion_commands.set_text_of_screen_component(p15_t15, String(threshold_temperature_antifreeze));
        }
        if (winter_mode == false)
        {
            nextion_commands.set_text_of_screen_component(p15_t13, "летен");
            nextion_commands.set_text_of_screen_component(p15_t14, "--");
            nextion_commands.set_text_of_screen_component(p15_t15, "--");
        }
        if (f1_on_off_state == true)
        {
            nextion_commands.set_text_of_screen_component(p15_t17, "включен");
        }
        if (f1_on_off_state == false)
        {
            nextion_commands.set_text_of_screen_component(p15_t17, "изключен");
        }
        if (f2_on_off_state == true)
        {
            nextion_commands.set_text_of_screen_component(p15_t16, "включен");
        }
        if (f2_on_off_state == false)
        {
            nextion_commands.set_text_of_screen_component(p15_t16, "изключен");
        }
        if (heater1_on_off_state == false && heater2_on_off_state == false && heater3_on_off_state == false)
        {
            nextion_commands.set_text_of_screen_component(p15_t19, String(temperatures_control.calculate_heat_exchanger_efficiency(), 0) + "%");
        }
    }
}
void Overview::commands_from_display()
{
    if (inData == p15_b4)
    {
        //on_page_15 = false;
        nextion_commands.on_page(Settings_7);
        nextion_commands.go_to_page_Nextion(7);
    }
}
Overview overview_control;