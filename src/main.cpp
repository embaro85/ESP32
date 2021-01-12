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

void read_DS18B20_temperatures_core_0(void * parameter)
{

  for (;;)
  { // infinite loop

    // Turn the LED on
    temperatures_control.measure_temperatures();

    // Pause the task for 500ms
    vTaskDelay(500 / portTICK_PERIOD_MS);
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

    xTaskCreatePinnedToCore(
      read_DS18B20_temperatures_core_0, /* Function to implement the task */
      "Task1", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      0,  /* Priority of the task */
      &Task1,  /* Task handle. */
      0); /* Core where the task should run */

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

    temperatures_control.temp_sensor_begin(); // start the temperature sensors and assign addresses
    logic_control.Load_Saved_Settings_Fans(); //  Load the existing settings for the fans only

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


    /*A method for measuring the temperatures, setting up the display and populating the variables must be made*/
  
} // end void setup

void loop()
{
    time_in_millis = millis(); //needed for void checkTimeForExecution () must stay
    inData = "0";
    display_control.receive_data_from_display();
    logic_control.check_and_save_data();
    fan1_0_10_voltage_input = fans_control.fan1_control_voltage_up(f1_Nextion_Text_Field, fan1_0_10_voltage_input, f1_plus_cmd);
    fan1_0_10_voltage_input = fans_control.fan1_control_voltage_down(f1_Nextion_Text_Field, fan1_0_10_voltage_input, f1_minus_cmd);
    fans_control.fan1_control_on_off();
    fan2_0_10_voltage_input = fans_control.fan2_control_voltage_up(f2_Nextion_Text_Field, fan2_0_10_voltage_input, f2_plus_cmd);
    fan2_0_10_voltage_input = fans_control.fan2_control_voltage_down(f2_Nextion_Text_Field, fan2_0_10_voltage_input, f2_minus_cmd);
    fans_control.fan2_control_on_off();
    display_control.Refresh_Fans_Screen(f1_Nextion_Text_Field, fan1_0_10_voltage_input, f2_Nextion_Text_Field, fan2_0_10_voltage_input, ref_fans_screen_cmd);
    heaters_control.heaters_temperature_contol();
    heaters_control.heaters_manual_control();
    display_control.menu_navigation_Nextion();
    if (inData == "info")
    {
        Serial.println("Heater1 state is: " + String(heater1_on_off_state));
        Serial.println("Manual control is : " + String(h_manual_control_state_new));
        Serial.println("new_state_h1 : " + String(new_state_h1));
        



    }

  

    //check_time_for_execution(); //Measure the time needed to process everything once

} // end void loop
