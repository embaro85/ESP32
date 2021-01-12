#include <Arduino.h>
#include "definitions.h"
#include "Heaters.h"
#include "Display.h"
#include "Temperatures.h"

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
        display_control.sendDataToDisplay();
    }
    if (heater_number == H2)
    {
        heater2_on_off_state = false;
        digitalWrite(heater_number, LOW);
        outData = "h3btn.val=" + String(heater2_on_off_state);
        display_control.sendDataToDisplay();
    }
    if (heater_number == H3)
    {
        heater2_on_off_state = false;
        digitalWrite(heater_number, LOW);
        outData = "h3btn.val=" + String(heater3_on_off_state);
        display_control.sendDataToDisplay();
    }
}

// switch on/off state of heater 1 according to a set temperature
void h1_temperature_control()
{
    if (T_2 < threshhold_temperature && h_manual_control_state_new == false && heater1_on_off_state == false)
    {
        heater1_on_off_state = true;
        Serial.print("Heater 1 state changed to ");
        Serial.println(heater1_on_off_state); //for debugging
        //new_state_h1 = false;  //sets new_state_h1 to true
        h_turn_on(H1);
        display_control.refresh_heaters_screen();
    }
    else if (T_2 > threshhold_temperature && h_manual_control_state_new == false && heater1_on_off_state == true)
    {
        heater1_on_off_state = false;
        Serial.print("Heater 1 state changed to ");
        Serial.println(heater1_on_off_state); //for debugging
                                              // new_state_h1 = true;  //sets new_state_h1 to false
        h_turn_off(H1);
        display_control.refresh_heaters_screen();
    }
}

/*void h2_temperature_control() // switch on/off state of heater 2 according to a set temperature
{
    if (T_2 > threshhold_temperature && h_manual_control_state_new == false)
    {
        heater2_on_off_state = true;
        //Serial.println("Heater 2 state is set to " + String(heater2_on_off_state));
    }
    else
    {
        heater2_on_off_state = false;
        // Serial.println("Heater 2 state is set to " + String(heater2_on_off_state));
    }
}

void h3_temperature_control() // switch on/off state of heater 3 according to a set temperature
{
    if (T_2 > threshhold_temperature && h_manual_control_state_new == false)
    {
        heater3_on_off_state = true;
        //Serial.println("Heater 3 state is set to " + String(heater3_on_off_state));
    }
    else
    {
        heater3_on_off_state = false;
        // Serial.println("Heater 3 state is set to " + String(heater3_on_off_state));
    }
}*/

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

Heaters heaters_control;
