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

/*
T_1 - extract air
T_2 - supply air
T_3 - ambient air
T_4 - exhaust air
T_5 - valve temperature
*/

void Temperatures::working_stream()
{
    temperatures_control.refresh_screen();
    temperatures_control.commands_from_display();
    temperatures_control.calculate_heat_exchanger_efficiency();
}

void printAddress(DeviceAddress deviceAddress)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        // zero pad the address if necessary
        /* if (deviceAddress[i] < 16)
            Serial.print("0");*/
        Serial.print(deviceAddress[i]);
    }
}
void Temperatures::temp_sensor_begin() //start and define thr DS18B20 temperature sensors
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
    /* if (!DS18B20.getAddress(device_4, 4))
    {
        Serial.println("Unable to locate Device 5");
    }
    if (!DS18B20.getAddress(device_5, 5))
    {
        Serial.println("Unable to locate Device 6");
    }*/
    DS18B20.setResolution(device_0, DS18B20_PRECISION); // set the resolution to 9 bit per device
    DS18B20.setResolution(device_1, DS18B20_PRECISION); // set the resolution to 9 bit per device
    DS18B20.setResolution(device_2, DS18B20_PRECISION); // set the resolution to 9 bit per device
    DS18B20.setResolution(device_3, DS18B20_PRECISION); // set the resolution to 9 bit per device
    //DS18B20.setResolution(device_4, DS18B20_PRECISION); // set the resolution to 9 bit per device
    // DS18B20.setResolution(device_5, DS18B20_PRECISION); // set the resolution to 9 bit per device

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

    /* Serial.print("Device 4 Address: ");
    printAddress(device_4);
    Serial.println();*/

    /*Serial.print("Device 5 Address: ");
    printAddress(device_5);
    Serial.println();*/

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

    /*Serial.print("Device 4 Resolution: ");
    Serial.print(DS18B20.getResolution(device_4), DEC);
    Serial.println();*/

    /* Serial.print("Device 5 Resolution: ");
    Serial.print(DS18B20.getResolution(device_5), DEC);
    Serial.println();*/
}
void Temperatures::measure_temperatures() //the measurement of the temperatures is performed here. It works constantly on core 1
{
    if (millis() > timer1 + temp_measure_interval)
    {
        timer1 = millis();
        /* if (temperature_sensor == 1)
        {

            DS18B20.requestTemperaturesByIndex(extract_air_temperature_device_index);
            T_1 = DS18B20.getTempCByIndex(extract_air_temperature_device_index);
            temperature_sensor++;
        }
        else if (temperature_sensor == 2)
        {
            DS18B20.requestTemperaturesByIndex(supply_air_temperature_device_index);
            T_2 = DS18B20.getTempCByIndex(supply_air_temperature_device_index);
            temperature_sensor++;
        }
        else if (temperature_sensor == 3)
        {
            DS18B20.requestTemperaturesByIndex(ambient_air_temperature_device_index);

            T_3 = DS18B20.getTempCByIndex(ambient_air_temperature_device_index);
            temperature_sensor++;
        }
        else if (temperature_sensor == 4)
        {
            DS18B20.requestTemperaturesByIndex(exhaust_air_temperature_device_index);

            T_4 = DS18B20.getTempCByIndex(exhaust_air_temperature_device_index);
            temperature_sensor = 1;
        }
    }*/
        DS18B20.requestTemperatures();
        if (!DS18B20.getTempCByIndex(extract_air_temperature_device_index))
        {
            Serial.println("Error reading extract air temperature sensor");
        }
        if (!DS18B20.getTempCByIndex(supply_air_temperature_device_index))
        {
            Serial.println("Error reading supply air temperature sensor");
        }
        if (!DS18B20.getTempCByIndex(ambient_air_temperature_device_index))
        {
            Serial.println("Error reading ambient air temperature sensor");
        }
        if (!DS18B20.getTempCByIndex(exhaust_air_temperature_device_index))
        {
            Serial.println("Error reading exhaust air temperature sensor");
        }

        T_1 = DS18B20.getTempCByIndex(extract_air_temperature_device_index);
        T_2 = DS18B20.getTempCByIndex(supply_air_temperature_device_index);
        T_3 = DS18B20.getTempCByIndex(ambient_air_temperature_device_index);
        T_4 = DS18B20.getTempCByIndex(exhaust_air_temperature_device_index);
        //Serial.println ("temperatures read");
        //delay(100);
    }
}
void Temperatures::refresh_screen()
{
    if (millis() > (2000 + timer3) && on_page_number == Temperatures_4)
    {
        timer3 = millis();
        nextion_commands.set_text_of_screen_component(p4_tt1, String(T_1, 1));
        nextion_commands.set_text_of_screen_component(p4_tt2, String(T_2, 1));
        nextion_commands.set_text_of_screen_component(p4_tt3, String(T_3, 1));
        nextion_commands.set_text_of_screen_component(p4_tt4, String(T_4, 1));
    }
}
void Temperatures::commands_from_display()
{
    if (inData == p4_b2_command)
    {
        //on_page_4 = false;
        nextion_commands.on_page(1);
        nextion_commands.go_to_page_Nextion(1);
        //on_page_1 = true;
    }
}
float Temperatures::calculate_heat_exchanger_efficiency() //calculates the efficiency of the heat exchanger
{
    heat_exchanger_efficiency = ((T_1 - T_3) / (T_2 - T_3)) * 100;
    return heat_exchanger_efficiency;
}
void Temperatures::extract_air_temperature_sensors() //check the DS18B20 address and assign it as extract air temperature sensor
{
    for (int j = 0; j < 8; j++)
    {

        device_0_address = device_0_address + String(device_0[j]);
    }
    for (int j = 0; j < 8; j++)
    {

        device_1_address = device_1_address + String(device_1[j]);
    }
    for (int j = 0; j < 8; j++)
    {

        device_2_address = device_2_address + String(device_2[j]);
    }
    for (int j = 0; j < 8; j++)
    {

        device_3_address = device_3_address + String(device_3[j]);
    }

    for (byte i = 0; i < 4; i++)
    {
        if (device_0_address == extract_air_temperature_sensor_address[i])
        {
            Serial.println("Extract air sensor address is:" + String(device_0_address));
            extract_air_temperature_device_index = 0;
        }
    }
    for (byte i = 0; i < 4; i++)
    {
        if (device_1_address == extract_air_temperature_sensor_address[i])
        {
            Serial.println("Extract air sensor address is:" + String(device_1_address));
            extract_air_temperature_device_index = 1;
        }
    }
    for (byte i = 0; i < 4; i++)
    {
        if (device_2_address == extract_air_temperature_sensor_address[i])
        {
            Serial.println("Extract air sensor address is:" + String(device_2_address));
            extract_air_temperature_device_index = 2;
        }
    }
    for (byte i = 0; i < 4; i++)
    {
        if (device_3_address == extract_air_temperature_sensor_address[i])
        {
            Serial.println("Extract air sensor address is:" + String(device_3_address));
            extract_air_temperature_device_index = 3;
        }
    }
}
void Temperatures::supply_air_temperature_sensors() //check the DS18B20 address and assign it as supply air temperature sensor
{
    for (byte i = 0; i < 4; i++)
    {
        if (device_0_address == supply_air_temperature_sensor_address[i])
        {
            Serial.println("Supply air sensor address is:" + String(device_0_address));
            supply_air_temperature_device_index = 0;
        }
    }
    for (byte i = 0; i < 4; i++)
    {
        if (device_1_address == supply_air_temperature_sensor_address[i])
        {
            Serial.println("Supply air sensor address is:" + String(device_1_address));
            supply_air_temperature_device_index = 1;
        }
    }
    for (byte i = 0; i < 4; i++)
    {
        if (device_2_address == supply_air_temperature_sensor_address[i])
        {
            Serial.println("Supply air sensor address is:" + String(device_2_address));
            supply_air_temperature_device_index = 2;
        }
    }
    for (byte i = 0; i < 4; i++)
    {
        if (device_3_address == supply_air_temperature_sensor_address[i])
        {
            Serial.println("Supply air sensor address is:" + String(device_3_address));
            supply_air_temperature_device_index = 3;
        }
    }
}
void Temperatures::ambient_air_temperature_sensors() //check the DS18B20 address and assign it as ambient air temperature sensor
{
    for (byte i = 0; i < 4; i++)
    {
        if (device_0_address == ambient_air_temperature_sensor_address[i])
        {
            Serial.println("Ambient air sensor address is:" + String(device_0_address));
            ambient_air_temperature_device_index = 0;
        }
    }
    for (byte i = 0; i < 4; i++)
    {
        if (device_1_address == ambient_air_temperature_sensor_address[i])
        {
            Serial.println("Ambient air sensor address is:" + String(device_1_address));
            ambient_air_temperature_device_index = 1;
        }
    }
    for (byte i = 0; i < 4; i++)
    {
        if (device_2_address == ambient_air_temperature_sensor_address[i])
        {
            Serial.println("Ambient air sensor address is:" + String(device_2_address));
            ambient_air_temperature_device_index = 2;
        }
    }
    for (byte i = 0; i < 4; i++)
    {
        if (device_3_address == ambient_air_temperature_sensor_address[i])
        {
            Serial.println("Ambient air sensor address is:" + String(device_3_address));
            ambient_air_temperature_device_index = 3;
        }
    }
}
void Temperatures::exhaust_air_temperature_sensors() //check the DS18B20 address and assign it as exhaust air temperature sensor
{
    for (byte i = 0; i < 4; i++)
    {
        if (device_0_address == exhaust_air_temperature_sensor_address[i])
        {
            Serial.println("Exhaust air sensor address is:" + String(device_0_address));
            exhaust_air_temperature_device_index = 0;
        }
    }
    for (byte i = 0; i < 4; i++)
    {
        if (device_1_address == exhaust_air_temperature_sensor_address[i])
        {
            Serial.println("Exhaust air sensor address is:" + String(device_1_address));
            exhaust_air_temperature_device_index = 1;
        }
    }
    for (byte i = 0; i < 4; i++)
    {
        if (device_2_address == exhaust_air_temperature_sensor_address[i])
        {
            Serial.println("Exhaust air sensor address is:" + String(device_2_address));
            exhaust_air_temperature_device_index = 2;
        }
    }
    for (byte i = 0; i < 4; i++)
    {
        if (device_3_address == exhaust_air_temperature_sensor_address[i])
        {
            Serial.println("Exhaust air sensor address is:" + String(device_3_address));
            exhaust_air_temperature_device_index = 3;
        }
    }
}

Temperatures temperatures_control;
