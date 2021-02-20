#include <Arduino.h>
#include "definitions.h"
#include "Heaters.h"
#include "Display.h"
#include "Temperatures.h"
#include "Nextion_commands.h"

void Heaters::working_stream()

{
    heaters_control.resfresh_page();
    heaters_control.commands_from_display();
}
//digitalWrite HIGH in another form for heater 1
void h_turn_on(uint8_t heater_number)
{
    digitalWrite(heater_number, HIGH);
}
//digitalWrite LOW in another form for heater 1
void h_turn_off(uint8_t heater_number) //Heater 1 turn off manually
{
    digitalWrite(heater_number, LOW);
}
// example for heater number -H1 (not just the number)
void turn_heater_on(uint8_t heater_number)
{
    if (heater_number == H1)
    {
        heater1_on_off_state = true;
        h_turn_on(H1);
    }
    if (heater_number == H2)
    {
        heater2_on_off_state = true;
        h_turn_on(H2);
    }

    if (heater_number == H3)
    {
        heater3_on_off_state = true;
        h_turn_on(H1);
    }
}
// example for heater number -H1 (not just the number)
void turn_heater_off(uint8_t heater_number)
{
    if (heater_number == H1)
    {
        heater1_on_off_state = false;
        digitalWrite(heater_number, LOW);
        outData = "h3btn.val=" + String(heater1_on_off_state);
        nextion_commands.send_data_to_display();
    }
    if (heater_number == H2)
    {
        heater2_on_off_state = false;
        digitalWrite(heater_number, LOW);
        outData = "h3btn.val=" + String(heater2_on_off_state);
        nextion_commands.send_data_to_display();
    }
    if (heater_number == H3)
    {
        heater2_on_off_state = false;
        digitalWrite(heater_number, LOW);
        outData = "h3btn.val=" + String(heater3_on_off_state);
        nextion_commands.send_data_to_display();
    }
}

// switch on/off state of heater 1 according to a set temperature
void Heaters::h1_temperature_control()
{
    if (T_2 < threshold_temperature && h_manual_control_state_new == false && heater1_on_off_state == false)
    {
        heater1_on_off_state = true;
        Serial.print("Heater 1 state changed to ");
        Serial.println(heater1_on_off_state); //for debugging
        h_turn_on(H1);
    }
    else if (T_2 > threshold_temperature && h_manual_control_state_new == false && heater1_on_off_state == true)
    {
        heater1_on_off_state = false;
        Serial.print("Heater 1 state changed to ");
        Serial.println(heater1_on_off_state); //for debugging
        h_turn_off(H1);
    }
}

void Heaters::heaters_temperature_contol() //unifies the methods for the heaters
{
    h1_temperature_control();
    //  h2_temperature_control();
    // h3_temperature_control();
}

void Heaters::heaters_manual_control()
{
    if (h_manual_control_state_new == true && inData == "h1_on")
    {
        turn_heater_on(H1);
        heater1_on_off_state = false;
    }
    if (h_manual_control_state_new == true && inData == "h1_off")
    {
        turn_heater_off(H1);
        heater1_on_off_state = true;
    }

    if (h_manual_control_state_new == true && inData == "h2_on")
    {
        turn_heater_on(H2);
        heater2_on_off_state = true;
    }
    if (h_manual_control_state_new == true && inData == "h2_off")
    {
        turn_heater_off(H2);
        heater2_on_off_state = false;
    }

    if (h_manual_control_state_new == true && inData == "h3_on")
    {
        turn_heater_on(H3);
        heater3_on_off_state = true;
    }
    if (h_manual_control_state_new == true && inData == "h3_off")
    {
        turn_heater_off(H3);
        heater3_on_off_state = false;
    }
}

void Heaters::turn_heaters_off()
{
    heater1_on_off_state = false;
    heater2_on_off_state = false;
    heater3_on_off_state = false;
}

void Heaters::resfresh_page()
{
    if (millis() > (timer4 + 2000) && on_page_2 == true)
    {
       timer4 = millis();
        if (heater1_on_off_state == true)
        {
            nextion_commands.set_text_of_screen_component(p2_t5, "включен");
        }
        if (heater1_on_off_state == false)
        {
            nextion_commands.set_text_of_screen_component(p2_t5, "изключен");
        }

        if (heater2_on_off_state == true)
        {
            nextion_commands.set_text_of_screen_component(p2_t6, "включен");
        }
        if (heater2_on_off_state == false)
        {
            nextion_commands.set_text_of_screen_component(p2_t6, "изключен");
        }

        if (heater3_on_off_state == true)
        {
            nextion_commands.set_text_of_screen_component(p2_t7, "включен");
        }
        if (heater3_on_off_state == false)
        {
            nextion_commands.set_text_of_screen_component(p2_t7, "изключен");
        }

        nextion_commands.set_value_of_screen_component(p2_bhmanual, h_manual_control_state_new);
    }
}

void Heaters::commands_from_display()
{
   
   if (inData == p2_b0_command)
    {
        on_page_2 = false;
        nextion_commands.go_to_page_Nextion(1);
    }
}


Heaters heaters_control;
