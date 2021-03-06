#include "definitions.h"
#include "Temperatures.h"
#include "Display.h"
#include "Heaters.h"
#include "Nextion_commands.h"
#include "Logic.h"
#include <Arduino.h>
#include <DallasTemperature.h>
#include <OneWire.h>

DeviceAddress device_0, device_1, device_2, device_3, device_4, device_5;
OneWire oneWire(temp_bus);           // Setup a oneWire instance to communicate with any OneWire devices
DallasTemperature DS18B20(&oneWire); // Pass our oneWire reference to Dallas Temperature sensor

void Temperatures::working_stream()
{
    temperatures_control.save_temperature_settings_heaters_control();
    temperatures_control.save_temperature_settings_turn_everything_on_off();
    temperatures_control.refresh_screen();
    temperatures_control.exit_page();
}

void printAddress(DeviceAddress deviceAddress)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        // zero pad the address if necessary
        if (deviceAddress[i] < 16)
            Serial.print("0");
        Serial.print(deviceAddress[i], HEX);
    }
}

void Temperatures::temp_sensor_begin()
{

    DS18B20.begin(); // Start the DS18B20 sensor

    if (!DS18B20.getAddress(device_0, 0))
    {
        Serial.println("Unable to locate Device 1");
    }

    if (!DS18B20.getAddress(device_1, 1))
    {
        Serial.println("Unable to locate Device 2");
    }
    if (!DS18B20.getAddress(device_2, 2))
    {
        Serial.println("Unable to locate Device 3");
    }
    if (!DS18B20.getAddress(device_3, 3))
    {
        Serial.println("Unable to locate Device 4");
    }
    if (!DS18B20.getAddress(device_4, 4))
    {
        Serial.println("Unable to locate Device 5");
    }
    if (!DS18B20.getAddress(device_5, 5))
    {
        Serial.println("Unable to locate Device 6");
    }
    DS18B20.setResolution(device_0, DS18B20_PRECISION); // set the resolution to 9 bit per device
    DS18B20.setResolution(device_1, DS18B20_PRECISION); // set the resolution to 9 bit per device
    DS18B20.setResolution(device_2, DS18B20_PRECISION); // set the resolution to 9 bit per device
    DS18B20.setResolution(device_3, DS18B20_PRECISION); // set the resolution to 9 bit per device
    DS18B20.setResolution(device_4, DS18B20_PRECISION); // set the resolution to 9 bit per device
    DS18B20.setResolution(device_5, DS18B20_PRECISION); // set the resolution to 9 bit per device
    /*Serial.print("Found ");
    Serial.print(devCount);
    Serial.println(" devices.");*/

    Serial.print("Device 0 Address: ");
    printAddress(device_0);
    Serial.println();

    Serial.print("Device 1 Address: ");
    printAddress(device_1);
    Serial.println();

    Serial.print("Device 2 Address: ");
    printAddress(device_2);
    Serial.println();

    Serial.print("Device 3 Address: ");
    printAddress(device_3);
    Serial.println();

    Serial.print("Device 4 Address: ");
    printAddress(device_4);
    Serial.println();

    Serial.print("Device 5 Address: ");
    printAddress(device_5);
    Serial.println();

    Serial.print("Device 0 Resolution: ");
    Serial.print(DS18B20.getResolution(device_0), DEC);
    Serial.println();

    Serial.print("Device 1 Resolution: ");
    Serial.print(DS18B20.getResolution(device_1), DEC);
    Serial.println();

    Serial.print("Device 2 Resolution: ");
    Serial.print(DS18B20.getResolution(device_2), DEC);
    Serial.println();

    Serial.print("Device 3 Resolution: ");
    Serial.print(DS18B20.getResolution(device_3), DEC);
    Serial.println();

    Serial.print("Device 4 Resolution: ");
    Serial.print(DS18B20.getResolution(device_4), DEC);
    Serial.println();

    Serial.print("Device 5 Resolution: ");
    Serial.print(DS18B20.getResolution(device_5), DEC);
    Serial.println();
}

