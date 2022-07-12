#include "Temperature_settings.h"
#include "definitions.h"
#include "Nextion_commands.h"
#include <SPIFFS.h>
#include <StringSplitter.h>

void Temperature_settings::working_stream()
{
    temperature_settings_control.summer_winter_mode();
    temperature_settings_control.commands_from_display();
    temperature_settings_control.save_settings();
}

void Temperature_settings::refresh_screen()
{
    if (winter_mode == true)
    {
        nextion_commands.set_text_of_screen_component(p10_t1, String(threshold_temperature_heating));
        nextion_commands.set_text_of_screen_component(p10_t3, String(threshold_temperature_antifreeze));
        nextion_commands.set_visibility_on_Nextion(p10_b5, 1);
        nextion_commands.set_visibility_on_Nextion(p10_b6, 1);
        nextion_commands.set_visibility_on_Nextion(p10_b0, 1);
        nextion_commands.set_visibility_on_Nextion(p10_b1, 1);
        nextion_commands.set_visibility_on_Nextion(p10_c0, 1);
        nextion_commands.set_visibility_on_Nextion(p10_c1, 1);
    }
    if (winter_mode == false)
    {
        nextion_commands.set_text_of_screen_component(p10_t1, "--");
        nextion_commands.set_text_of_screen_component(p10_t3, "--");
        nextion_commands.set_visibility_on_Nextion(p10_b5, 0);
        nextion_commands.set_visibility_on_Nextion(p10_b6, 0);
        nextion_commands.set_visibility_on_Nextion(p10_b0, 0);
        nextion_commands.set_visibility_on_Nextion(p10_b1, 0);
        nextion_commands.set_visibility_on_Nextion(p10_c0, 0);
        nextion_commands.set_visibility_on_Nextion(p10_c1, 0);
    }
    nextion_commands.set_value_of_screen_component(p10_c0_value, heating_enabled);
    nextion_commands.set_value_of_screen_component(p10_c1_value, antifreeze_ebanbled);
    nextion_commands.set_value_of_screen_component(p10_bt0_value, (!winter_mode));
    nextion_commands.set_value_of_screen_component(p10_bt1_value, winter_mode);
    if (heating_enabled == false)
    {
        nextion_commands.set_text_of_screen_component(p10_t1, "--");
    }
    if (antifreeze_ebanbled == false)
    {
        nextion_commands.set_text_of_screen_component(p10_t3, "--");
    }
}
bool Temperature_settings::summer_winter_mode() // switch between summer and winter mode
{
    if (inData == summer_mode_p10_bt0) // turn OFF winter mode
    {
        winter_mode = false;
        temperature_settings_control.refresh_screen();
        Serial.println("Winter Mode is OFF");
        heating_enabled = false;
        antifreeze_ebanbled = false;
       // heaters_on = true; //needed as a run once variable
        return true;
    }
    if (inData == winter_mode_p10_bt1) // turn on winter mode
    {
        winter_mode = true;
        temperature_settings_control.refresh_screen();
        Serial.println("Winter Mode is ON");
        return false;
    }
}
void Temperature_settings::save_settings()
{
    String _temperature_settings = temperature_settings;
    temperature_settings = String(threshold_temperature_heating) + "," + String(threshold_temperature_antifreeze) + "," + String(winter_mode) + "," + String(heating_enabled) + "," + String(antifreeze_ebanbled);
    if (temperature_settings != _temperature_settings)
    {
        Serial.println("New Temperature Settings detected: " + temperature_settings);
        File saved_values_temperature_settings;
        saved_values_temperature_settings = SPIFFS.open("/values_temp_settings.txt", FILE_WRITE);
        if (saved_values_temperature_settings.print(temperature_settings))
        {
            Serial.println("New settings for the temperatures have been changed and successfully written to the internal memory");
        }
        else
        {
            Serial.println("File write for the temperature settings failed");
        }
        saved_values_temperature_settings.close();
    }
}
void Temperature_settings::load_settings()
{
    File saved_values_temperature_settings;
    saved_values_temperature_settings = SPIFFS.open("/values_temp_settings.txt", "r");
    if (!saved_values_temperature_settings)
    {
        Serial.println("Failed to open temperature settings file for reading");
        return;
    }
    Serial.print("Temperature Settings: ");
    temperature_settings = saved_values_temperature_settings.readString();
    saved_values_temperature_settings.close();
    Serial.println(temperature_settings);
    StringSplitter *splitter = new StringSplitter(temperature_settings, ',', 6);
    String _threshhold_temperature_heating = splitter->getItemAtIndex(0);
    String _threshold_temperature_antifreeze = splitter->getItemAtIndex(1);
    String _winter_mode_activated = splitter->getItemAtIndex(2);
    String _heating_enabled = splitter->getItemAtIndex(3);
    String _antifreeze_ebanbled = splitter->getItemAtIndex(4);
    threshold_temperature_heating = _threshhold_temperature_heating.toInt();
    threshold_temperature_antifreeze = _threshold_temperature_antifreeze.toInt();
    winter_mode = _winter_mode_activated.toInt();
    heating_enabled = _heating_enabled.toInt();
    antifreeze_ebanbled = _antifreeze_ebanbled.toInt();
}
void Temperature_settings::commands_from_display()
{
    if (inData == p10_b5_command_101 && heating_enabled == true) //increase heating temperature
    {
        threshold_temperature_heating++;
        temperature_settings_control.refresh_screen();
        temperature_setpoint_1 = threshold_temperature_heating;
        temperature_setpoint_2 = threshold_temperature_heating -2;
        temperature_setpoint_3 = threshold_temperature_heating -4;
    }
    if (inData == p10_b6_command && heating_enabled == true) // decrease heating temperature
    {
        threshold_temperature_heating--;
        temperature_settings_control.refresh_screen();
        temperature_setpoint_1 = threshold_temperature_heating;
        temperature_setpoint_2 = threshold_temperature_heating - 2;
        temperature_setpoint_3 = threshold_temperature_heating - 4;
    }
    if (inData == p10_b1_command && antifreeze_ebanbled == true) //increase antifreeze threshold temperature
    {
        threshold_temperature_antifreeze++;
        temperature_settings_control.refresh_screen();
    }
    if (inData == p10_b0_command && antifreeze_ebanbled == true) // decrease antifreeze threshold temperature
    {
        threshold_temperature_antifreeze--;
        temperature_settings_control.refresh_screen();
    }
    if (inData == p10_t7_command) // displays a info text
    {
        nextion_commands.set_visibility_on_Nextion("t6", 1);
    }
    if (inData == p10_t5_t6_command) //hides the info text boxes
    {
        nextion_commands.set_visibility_on_Nextion("t5", 0);
        nextion_commands.set_visibility_on_Nextion("t6", 0);
    }
    if (inData == p10_t4_command) // displays info text
    {
        nextion_commands.set_visibility_on_Nextion("t5", 1);
    }
    if (inData == p10_c0_enabled_112 && winter_mode == true) //enable heating if winter mode is active
    {
        heating_enabled = true;
        temperature_settings_control.refresh_screen();
    }
    if (inData == p10_c0_disabled_113) // disable heating
    {
        heating_enabled = false;
       // heaters_on = true; //needed as a run once variable
        temperature_settings_control.refresh_screen();
    }
    if (inData == p10_c1_enabled_114 && winter_mode == true) // enable antifreeze protection
    {
        antifreeze_ebanbled = true;
        temperature_settings_control.refresh_screen();
    }
    if (inData == p10_c1_disabled_115) // disable antifreeze protection
    {
        antifreeze_ebanbled = false;
       // heaters_on = true; //needed as a run once variable
        temperature_settings_control.refresh_screen();
    }
}

Temperature_settings temperature_settings_control;
