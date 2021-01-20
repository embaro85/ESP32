#include <Arduino.h>
#include "definitions.h"
#include <StringSplitter.h>
#include <SPIFFS.h>
#include "Logic.h"
#include "Temperatures.h"

/*
loads the saved settings in the SPIFFS for the fans.
the loaded settings are the control voltage and the on/off state of the fan
*/
void Logic::Load_Saved_Settings_Fans()
{ // loaded once in void setup ONLY!!!

  File saved_values_fans;
  saved_values_fans = SPIFFS.open("/values.txt", "r");
  if (!saved_values_fans)
  {
    Serial.println("Failed to open file for reading");
    return;
  }
  Serial.print("File Content: ");
  saved_settings_fans = saved_values_fans.readString();
  new_settings_fans = saved_settings_fans;
  saved_values_fans.close();
  Serial.println(new_settings_fans);
  StringSplitter *splitter = new StringSplitter(new_settings_fans, ',', 4); // new StringSplitter(string_to_split, delimiter, limit)
  f1_voltage_string = splitter->getItemAtIndex(0);
  fan1_0_10_voltage_input = f1_voltage_string.toFloat();
  f2_voltage_string = splitter->getItemAtIndex(1);
  fan2_0_10_voltage_input = f2_voltage_string.toFloat();
  f1_on_off_state_string = splitter->getItemAtIndex(2);
  f2_on_off_state_string = splitter->getItemAtIndex(3);
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
    saved_values_fans.close();
    old_settings_fans = new_settings_fans;
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
  Serial.print("File Content: ");
  old_display_settings = saved_values_display_settings.readString();
  saved_values_display_settings.close();
  Serial.println(old_display_settings);
  StringSplitter *splitter = new StringSplitter(old_display_settings, ',', 6); // new StringSplitter(string_to_split, delimiter, limit)
                                                                               // read display brightness
  display_brightness_string = splitter->getItemAtIndex(0);
  display_brightness = display_brightness_string.toInt();
// read the auto ON/OFF display setting state
  display_auto_on_off_state_string = splitter->getItemAtIndex(1);
  display_auto_on_off_state = display_auto_on_off_state_string.toInt();
// read the set period for the screen sleep function 
  auto_off_period_string = splitter->getItemAtIndex(2);
  auto_off_period = auto_off_period_string.toInt();
// read the screen lock display setting state 
  display_screen_lock_on_off_state_string = splitter->getItemAtIndex(3);
  display_screen_lock_on_off_state = display_screen_lock_on_off_state_string.toInt();
// read the set screen lock period 
  display_screen_lock_period_string = splitter->getItemAtIndex(4);
  display_auto_on_off_state = display_auto_on_off_state_string.toInt();
// read the saved PIN for the screen lock
  screen_lock_pin_string = splitter->getItemAtIndex(5);
  screen_lock_pin = screen_lock_pin_string.toInt();

  new_display_settings = old_display_settings;
}
void Logic::check_and_save_data_display_settings()
{ // check if there is a change in the display properties

  new_display_settings = String(display_brightness) + "," + String(display_auto_on_off_state) + "," + String(auto_off_period) + "," + String(display_screen_lock_on_off_state) + "," + String(display_screen_lock_period) + "," + String(screen_lock_pin) + ",";
  if (new_display_settings != old_display_settings)
  {
    Serial.println(new_display_settings);
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

Logic logic_control;
