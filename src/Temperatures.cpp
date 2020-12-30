#include "definitions.h"
#include "Temperatures.h"
#include "Display.h"
#include <Arduino.h>
#include <DallasTemperature.h>
#include <OneWire.h>

DeviceAddress device_0, device_1, device_2, device_3, device_4, device_5;
OneWire oneWire(temp_bus);           // Setup a oneWire instance to communicate with any OneWire devices
DallasTemperature DS18B20(&oneWire); // Pass our oneWire reference to Dallas Temperature sensor

void Temperatures::printAddress(DeviceAddress deviceAddress)
{
    for (uint8_t i = 0; i < 7; i++)
    {
        // zero pad the address if necessary
        if (deviceAddress[i] < 16)
            Serial.print("0");
        Serial.print(deviceAddress[i], HEX);
    }
}
void Temperatures::temp_sensor_begin()
{

    DS18B20.setResolution(DS18B20_PRECISION); // set the resolution to 9 bit per device
    DS18B20.begin();                          // Start the DS18B20 sensor
    Serial.print("Found ");
    Serial.print(devCount);
    Serial.println(" devices.");

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
    DS18B20.setResolution(DS18B20_PRECISION); // set the resolution to 9 bit per device

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
    Serial.println();

    Serial.print("Device 5 Address: ");
    printAddress(device_5);
    Serial.println();*/
    DS18B20.setResolution(DS18B20_PRECISION); // set the resolution to 9 bit per device

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
    DS18B20.setResolution(DS18B20_PRECISION); // set the resolution to 9 bit per device
}
void Temperatures::measure_temperatures()
{
    DS18B20.requestTemperatures();
    if (millis() > timer1 + temp_measure_interval)
    {
        timer1 = millis();
        T_1 = DS18B20.getTempCByIndex(0);
        Serial.print("Temperature Sensor 1 reading is: ");
        Serial.print(T_1);
        Serial.println("ºC");
        outData = "tt1.txt=\"" + String(T_1, 2) + "\""; // generate string for the display
        display_control.sendDataToDisplay();
    }
    if (millis() > timer2 + temp_measure_interval)
    {
        timer2 = millis();
        T_2 = DS18B20.getTempCByIndex(1) - 0.5;
        timer2 = millis();
        Serial.print("Temperature Sensor 2 reading is: ");
        Serial.print(T_2 - 0.5);
        Serial.println("ºC");
        outData = "tt2.txt=\"" + String(T_2, 2) + "\""; // generate string for the display
        display_control.sendDataToDisplay();
    }
    if (millis() > timer3 + temp_measure_interval)
    {
        timer3 = millis();
        T_3 = DS18B20.getTempCByIndex(2) + 0.375;
        Serial.print("Temperature Sensor 3 reading is: ");
        Serial.print(T_3 + 0.375);
        Serial.println("ºC");
        outData = "tt3.txt=\"" + String(T_3, 2) + "\""; // generate string for the display
        display_control.sendDataToDisplay();
    }
    if (millis() > timer4 + temp_measure_interval)
    {
        timer4 = millis();
        T_4 = DS18B20.getTempCByIndex(3) - 0.25;
        Serial.print("Temperature Sensor 4 reading is: ");
        Serial.print(T_4 - 0.25);
        Serial.println("ºC");
        outData = "tt4.txt=\"" + String(T_4, 2) + "\""; // generate string for the display
        display_control.sendDataToDisplay();
    }
    /* if (millis() > timer5 + temp_measure_interval)
    {
        timer5 = millis();
        T_5 = DS18B20.getTempCByIndex(4);
        Serial.print("Temperature Sensor 5 reading is: ");
        Serial.print(T_5);
        Serial.println("ºC");
    }
    if (millis() > timer6 + temp_measure_interval)
    {
        timer6 = millis();
        T_6 = DS18B20.getTempCByIndex(5);
        Serial.print("Temperature Sensor 6 reading is: ");
        Serial.print(T_6);
        Serial.println("ºC");
    }*/
}

Temperatures temperatures_control;
