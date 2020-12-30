#include <definitions.h>
#include "Display.h"

void Display::endNextionCommand()
{
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.write(0xff);
}
void Display::sendDataToDisplay()
{ //send data to display
    Serial2.print(outData);
    endNextionCommand();
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

void Display::Refresh_Fans_Screen(String Nextion_Text_Field_f1, float f1_control_voltage, String Nextion_Text_Field_f2, float f2_control_voltage )
{
    if (inData == "f_m")
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






//hjgjkh




void Display::Refresh_Temperature_Screens()
{
    if (inData == "t_m") 
    {
        outData = "tt1.txt=\"" + String(T_1, 2) + "\"";
        sendDataToDisplay();
        outData = "tt2.txt=\"" + String(T_2, 2) + "\"";
        sendDataToDisplay();
        outData = "tt3.txt=\"" + String(T_3, 2) + "\"";
        sendDataToDisplay();
        outData = "tt4.txt=\"" + String(T_4, 2) + "\"";
        sendDataToDisplay();
    }
}

Display display_control;
