#include <Arduino.h>
#include "definitions.h"
#include "Heaters.h"
#include "Display.h"
#include "Temperatures.h"
#include "Nextion_commands.h"
#include "SPIFFS.h"
#include "StringSplitter.h"
/*
/////Temperatures/////
float T_1 = 0.00; // exctract air
float T_2 = 0.00; // supply air
float T_3 = 0.00; // ambient air
float T_4 = 0.00; // exhaust air
float T_5 = 0.00; // valve temperature

deltaT=P/(1.26xQx0,34)
heated_air_temperature = ambient+???

Example 1:
P=2000W, Q=1000m3/h, ambient_temperature = -5°C
deltaT=2000/(1.26x1000x0,34) = 2000/428,4 = 4,669K
heated_air_temperature = -5+4,669 = -0,331°C

Example 2:
P=2000W, Q=500m3/h, ambient_temperature = -5°C
deltaT=2000/(1.26x500x0,34) = 2000/214,2 = 9,337K
heated_air_temperature = -5+9,337 = 4,337°C
*/

void Heaters::h1_PID_control() //temperature control of heater 1
{
    if (heaters_manual_control_enabled == false && f2_permission_for_heaters_start_granted == true && winter_mode == true && heating_enabled == true && h1_enabled == true)
    {
        /* setpoint 3 is the lowest temperature and setpoint 1 the highest*/
        if (T_2 <= temperature_setpoint_1 && h1_enabled == true) // heating on, antifreeze off
        {
            heater1_on_off_state = true;
            timer5 = millis();
        }

        if ((T_2 > temperature_setpoint_1 && heater1_on_off_state == true && millis() > (timer5 + (h1_time_period * 1000))) || h1_enabled == false)
        {
            heater1_on_off_state = false;
            timer5 = millis();
        }
    }
    if (heaters_manual_control_enabled == false) // turn heater off if conditions are met
    {
        if (heating_enabled == false || f2_permission_for_heaters_start_granted == false || winter_mode == false || h1_enabled == false)
        {
            if (heater1_on_off_state == true)
            {
                heater1_on_off_state = false;
            }
        }
    }
}
void Heaters::h2_PID_control() //temperature control of heater 2
{
    if (heaters_manual_control_enabled == false && f2_permission_for_heaters_start_granted == true && winter_mode == true && heating_enabled == true && h2_enabled == true)
    {
        if (T_2 <= temperature_setpoint_2)
        {
            heater2_on_off_state = true;
            timer6 = millis();
        }
        if (temperature_setpoint_2 < T_2 && heater2_on_off_state == true && millis() > (timer6 + (h2_time_period * 1000)))
        {
            heater2_on_off_state = false;
            timer6 = millis();
        }
    }
    if (heaters_manual_control_enabled == false) // turn heater off if conditions are met
    {
        if (heating_enabled == false || f2_permission_for_heaters_start_granted == false || winter_mode == false || h2_enabled == false)
        {
            if (heater2_on_off_state == true)
            {
                heater2_on_off_state = false;
            }
        }
    }
}
void Heaters::h3_PID_control() //temperature control of heater 3
{
    if (heaters_manual_control_enabled == false && f2_permission_for_heaters_start_granted == true && winter_mode == true && heating_enabled == true && h3_enabled == true && antifreeze_ebanbled == false)
    {
        if (T_2 <= temperature_setpoint_3)
        {
            heater3_on_off_state = true;
            timer7 = millis();
        }
        if (T_2 > temperature_setpoint_3 && heater3_on_off_state == true && millis() > (timer7 + (h3_time_period * 1000)))
        {
            heater3_on_off_state = false;
            timer7 = millis();
        }
    }
    if (heaters_manual_control_enabled == false) // turn heater off if conditions are met
    {
        if ((heating_enabled == false && antifreeze_ebanbled == false) || f2_permission_for_heaters_start_granted == false || winter_mode == false || h3_enabled == false)
        {
            if (heater3_on_off_state == true)
            {
                heater3_on_off_state = false;
            }
        }
    }
}
void Heaters::working_stream()
{
    heaters_control.resfresh_page_p2();
    heaters_control.commands_from_display();
    heaters_control.heaters_manual_control();
    heaters_control.save_manual_settings_p3();
    heaters_control.h1_PID_control();
    heaters_control.h2_PID_control();
    heaters_control.h3_PID_control();
    heaters_control.turn_heaters_on_or_off();
    heaters_control.heaters_antifreeze_protection();
}
void Heaters::h_turn_on(uint8_t heater_number)
{
    digitalWrite(heater_number, HIGH);
}
void Heaters::h_turn_off(uint8_t heater_number)
{
    digitalWrite(heater_number, LOW);
}
void Heaters::heaters_antifreeze_protection()
{
    if (heaters_manual_control_enabled == false && winter_mode == true && antifreeze_ebanbled == true && f2_permission_for_heaters_start_granted == true)
    {
        if (T_3 < threshold_temperature_antifreeze && heater3_on_off_state == false)
        {
            if (h3_enabled == true)
            {
                heater3_on_off_state = true;
                Serial.println("Heater 3 is ON as antifreeze protection");
            }
          
            //heaters_on = true;
        }
        else if (T_3 > threshold_temperature_antifreeze && heater3_on_off_state == true)
        {
            heater3_on_off_state = false;
            Serial.println("Heater 3 is OFF as antifreeze protection");
        }
    }
}
void Heaters::heaters_manual_control() // turn heaters manually on or off
{
    if (inData == p3_b1_on)
    {
        heater1_on_off_state = true;
        nextion_commands.set_text_of_screen_component(p3_b1_text, "ON");
        h_turn_on(H1);
        Serial.println("Heater 1 turned manually ON");
    }
    if (inData == p3_b1_off)
    {
        heater1_on_off_state = false;
        nextion_commands.set_text_of_screen_component(p3_b1_text, "OFF");
        h_turn_off(H1);
        Serial.println("Heater 1 turned manually OFF");
    }
    if (inData == p3_b2_on)
    {
        heater2_on_off_state = true;
        nextion_commands.set_text_of_screen_component(p3_b2_text, "ON");
        h_turn_on(H2);
        Serial.println("Heater 2 turned manually ON");
    }
    if (inData == p3_b2_off)
    {
        heater2_on_off_state = false;
        nextion_commands.set_text_of_screen_component(p3_b2_text, "OFF");
        h_turn_off(H2);
        Serial.println("Heater 2 turned manually OFF");
    }
    if (inData == p3_b3_on)
    {
        heater3_on_off_state = true;
        nextion_commands.set_text_of_screen_component(p3_b3_text, "ON");
        h_turn_on(H3);
        Serial.println("Heater 3 turned manually ON");
    }
    if (inData == p3_b3_off)
    {
        heater3_on_off_state = false;
        nextion_commands.set_text_of_screen_component(p3_b3_text, "OFF");
        h_turn_off(H3);
        Serial.println("Heater 3 turned manually OFF");
    }
}
void Heaters::turn_heaters_off()
{
    heater1_on_off_state = false;
    heater2_on_off_state = false;
    heater3_on_off_state = false;
    heater3_on_off_state = false;
    Serial.println("Heater 1 is OFF ");
    Serial.println("Heater 2 is OFF ");
    Serial.println("Heater 3 is OFF ");
}
void Heaters::turn_heaters_on_or_off() //set the pins to HiGH or LOW according to the settings and current conditions
{
    if (heaters_manual_control_enabled == false)
    {
        if (heater1_on_off_state == true)
        {
            h_turn_on(H1);
        }
        if (heater1_on_off_state == false)
        {
            h_turn_off(H1);
        }
        if (heater2_on_off_state == true)
        {
            h_turn_on(H2);
        }
        if (heater2_on_off_state == false)
        {
            h_turn_off(H2);
        }
        if (heater3_on_off_state == true)
        {
            h_turn_on(H3);
        }
        if (heater3_on_off_state == false)
        {
            h_turn_off(H3);
        }
    }
}
void Heaters::resfresh_page_p2()
{
    if (millis() > (timer4 + 2000) && on_page_number == Heaters1_2)
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

        nextion_commands.set_value_of_screen_component(p2_c0_value, heaters_manual_control_enabled);
    }
}
void Heaters::refresh_page_p3()
{
    if (heater1_on_off_state == true)
    {
        nextion_commands.set_value_of_screen_component(p3_b1_value, heater1_on_off_state);
        nextion_commands.set_text_of_screen_component(p3_b1_text, "ON");
    }
    if (heater1_on_off_state == false)
    {
        nextion_commands.set_value_of_screen_component(p3_b1_value, heater1_on_off_state);
        nextion_commands.set_text_of_screen_component(p3_b1_text, "OFF");
    }

    if (heater2_on_off_state == true)
    {
        nextion_commands.set_value_of_screen_component(p3_b2_value, heater2_on_off_state);
        nextion_commands.set_text_of_screen_component(p3_b2_text, "ON");
    }
    if (heater2_on_off_state == false)
    {
        nextion_commands.set_value_of_screen_component(p3_b2_value, heater2_on_off_state);
        nextion_commands.set_text_of_screen_component(p3_b2_text, "OFF");
    }
    if (heater3_on_off_state == true)
    {
        nextion_commands.set_value_of_screen_component(p3_b3_value, heater3_on_off_state);
        nextion_commands.set_text_of_screen_component(p3_b3_text, "ON");
    }
    if (heater3_on_off_state == false)
    {
        nextion_commands.set_value_of_screen_component(p3_b3_value, heater3_on_off_state);
        nextion_commands.set_text_of_screen_component(p3_b3_text, "OFF");
    }
    nextion_commands.set_value_of_screen_component(p3_c0_value, heaters_manual_control_enabled);
}
void Heaters::commands_from_display()
{
    if (inData == p2_b0_command) // return to home screen
    {
        //on_page_2 = false;
        nextion_commands.on_page(1);
        nextion_commands.go_to_page_Nextion(1);
    }
    if (inData == p3_b0_command)
    {
        nextion_commands.go_to_page_Nextion(1);
    }
    if (inData == p2_c0_on) //navigates to warning page
    {
        nextion_commands.go_to_page_Nextion(8);
        nextion_commands.on_page(8);
    }
    if (inData == p8_b0_command) //turns the manual control ON
    {
        heaters_manual_control_enabled = true;
        nextion_commands.go_to_page_Nextion(3);
        heaters_control.refresh_page_p3();
    }
    if (inData == p8_b1_command || inData == p3_c0_off) // turns the manual control OFF
    {
        heaters_manual_control_enabled = false;
        nextion_commands.on_page(Heaters1_2);
        //on_page_2 = true;
        nextion_commands.go_to_page_Nextion(2);
    }
}
void Heaters::save_manual_settings_p3()
{
    String _save_settings_p3 = save_settings_p3;
    save_settings_p3 = String(heaters_manual_control_enabled) + "," + String(heater1_on_off_state) + "," + String(heater2_on_off_state) + "," + String(heater3_on_off_state) + ",";
    if (_save_settings_p3 != save_settings_p3)
    {
        Serial.println(save_settings_p3);
        File saved_values_p3;
        saved_values_p3 = SPIFFS.open("/values_p3.txt", FILE_WRITE);
        if (saved_values_p3.print(save_settings_p3))
        {
            Serial.println("New settings for the manual control of the heaters have been successfully written to the internal memory");
        }
        else
        {
            Serial.println("File write for the fan settings failed");
        }
        saved_values_p3.close();
    }
}
void Heaters::load_manual_settings_p3()
{
    File saved_values_p3;
    saved_values_p3 /*here the file name, not the string variable*/ = SPIFFS.open("/values_p3.txt", "r");
    if (!saved_values_p3)
    {
        Serial.println("Failed to open heaters settings file for reading");
        return;
    }
    Serial.print("Heaters manual control Settings: ");
    save_settings_p3 = saved_values_p3.readString();
    saved_values_p3.close();
    Serial.println(save_settings_p3);
    StringSplitter *splitter = new StringSplitter(save_settings_p3, ',', 4);
    String _heaters_manual_control_enabled = splitter->getItemAtIndex(0);
    String _heater1_on_off_state = splitter->getItemAtIndex(1);
    String _heater2_on_off_state = splitter->getItemAtIndex(2);
    String _heater3_on_off_state = splitter->getItemAtIndex(3);
    heaters_manual_control_enabled = _heaters_manual_control_enabled.toInt();
    heater1_on_off_state = _heater1_on_off_state.toInt();
    heater2_on_off_state = _heater2_on_off_state.toInt();
    heater3_on_off_state = _heater3_on_off_state.toInt();
    if (heaters_manual_control_enabled == true)
    {
        delay(100);
        digitalWrite(H1, heater1_on_off_state);
        digitalWrite(H2, heater2_on_off_state);
        digitalWrite(H3, heater3_on_off_state);
        Serial.println(heater1_on_off_state);
        Serial.println("Heater 2 is: " + String(heater2_on_off_state));
        Serial.println("Heater 3 is: " + String(heater3_on_off_state));
    }
}

Heaters heaters_control;
