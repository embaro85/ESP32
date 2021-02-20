#include "Temperature_settings.h"
#include "definitions.h"
#include "Nextion_commands.h"




void Temperature_settings::working_stream()
{
//temperature_settings_control.refresh_screen();
temperature_settings_control.summer_winter_mode();
}


void Temperature_settings::refresh_screen()
{
    if (winter_mode_activated == true)
    {
        nextion_commands.set_text_of_screen_component(p10_t1, String(threshold_temperature));
        nextion_commands.set_text_of_screen_component(p10_t3, String(turn_everything_off_temperature_threshold));
        nextion_commands.set_value_of_screen_component(p10_bt0, summer_mode_activated);
        nextion_commands.set_value_of_screen_component(p10_bt1, winter_mode_activated);
    }
    if (summer_mode_activated == true)
    {
        nextion_commands.set_text_of_screen_component(p10_t1, "--");
        nextion_commands.set_text_of_screen_component(p10_t3, "--");
        nextion_commands.set_value_of_screen_component(p10_bt0, summer_mode_activated);
        nextion_commands.set_value_of_screen_component(p10_bt1, winter_mode_activated);
        nextion_commands.set_visibility_on_Nextion(p10_b5, 0);
        nextion_commands.set_visibility_on_Nextion(p10_b6, 0);
        nextion_commands.set_visibility_on_Nextion(p10_b0, 0);
        nextion_commands.set_visibility_on_Nextion(p10_b1, 0);
    }
}

bool Temperature_settings::summer_winter_mode()
{
    if (inData == summer_mode_p10_bt0)
    {
        summer_mode_activated = true;
        winter_mode_activated = false;
        nextion_commands.set_value_of_screen_component(p10_bt0, summer_mode_activated);
        nextion_commands.set_value_of_screen_component(p10_bt1, winter_mode_activated);
        outData = p10_t1 + "--" + "\"";
        nextion_commands.send_data_to_display();
        outData = p10_t3 + "--" + "\"";
        nextion_commands.send_data_to_display();
        nextion_commands.set_visibility_on_Nextion(p10_b5, 0);
        nextion_commands.set_visibility_on_Nextion(p10_b6, 0);
        nextion_commands.set_visibility_on_Nextion(p10_b0, 0);
        nextion_commands.set_visibility_on_Nextion(p10_b1, 0);
        nextion_commands.set_visibility_on_Nextion(p10_b2,0);
        nextion_commands.set_visibility_on_Nextion(p10_b3, 0);
    temperature_settings_control.refresh_screen();

        return true;
    }
    if (inData == winter_mode_p10_bt1)
    {
        summer_mode_activated = false;
        winter_mode_activated = true;
        nextion_commands.set_value_of_screen_component(p10_bt0, summer_mode_activated);
        nextion_commands.set_value_of_screen_component(p10_bt1, winter_mode_activated);
        nextion_commands.set_visibility_on_Nextion(p10_b5, 1);
        nextion_commands.set_visibility_on_Nextion(p10_b6, 1);
        nextion_commands.set_visibility_on_Nextion(p10_b0, 1);
        nextion_commands.set_visibility_on_Nextion(p10_b1, 1);
        temperature_settings_control.refresh_screen();
    temperature_settings_control.refresh_screen();

        return false;
    }
}


Temperature_settings temperature_settings_control;
