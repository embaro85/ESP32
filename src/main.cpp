/*
  Version 0.1
  Created 23-12-2020
  A program for controlling a AHU with 2 fans, 3 sections heater, 0-10V controll of two fans and a single valve, measuring up to
  6 temperatures. four free programable OUTPUTS (can be used as INPUTS by manipulating the channel transistor).
  Upload Settings for ESP32:
  Board: ESP32  Dev Module
  Upload Speed - 921600
  CPU Frequency 240MHz (WiFi/BT)
  Flash Frequency 80MHz
  Flash Mode - QIO
  Flash Size - 4MB (32Mb)
  Partition Scheme - Minimal SPIFFS (1.9MB APP with OTA/190KB SPIFFS
  Debug Level - none
  PSRAM - Disabled
*/
#include <Arduino.h>
#include <Logic.h>
#include <SPIFFS.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "definitions.h"
#include "Display.h"
#include "Fans.h"
#include "Temperatures.h"
#include "Heaters.h"
#include "Logic.h"
#include "Nextion_commands.h"
#include "Settings.h"
#include "Overview.h"
#include "Temperature_settings.h"

void read_DS18B20_temperatures_core_0(void *parameter)
{

  for (;;)
  {
    temperatures_control.measure_temperatures();
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

TaskHandle_t Task1;

void setup()
{

  Serial.begin(115200);
  //Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial2.begin(115200, SERIAL_8N1, 17, 16); //there is a mistake in the circuit
  //in the Nextion editor in Preinitialize Event - input: baud=115200
  Serial2.setTimeout(100);
  temperatures_control.temp_sensor_begin(); // start the temperature sensors and assign addresses

  xTaskCreatePinnedToCore(
      read_DS18B20_temperatures_core_0, /* Function to implement the task */
      "Task1",                          /* Name of the task */
      10000,                            /* Stack size in words */
      NULL,                             /* Task input parameter */
      0,                                /* Priority of the task */
      &Task1,                           /* Task handle. */
      0);                               /* Core where the task should run */

  // configure the PWM of FAN1
  ledcSetup(fan_1_PWM_Channel, fan_1_PWM_frequency, fan_1_PWM_resolution);
  ledcAttachPin(fan_1_PWM_pin, fan_1_PWM_Channel);

  // configure the PWM of FAN2
  ledcSetup(fan_2_PWM_Channel, fan_2_PWM_frequency, fan_2_PWM_resolution);
  ledcAttachPin(fan_2_PWM_pin, fan_2_PWM_Channel); //!!!!!! check the channel

  // configure the PWM of VALVE1
  ledcSetup(valve_1_PWM_Channel, valve_1_PWM_frequency, valve_1_PWM_resolution);
  ledcAttachPin(valve_1_PWM_pin, valve_1_PWM_Channel); //!!!!!! check the channel

  if (!SPIFFS.begin(true))
  { // start SPIFFS
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  else
  {
    Serial.println("SPIFFS successfully loaded");
  }
  delay(100);
  nextion_commands.set_visibility_on_Nextion("t2", 0);
  nextion_commands.set_visibility_on_Nextion("b11", 0);

  pinMode(FP1, OUTPUT);
  pinMode(FP2, OUTPUT);
  pinMode(FP3, OUTPUT);
  pinMode(FP4, OUTPUT);
  pinMode(F1, OUTPUT);
  pinMode(F2, OUTPUT);
  pinMode(H1, OUTPUT);
  pinMode(H2, OUTPUT);
  pinMode(H3, OUTPUT);
  pinMode(fan_1_PWM_pin, OUTPUT);
  pinMode(fan_2_PWM_pin, OUTPUT);
  pinMode(valve_1_PWM_pin, OUTPUT);
  pinMode(Pressure1, INPUT_PULLDOWN);
  pinMode(Pressure2, INPUT_PULLDOWN);

  digitalWrite(FP1, LOW);
  digitalWrite(FP2, LOW);
  digitalWrite(FP3, LOW);
  digitalWrite(FP4, LOW);
  digitalWrite(F1, LOW);
  digitalWrite(F2, LOW);
  digitalWrite(H1, LOW);
  digitalWrite(H2, LOW);
  digitalWrite(H3, LOW);

  logic_control.Load_Saved_Settings_Fans();    //  Load the existing settings for the fans only
  logic_control.load_saved_display_settings(); //load the existing settings for the display only
  logic_control.load_saved_temperature_settings();
  logic_control.load_saved_heaters_settings();
} // end void setup

void loop()
{
  
  time_in_millis = millis(); //needed for void checkTimeForExecution () must stay
  inData = "0";
  nextion_commands.receive_data_from_display();
  fan1_0_10_voltage_input = fans_control.fan1_control_voltage_up(f1_Nextion_Text_Field, fan1_0_10_voltage_input, f1_plus_cmd);
  fan1_0_10_voltage_input = fans_control.fan1_control_voltage_down(f1_Nextion_Text_Field, fan1_0_10_voltage_input, f1_minus_cmd);
  fans_control.fan1_control_on_off();
  fan2_0_10_voltage_input = fans_control.fan2_control_voltage_up(f2_Nextion_Text_Field, fan2_0_10_voltage_input, f2_plus_cmd);
  fan2_0_10_voltage_input = fans_control.fan2_control_voltage_down(f2_Nextion_Text_Field, fan2_0_10_voltage_input, f2_minus_cmd);
  fans_control.fan2_control_on_off();
  heaters_control.heaters_temperature_contol();
  heaters_control.heaters_manual_control();
  display_control.working_stream();
  logic_control.working_stream();
  temperatures_control.working_stream(); 
  settings_control.working_stream();
  overview_control.working_stream();
  heaters_control.working_stream();
  temperature_settings_control.working_stream();
  if (inData == "info")
  {
    Serial.println("Heater1 state is: " + String(heater1_on_off_state));
    Serial.println("Manual control is : " + String(h_manual_control_state_new));
    Serial.println("new_state_h1 : " + String(new_state_h1));
  }

  //Serial.println(outData);
  //Serial.println(on_page_15);

} // end void loop
