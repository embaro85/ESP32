#include "Overview.h"
#include "definitions.h"
#include "Nextion_commands.h"

void Overview::working_stream()
{

    overview_control.refresh_screen();
    overview_control.commands_from_display();
}

void Overview::refresh_screen()
{
    
    if ((millis() > (2000 + timer2) && on_page_15 == true))
    {
        timer2 = millis();
        nextion_commands.set_text_of_screen_component(p15_t9, String(T_1, 1));
        // Serial.println(outData);
        nextion_commands.set_text_of_screen_component(p15_t10, String(T_2, 1));
        // Serial.println(outData);
        nextion_commands.set_text_of_screen_component(p15_t11, String(T_3, 1));
        // Serial.println(outData);
        nextion_commands.set_text_of_screen_component(p15_t12, String(T_4, 1));
        //  Serial.println(outData);
        if (winter_mode_activated == true)
        {
            nextion_commands.set_text_of_screen_component(p15_t13, "зимен");
        }
        if (summer_mode_activated == true)
        {
            nextion_commands.set_text_of_screen_component(p15_t13, "летен");
        }
    }
}

void Overview::commands_from_display()
{
    if (inData == p15_b4)
    {
        on_page_15 = false;
        nextion_commands.go_to_page_Nextion(7);
    }
}
Overview overview_control;