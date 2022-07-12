#include "Heater_settings.h"
#include "definitions.h"
#include "Nextion_commands.h"
#include "SPIFFS.h"
#include "StringSplitter.h"

void Heaters_settings::working_stream()
{
    heaters_settings_control.heater1_enabled();
    heaters_settings_control.heater2_enabled();
    heaters_settings_control.heater3_enabled();
    heaters_settings_control.commands_from_display();
    heaters_settings_control.h1_settings();
    heaters_settings_control.h2_settings();
    heaters_settings_control.h3_settings();
    heaters_settings_control.save_settings_heater1();
    heaters_settings_control.save_settings_heater2();
    heaters_settings_control.save_settings_heater3();
    heaters_settings_control.save_heaters_settings_p14();
}

void Heaters_settings::heater1_enabled() // enable/disable heater 1 from the heaters setting menu
{
    if (inData == p14_c0_on_1406)
    {
        h1_enabled = true;
    }
    if (inData == p14_c0_off_1407)
    {
        h1_enabled = false;
    }
}
void Heaters_settings::heater2_enabled() // enable/disable heater 2 from the heaters setting menu
{
    if (inData == p14_c1_on_1408)
    {
        h2_enabled = true;
    }
    if (inData == p14_c1_off_1409)
    {
        h2_enabled = false;
    }
}
void Heaters_settings::heater3_enabled() // enable/disable heater 3 from the heaters setting menu
{
    if (inData == p14_c2_on_1410 /*&& H3_antifreeze_enabled == false*/)
    {
        h3_enabled = true;
    }
    if (inData == p14_c2_off_1411 /*&& H3_antifreeze_enabled == true*/)
    {
        h3_enabled = false;
    }
}
void Heaters_settings::commands_from_display()
{
    if (inData == p14_b5_command && h1_enabled == true)
    {
        nextion_commands.go_to_page_Nextion(18);
        heaters_settings_control.refresh_page_h1_settings();
    }
    if (inData == p14_b1_command && h2_enabled == true)
    {
        nextion_commands.go_to_page_Nextion(19);
        heaters_settings_control.refresh_page_h2_settings();
    }
    if (inData == p14_b7_command && h3_enabled == true)
    {
        nextion_commands.go_to_page_Nextion(20);
        heaters_settings_control.refresh_page_h3_settings();
    }
    if (inData == p14_b4_command)
    {
        nextion_commands.go_to_page_Nextion(7);
    }
    if (inData == p18_b4_command)
    {
        nextion_commands.go_to_page_Nextion(14);
        heaters_settings_control.refresh_page();
    }
    if (inData == p19_b4_command)
    {
        nextion_commands.go_to_page_Nextion(14);
        heaters_settings_control.refresh_page();
    }
    if (inData == p20_b4_command)
    {
        nextion_commands.go_to_page_Nextion(14);
        heaters_settings_control.refresh_page();
    }
}
void Heaters_settings::h1_settings()
{
    if (inData == p18_b5_command) //increase setpoint temperature of heater 1
    {
        temperature_setpoint_1 = temperature_setpoint_1 + 1;
        nextion_commands.set_text_of_screen_component(p18_t3, String(temperature_setpoint_1) + " œC");
        threshold_temperature_heating = temperature_setpoint_1; //threshold temperature and H1 set point temperature are linked
    }
    if (inData == p18_b6_command) //decrease setpoint temperature of heater 1
    {
        temperature_setpoint_1 = temperature_setpoint_1 - 1;
        nextion_commands.set_text_of_screen_component(p18_t3, String(temperature_setpoint_1) + " œC");
        threshold_temperature_heating = temperature_setpoint_1; //threshold temperature and H1 set point temperature are linked
    }
    if (inData == p18_b7_command) // increase the minimum working time of heater 1
    {
        h1_time_period = h1_time_period + 5;
        nextion_commands.set_text_of_screen_component(p18_t5, String(h1_time_period) + " ÓÅË.");
    }
    if (inData == p18_b3_command) // decrease the minimum working time of heater 1
    {
        if (h1_time_period > 0)
        {
            h1_time_period = h1_time_period - 5;
            nextion_commands.set_text_of_screen_component(p18_t5, String(h1_time_period) + " ÓÅË.");
        }
    }
}
void Heaters_settings::h2_settings()
{
    if (inData == p19_b5_command_1901) //increase setpoint temperature of heater 2
    {
        temperature_setpoint_2 = temperature_setpoint_2 + 1;
        nextion_commands.set_text_of_screen_component(p19_t3, String(temperature_setpoint_2) + " œC");
    }
    if (inData == p19_b6_command) //decrease setpoint temperature of heater 2
    {
        temperature_setpoint_2 = temperature_setpoint_2 - 1;
        nextion_commands.set_text_of_screen_component(p19_t3, String(temperature_setpoint_2) + " œC");
    }
    if (inData == p19_b7_command) //increase the minimum working time of heater 2
    {
        h2_time_period = h2_time_period + 5;
        nextion_commands.set_text_of_screen_component(p19_t5, String(h2_time_period) + " ÓÅË.");
    }
    if (inData == p19_b3_command) // decrease the minimum working time of heater 2
    {
        if (h2_time_period > 0)
        {
            h2_time_period = h2_time_period - 5;
            nextion_commands.set_text_of_screen_component(p19_t5, String(h2_time_period) + " ÓÅË.");
        }
    }
}
void Heaters_settings::h3_settings()
{
    if (inData == p20_b5_command) //increase setpoint temperature of heater 3
    {
        temperature_setpoint_3 = temperature_setpoint_3 + 1;
        nextion_commands.set_text_of_screen_component(p20_t3, String(temperature_setpoint_3) + " œC");
    }
    if (inData == p20_b6_command) //decrease setpoint temperature of heater 3
    {
        temperature_setpoint_3 = temperature_setpoint_3 - 1;
        nextion_commands.set_text_of_screen_component(p20_t3, String(temperature_setpoint_3) + " œC");
    }
    if (inData == p20_b7_command) //increase the minimum working time of heater 3
    {
        h3_time_period = h3_time_period + 5;
        nextion_commands.set_text_of_screen_component(p20_t5, String(h3_time_period) + " ÓÅË.");
    }
    if (inData == p20_b3_command) // decrease the minimum working time of heater 3
    {
        if (h3_time_period > 0)
        {
            h3_time_period = h3_time_period - 5;
            nextion_commands.set_text_of_screen_component(p20_t5, String(h3_time_period) + " ÓÅË.");
        }
    }
}
void Heaters_settings::refresh_page()
{
    {
        nextion_commands.set_value_of_screen_component(p14_c0_value, h1_enabled);
        nextion_commands.set_value_of_screen_component(p14_c1_value, h2_enabled);
        nextion_commands.set_value_of_screen_component(p14_c2_value, h3_enabled);
    }
}
void Heaters_settings::refresh_page_h1_settings()
{
    nextion_commands.set_text_of_screen_component(p18_t3, String(temperature_setpoint_1) + " œC");
    nextion_commands.set_text_of_screen_component(p18_t5, String(h1_time_period) + " ÓÅË.");
}
void Heaters_settings::refresh_page_h2_settings()
{
    nextion_commands.set_text_of_screen_component(p19_t3, String(temperature_setpoint_2) + " œC");
    nextion_commands.set_text_of_screen_component(p19_t5, String(h2_time_period) + " ÓÅË.");
}
void Heaters_settings::refresh_page_h3_settings()
{
    nextion_commands.set_text_of_screen_component(p20_t3, String(temperature_setpoint_3) + " œC");
    nextion_commands.set_text_of_screen_component(p20_t5, String(h3_time_period) + " ÓÅË.");
}
void Heaters_settings::save_settings_heater1()
{
    String _heater1_settings = heater1_settings;
    heater1_settings = String(temperature_setpoint_1) + "," + String(h1_time_period) + ",";
    if (_heater1_settings != heater1_settings)
    {
        Serial.println("New Settings for Heater 1 detected: " + heater1_settings);
        File saved_values_heater1_settings;
        saved_values_heater1_settings = SPIFFS.open("/values_heater1_settings.txt", FILE_WRITE);
        if (saved_values_heater1_settings.print(heater1_settings))
        {
            Serial.println("New settings for the heaters have been changed and successfully written to the internal memory");
        }
        else
        {
            Serial.println("File write for the heaters settings failed");
        }
        saved_values_heater1_settings.close();
    }
}
void Heaters_settings::save_settings_heater2()
{
    String _heater2_settings = heater2_settings;
    heater2_settings = String(temperature_setpoint_2) + "," + String(h2_time_period) + ",";
    if (_heater2_settings != heater2_settings)
    {
        Serial.println("New Settings for Heater 2 detected: " + heater2_settings);
        File saved_values_heater2_settings;
        saved_values_heater2_settings = SPIFFS.open("/values_heater2_settings.txt", FILE_WRITE);
        if (saved_values_heater2_settings.print(heater2_settings))
        {
            Serial.println("New settings for the heaters have been changed and successfully written to the internal memory");
        }
        else
        {
            Serial.println("File write for the heaters settings failed");
        }
        saved_values_heater2_settings.close();
    }
}
void Heaters_settings::save_settings_heater3()
{
    String _heater3_settings = heater3_settings;
    heater3_settings = String(temperature_setpoint_3) + "," + String(h3_time_period) + ",";
    if (_heater3_settings != heater3_settings)
    {
        Serial.println("New Settings for Heater 3 detected: " + heater3_settings);
        File saved_values_heater3_settings;
        saved_values_heater3_settings = SPIFFS.open("/values_heater3_settings.txt", FILE_WRITE);
        if (saved_values_heater3_settings.print(heater3_settings))
        {
            Serial.println("New settings for the heaters have been changed and successfully written to the internal memory");
        }
        else
        {
            Serial.println("File write for the heaters settings failed");
        }
        saved_values_heater3_settings.close();
    }
}
void Heaters_settings::load_saved_settings_heater1()
{
    File saved_values_heater1_settings;
    saved_values_heater1_settings = SPIFFS.open("/values_heater1_settings.txt", "r");
    if (!saved_values_heater1_settings)
    {
        Serial.println("Failed to open heaters settings file for reading");
        return;
    }
    Serial.print("Heater 1 Settings: ");
    heater1_settings = saved_values_heater1_settings.readString();
    saved_values_heater1_settings.close();
    Serial.println(heater1_settings);
    StringSplitter *splitter = new StringSplitter(heater1_settings, ',', 2);
    String _temperature_setpoint_1 = splitter->getItemAtIndex(0);
    String _h1_time_period = splitter->getItemAtIndex(1);
    temperature_setpoint_1 = _temperature_setpoint_1.toInt();
    h1_time_period = _h1_time_period.toInt();
}
void Heaters_settings::load_saved_settings_heater2()
{
    File saved_values_heater2_settings;
    saved_values_heater2_settings = SPIFFS.open("/values_heater2_settings.txt", "r");
    if (!saved_values_heater2_settings)
    {
        Serial.println("Failed to open heaters settings file for reading");
        return;
    }
    Serial.print("Heater 2 Settings: ");
    heater2_settings = saved_values_heater2_settings.readString();
    saved_values_heater2_settings.close();
    Serial.println(heater2_settings);
    StringSplitter *splitter = new StringSplitter(heater2_settings, ',', 3);
    String _temperature_setpoint_2 = splitter->getItemAtIndex(0);
    String _h2_time_period = splitter->getItemAtIndex(1);
    temperature_setpoint_2 = _temperature_setpoint_2.toInt();
    h2_time_period = _h2_time_period.toInt();
}
void Heaters_settings::load_saved_settings_heater3()
{
    File saved_values_heater3_settings;
    saved_values_heater3_settings = SPIFFS.open("/values_heater3_settings.txt", "r");
    if (!saved_values_heater3_settings)
    {
        Serial.println("Failed to open heaters settings file for reading");
        return;
    }
    Serial.print("Heater 3 Settings: ");
    heater3_settings = saved_values_heater3_settings.readString();
    saved_values_heater3_settings.close();
    Serial.println(heater3_settings);
    StringSplitter *splitter = new StringSplitter(heater3_settings, ',', 3);
    String _temperature_setpoint_3 = splitter->getItemAtIndex(0);
    String _h3_time_period = splitter->getItemAtIndex(1);
    temperature_setpoint_3 = _temperature_setpoint_3.toInt();
    h3_time_period = _h3_time_period.toInt();
}
void Heaters_settings::save_heaters_settings_p14()
{
    String _heaters_settings = heaters_settings;
    heaters_settings = String(h1_enabled) + "," + String(h2_enabled) + "," + String(h3_enabled) + ",";
    if (_heaters_settings != heaters_settings)
    {
        Serial.println("New Heaters Settings detected: " + heaters_settings);
        File saved_values_heaters_settings;
        saved_values_heaters_settings = SPIFFS.open("/values_heaters_settings.txt", FILE_WRITE);
        if (saved_values_heaters_settings.print(heaters_settings))
        {
            Serial.println("New settings for the heaters have been changed and successfully written to the internal memory");
        }
        else
        {
            Serial.println("File write for the heaters settings failed");
        }
        saved_values_heaters_settings.close();
    }
}
void Heaters_settings::load_heaters_settings_p14()
{
    File saved_values_heaters_settings;
    saved_values_heaters_settings = SPIFFS.open("/values_heaters_settings.txt", "r");
    if (!saved_values_heaters_settings)
    {
        Serial.println("Failed to open heaters settings file for reading");
        return;
    }
    Serial.print("Heaters Settings: ");
    heaters_settings = saved_values_heaters_settings.readString();
    saved_values_heaters_settings.close();
    Serial.println(heaters_settings);
    StringSplitter *splitter = new StringSplitter(heaters_settings, ',', 6);
    String _h1_enabled = splitter->getItemAtIndex(0);
    String _h2_enabled = splitter->getItemAtIndex(1);
    String _h3_enabled = splitter->getItemAtIndex(2);
    h1_enabled = _h1_enabled.toInt();
    h2_enabled = _h2_enabled.toInt();
    h3_enabled = _h3_enabled.toInt();
}

Heaters_settings heaters_settings_control;