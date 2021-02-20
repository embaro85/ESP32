#include <Arduino.h>
#include "definitions.h"
#include <StringSplitter.h>
#include <SPIFFS.h>
#include "Logic.h"
#include "Temperatures.h"
#include "Fans.h"
#include "Heaters.h"

void Logic::working_stream()
{
  logic_control.check_and_save_data_display_settings();
  logic_control.check_and_save_data_Fans();
  logic_control.check_and_save_data_heaters_settings();
}

/*
loads the saved settings in the SPIFFS for the fans.
the loaded settings are the control voltage and the on/off state of the fan
*/
void Logic::Load_Saved_Settings_Fans()
{ // loaded once in void setup ONLY!!!

  File saved_values_fans;
  saved_values_fans = SPIFFS.open("/values_fans.txt", "r");
  if (!saved_values_fans)
  {
    Serial.println("Failed to open file for reading");
    return;
  }
  Serial.print("Fan Settings: ");
  saved_settings_fans = saved_values_fans.readString();
  new_settings_fans = saved_settings_fans;
  saved_values_fans.close();
  Serial.println(new_settings_fans);
  StringSplitter *splitter = new StringSplitter(new_settings_fans, ',', 4); // new StringSplitter(string_to_split, delimiter, limit)
  String _fan1_0_10_voltage_input = splitter->getItemAtIndex(0);
  fan1_0_10_voltage_input = _fan1_0_10_voltage_input.toFloat();
  String _fan2_0_10_voltage_input = splitter->getItemAtIndex(1);
  fan2_0_10_voltage_input = _fan2_0_10_voltage_input.toFloat();
  String _f1_on_off_state = splitter->getItemAtIndex(2);
  String _f2_on_off_state = splitter->getItemAtIndex(3);
  f1_on_off_state = _f1_on_off_state.toInt();
  if (f1_on_off_state == true)
  {
    fans_control.turn_fan_1_on();
  }
  if (f1_on_off_state == false)
  {
    fans_control.turn_fan_1_off();
  }
  f2_on_off_state = _f2_on_off_state.toInt();
  if (f2_on_off_state == true)
  {
    fans_control.turn_fan_2_on();
  }
  if (f2_on_off_state == false)
  {
    fans_control.turn_fan_2_off();
  }
  old_settings_fans = new_settings_fans;
}
void Logic::check_and_save_data_Fans()
{ // check if there is a change in the fans setup and control voltage

  new_settings_fans = String(fan1_0_10_voltage_input, 1) + "," + String(fan2_0_10_voltage_input, 1) + "," + String(f1_on_off_state) + "," + String(f2_on_off_state) + ",";
  if (new_settings_fans != old_settings_fans)
  {
    Serial.println(new_settings_fans);
    File saved_values_fans;
    saved_values_fans = SPIFFS.open("/values_fans.txt", FILE_WRITE);
    if (saved_values_fans.print(new_settings_fans))
    {
      Serial.println("New settings for the fans have been successfully written to the internal memory");
    }
    else
    {
      Serial.println("File write for the fan settings failed");
    }
    old_settings_fans = new_settings_fans;
    saved_values_fans.close();
  }
} //end function
void Logic::load_saved_display_settings()
{
  File saved_values_display_settings;
  saved_values_display_settings = SPIFFS.open("/values_display_settings.txt", "r");
  if (!saved_values_display_settings)
  {
    Serial.println("Failed to open file for reading");
    return;
  }
  Serial.print("Display Settings: ");
  old_display_settings = saved_values_display_settings.readString();
  saved_values_display_settings.close();
  Serial.println(old_display_settings);
  StringSplitter *splitter = new StringSplitter(old_display_settings, ',', 6); // new StringSplitter(string_to_split, delimiter, limit)
                                                                               // read display brightness
  String _display_brightness = splitter->getItemAtIndex(0);
  display_brightness = _display_brightness.toInt();
  // read the auto ON/OFF display setting state
  String _display_auto_on_off_state = splitter->getItemAtIndex(1);
  display_auto_on_off_state = _display_auto_on_off_state.toInt();
  // read the set period for the screen sleep function
  String _auto_off_period = splitter->getItemAtIndex(2);
  auto_off_period = _auto_off_period.toInt();
  // read the screen lock display setting state
  String _display_screen_lock_on_off_state = splitter->getItemAtIndex(3);
  display_screen_lock_on_off_state = _display_screen_lock_on_off_state.toInt();
  // read the set screen lock period
  String _display_screen_lock_period = splitter->getItemAtIndex(4);
  display_auto_on_off_state = _display_auto_on_off_state.toInt();
  // read the saved PIN for the screen lock
  screen_lock_pin = splitter->getItemAtIndex(5);
  new_display_settings = old_display_settings;
}
void Logic::check_and_save_data_display_settings()
{ // check if there is a change in the display properties
  new_display_settings = String(display_brightness) + "," + String(display_auto_on_off_state) + "," + String(auto_off_period) + "," + String(display_screen_lock_on_off_state) + "," + String(display_screen_lock_period) + "," + String(screen_lock_pin);
  if (new_display_settings != old_display_settings)
  {
    Serial.println("New Display Settings detected " + new_display_settings);
    File saved_values_display_settings;
    saved_values_display_settings = SPIFFS.open("/values_display_settings.txt", FILE_WRITE);
    if (saved_values_display_settings.print(new_display_settings))
    {
      Serial.println("New settings for the display have been changed and successfully written to the internal memory");
    }
    else
    {
      Serial.println("File write for the fan settings failed");
    }
    saved_values_display_settings.close();
    old_display_settings = new_display_settings;
  }
} //end function
void Logic::load_saved_temperature_settings()
{
  File saved_values_temperature_settings;
  saved_values_temperature_settings = SPIFFS.open("/values_temp_settings.txt", "r");
  if (!saved_values_temperature_settings)
  {
    Serial.println("Failed to open temperature settings file for reading");
    return;
  }
  Serial.print("Temperature Settings: ");
  new_temperature_settings = saved_values_temperature_settings.readString();
  saved_values_temperature_settings.close();
  Serial.println(new_temperature_settings);
  StringSplitter *splitter = new StringSplitter(new_temperature_settings, ',', 4);
  String _threshhold_temperature = splitter->getItemAtIndex(0);
  String _turn_everything_off_temperature_threshold = splitter->getItemAtIndex(1);
  String _summer_mode_activated = splitter->getItemAtIndex(2);
  String _winter_mode_activated = splitter->getItemAtIndex(3);
  threshold_temperature = _threshhold_temperature.toInt();
  turn_everything_off_temperature_threshold = _turn_everything_off_temperature_threshold.toInt();
  summer_mode_activated = _summer_mode_activated.toInt();
  winter_mode_activated = _winter_mode_activated.toInt();
}
void Logic::check_and_save_data_temperature_settings()
{
  String _new_temperature_settings = new_temperature_settings;
  new_temperature_settings = String(turn_everything_off_temperature_threshold_saved) + "," + String(threshold_temperature_saved) + "," + String(summer_mode_activated) + "," + String(winter_mode_activated);
  if (_new_temperature_settings != new_temperature_settings)
  {
    Serial.println("New Temperature Settings detected: " + new_temperature_settings);
    File saved_values_temperature_settings;
    saved_values_temperature_settings = SPIFFS.open("/values_temp_settings.txt", FILE_WRITE);
    if (saved_values_temperature_settings.print(new_temperature_settings))
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
void Logic::load_saved_heaters_settings()
{
  File saved_values_heaters_settings;
  saved_values_heaters_settings = SPIFFS.open("/values_heaters_settings.txt", "r");
  if (!saved_values_heaters_settings)
  {
    Serial.println("Failed to open heaters settings file for reading");
    return;
  }
  Serial.print("Heaters Settings: ");
  new_heaters_settings = saved_values_heaters_settings.readString();
  saved_values_heaters_settings.close();
  Serial.print(new_heaters_settings);
  StringSplitter *splitter = new StringSplitter(new_heaters_settings, ',', 6);
  String _h1_power = splitter->getItemAtIndex(0);
  String _h2_power = splitter->getItemAtIndex(1);
  String _h3_power = splitter->getItemAtIndex(2);
  String _h1_available = splitter->getItemAtIndex(3);
  String _h2_available = splitter->getItemAtIndex(4);
  String _h3_available = splitter->getItemAtIndex(5);
  h1_power = _h1_power.toFloat();
  h2_power = _h2_power.toFloat();
  h3_power = _h3_power.toFloat();
  h1_available = _h1_available.toInt();
  h2_available = _h2_available.toInt();
  h3_available = _h3_available.toInt();
}
void Logic::check_and_save_data_heaters_settings()
{
  String _new_heaters_settings = new_heaters_settings;
  new_heaters_settings = String(h1_power) + "," + String(h2_power) + "," + String(h3_power) + "," + String(h1_available) + "," + String(h2_available) + "," + String(h3_available);
  if (_new_heaters_settings != new_heaters_settings)
  {
    Serial.println("New Heaters Settings detected: " + new_heaters_settings);
    File saved_values_heaters_settings;
    saved_values_heaters_settings = SPIFFS.open("/values_heaters_settings.txt", FILE_WRITE);
    if (saved_values_heaters_settings.print(new_heaters_settings))
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
bool Logic::turn_everything_off()
{
  if (T2 < turn_everything_off_temperature_threshold)
  {
    fans_control.turn_fans_off();
    heaters_control.turn_heaters_off();
    return true;
  }
  else
  {
    return false;
  }
}

Logic logic_control;
