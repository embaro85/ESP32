#include "definitions.h"
#include "Temperatures.h"
#include "Display.h"
#include "Heaters.h"
#include <Arduino.h>
#include <DallasTemperature.h>
#include <OneWire.h>

DeviceAddress device_0, device_1, device_2, device_3, device_4, device_5;
OneWire oneWire(temp_bus);           // Setup a oneWire instance to communicate with any OneWire devices
DallasTemperature DS18B20(&oneWire); // Pass our oneWire reference to Dallas Temperature sensor

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
            outData = "Temperatures1.tt1.txt=\"" + String(T_1, 1) + "\"";
            display_control.sendDataToDisplay();
        }
        else if (temperature_sensor == 2)
        {
            DS18B20.requestTemperaturesByIndex(1);
            T_2 = DS18B20.getTempCByIndex(1);
            //    Serial.println("Temperature sensor " + String(temperature_sensor) + " reading is: " + String(T_2, 1) + "°C");
            temperature_sensor++;
            outData = "Temperatures1.tt2.txt=\"" + String(T_2, 1) + "\"";
            display_control.sendDataToDisplay();
        }
        else if (temperature_sensor == 3)
        {
            DS18B20.requestTemperaturesByIndex(2);

            T_3 = DS18B20.getTempCByIndex(2);
            //    Serial.println("Temperature sensor " + String(temperature_sensor) + " reading is: " + String(T_3, 1) + "°C");
            temperature_sensor++;
            outData = "Temperatures2.tt3.txt=\"" + String(T_3, 1) + "\"";
            display_control.sendDataToDisplay();
        }
        else if (temperature_sensor == 4)
        {
            DS18B20.requestTemperaturesByIndex(3);

            T_4 = DS18B20.getTempCByIndex(3);
            //   Serial.println("Temperature sensor " + String(temperature_sensor) + " reading is: " + String(T_4, 1) + "°C");
            temperature_sensor = 1;
            outData = "Temperatures2.tt4.txt=\"" + String(T_4, 1) + "\"";
            display_control.sendDataToDisplay();
        }
    }
}

Temperatures temperatures_control;
