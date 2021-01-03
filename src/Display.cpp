#include <definitions.h>
#include "Display.h"
#include "Temperatures.h"

void Display::sendDataToDisplay()
{ //send data to display
    Serial2.print(outData);
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.flush();
}

void Display::receive_data_from_display()
{ // Read incoming data from Display

    if (Serial2.available() > 0)
    { // wait for a character
        inData = Serial2.readStringUntil('#');
        Serial.println(inData); //for debugging
        delay(10);
        Serial2.flush();
    }
}

void Display::Refresh_Fans_Screen(String Nextion_Text_Field_f1, float f1_control_voltage, String Nextion_Text_Field_f2, float f2_control_voltage, String ref_fans_screen_cmd)
{
    if (ref_fans_screen_cmd == inData)
    {
        outData = Nextion_Text_Field_f1 + String(f1_control_voltage, 1) + String(" V") + "\"";
        sendDataToDisplay();
        outData = Nextion_Text_Field_f2 + String(f2_control_voltage, 1) + String(" V") + "\"";
        sendDataToDisplay();
        outData = "bt0.val=" + String(f1_on_off_state);
        sendDataToDisplay();
        outData = "bt1.val=" + String(f2_on_off_state);
        sendDataToDisplay();
    }
}

void Display::Refresh_Temperature_Screen_1(String t1_Nextion_Text_Field, float t1_temperature, String t2_Nextion_Text_Field, float t2_temperature, String ref_temp1_screen_cmd)
{
   /* if (ref_temp1_screen_cmd == inData)
    {
        on_temp_screen_one = inData;
       // while (on_temp_screen_one == ref_temp1_screen_cmd)
        {
            temperatures_control.measure_temperatures();
          
            outData = t1_Nextion_Text_Field + String(t1_temperature, 1) + "\"";
            sendDataToDisplay();
            outData = t2_Nextion_Text_Field + String(t2_temperature, 1) + "\"";
            sendDataToDisplay();
            
        }
    }*/
}

void Display::Refresh_Temperature_Screen_2(String t3_Nextion_Text_Field, float t3_temperature, String t4_Nextion_Text_Field, float t4_temperature, String ref_temp2_screen_cmd)
{
   /* if (ref_temp2_screen_cmd == inData)
    {
        temperatures_control.measure_temperatures();
        outData = t3_Nextion_Text_Field + String(t3_temperature, 1) + "\"";
        sendDataToDisplay();
        outData = t4_Nextion_Text_Field + String(t4_temperature, 1) + "\"";
        sendDataToDisplay();
    }*/
}

Display display_control;
