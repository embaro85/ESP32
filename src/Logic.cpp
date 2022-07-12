#include <Arduino.h>
#include "definitions.h"
#include <StringSplitter.h>
#include <SPIFFS.h>
#include "Logic.h"
#include "Temperatures.h"
#include "Fans.h"
#include "Heaters.h"
#include "Nextion_commands.h"
#include "Heater_settings.h"
#include "Dampers.h"
#include "Temperature_settings.h"

void Logic::working_stream()
{
  logic_control.check_and_save_data_display_settings();
  logic_control.alarms();
  logic_control.commands_from_display();
  logic_control.alarms_page();
}

void Logic::alarms()
{
  filter_1_raw_value = analogRead(Pressure1);
  filter_2_raw_value = analogRead(Pressure2);
  if (millis() > (timer8 + 5000))
  {
    if (T_3 <= 4 || (filter_1_raw_value > 200) || (filter_2_raw_value > 200))
    {
      if (on_page_number == Start_page_1)
      {
        nextion_commands.set_visibility_on_Nextion(p1_b5_visibility, 1);
      }
      alarm_button_new_state = true;
      if (alarm_button_new_state != alarm_button_last_state)
      {
        alarm_button_last_state = alarm_button_new_state;
      }
      if (T_3 < 4)
      {
        too_low_ambient_temperature = true;
      }
      if (filter_1_raw_value > 200)
      {
        clogged_filter_1 = true;
      }
      if (filter_2_raw_value > 200)
      {
        clogged_filter_2 = true;
      }
    }
    if (T_3 > 4)
    {
      too_low_ambient_temperature = false;
    }
    if (filter_1_raw_value < 200)
    {
      clogged_filter_1 = false;
    }
    if (filter_2_raw_value < 200)
    {
      clogged_filter_2 = false;
    }
    if (T_3 > 4 && filter_1_raw_value < 200 && filter_2_raw_value < 200)
    {
      clogged_filter_1 = false;
      clogged_filter_2 = false;
      too_low_ambient_temperature = false;
      alarm_button_new_state = false;
    }
    if (alarm_button_new_state != alarm_button_last_state)
    {
      alarm_button_last_state = alarm_button_new_state;
      nextion_commands.set_visibility_on_Nextion(p1_b5_visibility, 0);
    }
    timer8 = millis();
  }
}

void Logic::alarms_page()
{
  if (on_page_number == alarm_list_21 && millis() > (timer9 + 5000))
  {
    if (clogged_filter_1 == true)
    {
      alarm_message = alarm_message + "Филтър подаваща линия запушен\\r";
      Serial.println(filter_1_raw_value);
    }
    if (clogged_filter_2 == true)
    {
      alarm_message = alarm_message + "Филтър външен въздух запушен\\r";
      Serial.println(filter_2_raw_value);
    }
    if (too_low_ambient_temperature == true)
    {
      alarm_message = alarm_message + "Hиска външна температура\\r";
    }
    nextion_commands.set_text_of_screen_component(p21_t1, alarm_message);
    alarm_message = "";
    timer9 = millis();
  }
}

void Logic::commands_from_display()
{
  if (inData == p21_b4_command_2101)
  {
    if (screen_lock_on == false)
    {
      nextion_commands.on_page(1);
      nextion_commands.go_to_page_Nextion(1);
    }
    if (screen_lock_on == true)
    {
      screen_loaded = false;
      nextion_commands.on_page(24);
      nextion_commands.go_to_page_Nextion(24);
    }
  }
}
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
  String _display_auto_off = splitter->getItemAtIndex(1);
  display_auto_off = _display_auto_off.toInt();
  // read the set period for the screen sleep function
  String _auto_off_period = splitter->getItemAtIndex(2);
  display_auto_off_period = _auto_off_period.toInt();
  // read the screen lock display setting state
  String _screen_lock_on = splitter->getItemAtIndex(3);
  screen_lock_on = _screen_lock_on.toInt();
  // read the saved PIN for the screen lock
  screen_lock_pin = splitter->getItemAtIndex(4);
  new_display_settings = old_display_settings;
}
void Logic::check_and_save_data_display_settings()
{ // check if there is a change in the display properties
  new_display_settings = String(display_brightness) + "," + String(display_auto_off) + "," + String(display_auto_off_period) + "," + String(screen_lock_on) + "," + String(screen_lock_pin);
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
void Logic::turn_unit_on() // loads the saved settings for all of the equipment
{
  timer16 = millis(); // time since the start of the unit
  dampers_control.load_settings();
  fans_control.Load_Saved_Settings_Fans();     //  Load the existing settings for the fans only
  logic_control.load_saved_display_settings(); //load the existing settings for the display only
  heaters_settings_control.load_heaters_settings_p14();
  heaters_control.load_manual_settings_p3();
  heaters_settings_control.load_saved_settings_heater1();
  heaters_settings_control.load_saved_settings_heater2();
  heaters_settings_control.load_saved_settings_heater3();
  temperature_settings_control.load_settings();
  temperatures_control.extract_air_temperature_sensors();
  temperatures_control.supply_air_temperature_sensors();
  temperatures_control.ambient_air_temperature_sensors();
  temperatures_control.exhaust_air_temperature_sensors();
}

Logic logic_control;
