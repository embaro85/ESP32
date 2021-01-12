#include <Arduino.h>
#include "definitions.h"
#include <StringSplitter.h>
#include <SPIFFS.h>
#include "Logic.h"
#include "Temperatures.h"

void Logic::Load_Saved_Settings_Fans()
{ // loaded once in void setup ONLY!!!

  File saved_values;
  saved_values = SPIFFS.open("/values.txt", "r");
  if (!saved_values)
  {
    Serial.println("Failed to open file for reading");
    return;
  }
  Serial.print("File Content: ");
  saved_settings = saved_values.readString();
  new_settings = saved_settings;
  saved_values.close();
  Serial.println(new_settings);
  StringSplitter *splitter = new StringSplitter(new_settings, ',', 4); // new StringSplitter(string_to_split, delimiter, limit)
  f1_voltage_string = splitter->getItemAtIndex(0);
  fan1_0_10_voltage_input = f1_voltage_string.toFloat();
  f2_voltage_string = splitter->getItemAtIndex(1);
  fan2_0_10_voltage_input = f2_voltage_string.toFloat();
  f1_on_off_state_string = splitter->getItemAtIndex(2);
  f2_on_off_state_string = splitter->getItemAtIndex(3);
  old_settings = new_settings;
}

void Logic::check_and_save_data()
{ // check if there is a change in the fans setup and control voltage

  new_settings = String(fan1_0_10_voltage_input, 1) + "," + String(fan2_0_10_voltage_input, 1) + "," + String(f1_on_off_state) + "," + String(f2_on_off_state) + ",";
  if (new_settings != old_settings)
  {
    Serial.println(new_settings);
    File saved_values;
    saved_values = SPIFFS.open("/values.txt", FILE_WRITE);
    if (saved_values.print(new_settings))
    {
      Serial.println("New settings have been successfully written to the internal memory");
    }
    else
    {
      Serial.println("File write failed");
    }
    saved_values.close();
    old_settings = new_settings;
  }
} //end function

/*void Logic::read_DS18B20_temperatures_core_0(void * parameter)
{

  for (;;)
  { // infinite loop

    // Turn the LED on
    temperatures_control.measure_temperatures();

    // Pause the task for 500ms
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}*/

Logic logic_control;
