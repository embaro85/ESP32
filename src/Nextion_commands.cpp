#include "Nextion_commands.h"
#include <Arduino.h>
#include "definitions.h"



void Nextion_commands::receive_data_from_display()
{ // Read incoming data from Display
    if (Serial2.available() > 0)
    { // wait for a character
        inData = Serial2.readStringUntil('#');
        Serial.println(inData); //for debugging
        delay(10);
        Serial2.flush();
    }
}

void Nextion_commands::set_visibility_on_Nextion(String Element_name, uint8_t Visibility_toggle)
{
    outData = "vis " + Element_name + "," + Visibility_toggle;
    nextion_commands.send_data_to_display();
}

void Nextion_commands::set_value_of_screen_component(String nextion_component, uint8_t variable)
{
    outData = nextion_component + String(variable);
    nextion_commands.send_data_to_display();
}

void Nextion_commands::set_text_of_screen_component (String nextion_component, uint16_t variable)
{
    outData = nextion_component + String (variable) + "\"";
    nextion_commands.send_data_to_display();
}

void Nextion_commands::send_data_to_display()
{ //send data to display
    Serial2.print(outData);
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.flush();
}




void Nextion_commands::go_to_page_Nextion(int Page_number)
{
    outData = "page " + String(Page_number);
    nextion_commands.send_data_to_display();
}



Nextion_commands nextion_commands;
