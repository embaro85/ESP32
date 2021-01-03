#include <Arduino.h>
#include "definitions.h"
#include "Heaters.h"
#include "Display.h"

void Heaters::heaters_manual_control()
{
    if (inData == "ok_h_man")
    {
        h_manual_control = true;
        if (h_manual_control == 1)
        {
            outData = "bhmanual.val=" + String(h_manual_control);
            display_control.sendDataToDisplay();
            Serial.println("Manual contol is: " + String(h_manual_control));
        }
        else if (h_manual_control == 0)
        {
            h_manual_control = false;
            outData = "bhmanual.val=" + String(h_manual_control);
            display_control.sendDataToDisplay();
            Serial.println("Manual contol is: " + String(h_manual_control));
        }
    }
}

void Heaters::h1_manual_on_off()
{
    if (h_manual_control == true && inData == "h1_on")
    {
        heater1_on_off_state = true;
        digitalWrite(H1, HIGH);
        outData = "h1btn.val=" + String(heater1_on_off_state);
        display_control.sendDataToDisplay();
    }
    else if (h_manual_control == true && inData == "h1_off")
    {
        heater1_on_off_state = false;
        digitalWrite(H1, LOW);
        outData = "h1btn.val=" + String(heater1_on_off_state);
        display_control.sendDataToDisplay();
    }
}

void Heaters::h2_manual_on_off()
{
     if (h_manual_control == true && inData == "h2_on")
    {
        heater2_on_off_state = true;
        digitalWrite(H2, HIGH);
        outData = "h2btn.val=" + String(heater2_on_off_state);
        display_control.sendDataToDisplay();
    }
    else if (h_manual_control == true && inData == "h2_off")
    {
        heater2_on_off_state = false;
        digitalWrite(H2, LOW);
        outData = "h2btn.val=" + String(heater2_on_off_state);
        display_control.sendDataToDisplay();
    }
}

void Heaters::h3_manual_on_off()
{
    if (h_manual_control == true && inData == "h3_on")
    {
        heater3_on_off_state = true;
        digitalWrite(H3, HIGH);
        outData = "h3btn.val=" + String(heater3_on_off_state);
        display_control.sendDataToDisplay();
    }
    else if (h_manual_control == true && inData == "h3_off")
    {
        heater3_on_off_state = false;
        digitalWrite(H3, LOW);
        outData = "h3btn.val=" + String(heater3_on_off_state);
        display_control.sendDataToDisplay();
    }
}

Heaters heaters_control;