void Temperatures::measure_temperatures()
{
    if (millis() > timer1 + temp_measure_interval)
    {
        timer1 = millis();
        if (temperature_sensor == 1)
        {
            DS18B20.requestTemperaturesByIndex(0);
            T_1 = DS18B20.getTempCByIndex(0);
            //      Serial.println("Temperature sensor " + String(temperature_sensor) + " reading is: " + String(T_1, 1) + "°C");
            temperature_sensor++;
        }
        else if (temperature_sensor == 2)
        {
            DS18B20.requestTemperaturesByIndex(1);
            T_2 = DS18B20.getTempCByIndex(1);
            //    Serial.println("Temperature sensor " + String(temperature_sensor) + " reading is: " + String(T_2, 1) + "°C");
            temperature_sensor++;
        }
        else if (temperature_sensor == 3)
        {
            DS18B20.requestTemperaturesByIndex(2);

            T_3 = DS18B20.getTempCByIndex(2);
            //    Serial.println("Temperature sensor " + String(temperature_sensor) + " reading is: " + String(T_3, 1) + "°C");
            temperature_sensor++;
        }
        else if (temperature_sensor == 4)
        {
            DS18B20.requestTemperaturesByIndex(3);

            T_4 = DS18B20.getTempCByIndex(3);
            //   Serial.println("Temperature sensor " + String(temperature_sensor) + " reading is: " + String(T_4, 1) + "°C");
            temperature_sensor = 1;
        }
    }
}

uint8_t Temperatures::set_threshold_temperature_for_heaters_control()
{
    if (inData == p10_b5_command)
    {
        threshold_temperature++;
    }
    if (inData == p10_b6_command && threshold_temperature > 2)
    {
        threshold_temperature--;
    }
    return threshold_temperature;
}

uint8_t Temperatures::set_everything_off_threshold_temperature()
{
    if (inData == p10_b1_command)
    {
        turn_everything_off_temperature_threshold++;
    }
    if (inData == p10_b0_command && turn_everything_off_temperature_threshold > 2)
    {
        turn_everything_off_temperature_threshold--;
    }
    return turn_everything_off_temperature_threshold;
}

boolean Temperatures::handle_threshold_temperature()
{
    uint8_t _threshold_temperature = threshold_temperature;
    temperatures_control.set_threshold_temperature_for_heaters_control();
    if (_threshold_temperature != threshold_temperature)
    {
        return false;
    }
}

boolean Temperatures::handle_everything_off_threshold_temperature()
{
    uint8_t _turn_everything_off_temperature_threshold = turn_everything_off_temperature_threshold;
    temperatures_control.set_everything_off_threshold_temperature();
    if (_turn_everything_off_temperature_threshold != turn_everything_off_temperature_threshold)
    {
        return false;
    }
}

void Temperatures::hide_start_info_text_t0()
{
    if (inData == p10_b2_command)
    {
        nextion_commands.set_visibility_on_Nextion("t0", 0);
    }
}

void Temperatures::save_temperature_settings_heaters_control()
{
    if (inData == p10_b3_command)
    {
        turn_everything_off_temperature_threshold_saved = turn_everything_off_temperature_threshold;
        threshold_temperature_saved = threshold_temperature;
        logic_control.check_and_save_data_temperature_settings();
        nextion_commands.set_visibility_on_Nextion("t8", 1);
        delay(2000);
        nextion_commands.set_visibility_on_Nextion("t8", 0);
        nextion_commands.go_to_page_Nextion(1);
    }
}

void Temperatures::save_temperature_settings_turn_everything_on_off()
{
    if (inData == p10_b2_command)
    {
        turn_everything_off_temperature_threshold_saved = turn_everything_off_temperature_threshold;
        threshold_temperature_saved = threshold_temperature;
        logic_control.check_and_save_data_temperature_settings();
        nextion_commands.set_visibility_on_Nextion("t8", 1);
        delay(2000);
        nextion_commands.set_visibility_on_Nextion("t8", 0);
        nextion_commands.go_to_page_Nextion(1);
    }
}

void Temperatures::refresh_screen()
{
    if (millis() > (2000 + timer3) && on_page_4 == true)
    {
        timer3 = millis();
        nextion_commands.set_text_of_screen_component(p4_tt1, String(T_1, 1));
        nextion_commands.set_text_of_screen_component(p4_tt2, String(T_2, 1));
        nextion_commands.set_text_of_screen_component(p4_tt3, String(T_3, 1));
        nextion_commands.set_text_of_screen_component(p4_tt4, String(T_4, 1));
    }
}

void Temperatures::exit_page()
{
    if (inData == p4_b2_command)
    {
        on_page_4 = false;
        nextion_commands.go_to_page_Nextion(1);
    }
}

Temperatures temperatures_control;
