#include "dampers.h"
#include "Nextion_commands.h"
#include "definitions.h"
#include <SPIFFS.h>
#include <StringSplitter.h>

void Dampers::working_stream()
{
    dampers_control.commands_from_display();
    dampers_control.damper_1_control();
    dampers_control.damper_2_control();
    dampers_control.damper_3_control();
    dampers_control.damper_4_control();
    dampers_control.save_settings();
    dampers_control.dampers_start_routine();
}

void Dampers::damper_1_control() //set start time for DAMPER 1
{
    if (inData == p17_b0_command && d1_enabled == true) //set start time for DAMPER 1
    {
        if (d1_time_delay <= 95)
        {
            d1_time_delay = d1_time_delay + 5;
            nextion_commands.set_text_of_screen_component(p17_t5, String(d1_time_delay) + "сек");
        }
    }
    if (inData == p17_b1_command && d1_enabled == true)
    {
        if (d1_time_delay >= -95)
        {
            d1_time_delay = d1_time_delay - 5;
            nextion_commands.set_text_of_screen_component(p17_t5, String(d1_time_delay) + "сек");
        }
    }
}
void Dampers::damper_2_control() //set start time for DAMPER 2
{
    if (inData == p17_b2_command && d2_enabled == true) //set start time for DAMPER 2
    {
        if (d2_time_delay <= 95)
        {
            d2_time_delay = d2_time_delay + 5;
            nextion_commands.set_text_of_screen_component(p17_t7, String(d2_time_delay) + "сек");
        }
    }
    if (inData == p17_b3_command && d2_enabled == true)
    {
        if (d2_time_delay >= -95)
        {
            d2_time_delay = d2_time_delay - 5;
            nextion_commands.set_text_of_screen_component(p17_t7, String(d2_time_delay) + "сек");
        }
    }
}
void Dampers::damper_3_control() //set start time for DAMPER 3
{
    if (inData == p17_b4_command && d3_enabled == true) //set start time for DAMPER 1
    {
        if (d3_time_delay <= 95)
        {
            d3_time_delay = d3_time_delay + 5;
            nextion_commands.set_text_of_screen_component(p17_t9, String(d3_time_delay) + "сек");
        }
    }
    if (inData == p17_b5_command && d3_enabled == true)
    {
        if (d3_time_delay >= -95)
        {
            d3_time_delay = d3_time_delay - 5;
            nextion_commands.set_text_of_screen_component(p17_t9, String(d3_time_delay) + "сек");
        }
    }
}
void Dampers::damper_4_control() //set start time for DAMPER 4
{
    if (inData == p17_b6_command && d4_enabled == true)
    {
        if (d4_time_delay <= 95)
        {
            d4_time_delay = d4_time_delay + 5;
            nextion_commands.set_text_of_screen_component(p17_t11, String(d4_time_delay) + "сек");
        }
    }
    if (inData == p17_b7_command && d4_enabled == true)
    {
        if (d4_time_delay >= -95)
        {
            d4_time_delay = d4_time_delay - 5;
            nextion_commands.set_text_of_screen_component(p17_t11, String(d4_time_delay) + "сек");
        }
    }
}
void Dampers::refresh_screen()
{
    nextion_commands.set_value_of_screen_component(p17_c0, d1_enabled);
    nextion_commands.set_value_of_screen_component(p17_c1, d2_enabled);
    nextion_commands.set_value_of_screen_component(p17_c2, d3_enabled);
    nextion_commands.set_value_of_screen_component(p17_c3, d4_enabled);
    nextion_commands.set_text_of_screen_component(p17_t5, String(d1_time_delay) + "сек");
    nextion_commands.set_text_of_screen_component(p17_t7, String(d2_time_delay) + "сек");
    nextion_commands.set_text_of_screen_component(p17_t9, String(d3_time_delay) + "сек");
    nextion_commands.set_text_of_screen_component(p17_t11, String(d4_time_delay) + "сек");
}
void Dampers::commands_from_display()
{
    if (inData == p17_b8_command) // go back to the settings page
    {
        nextion_commands.go_to_page_Nextion(7);
    }
    if (inData == p17_c0_command_on) // enable damper 1 control
    {
        d1_enabled = true;
        nextion_commands.set_text_of_screen_component(p17_t5, String(d1_time_delay) + " сек");
    }
    if (inData == p17_c0_command_off) // disable damper 1 control
    {
        d1_enabled = false;
        d1_time_delay = 0;
        nextion_commands.set_text_of_screen_component(p17_t5, "--");
    }
    if (inData == p17_c1_command_on) // enable damper 2 control
    {
        d2_enabled = true;
        nextion_commands.set_text_of_screen_component(p17_t7, String(d2_time_delay) + " сек");
    }
    if (inData == p17_c1_command_off) // disable damper 1 control
    {
        d2_enabled = false;
        d2_time_delay = 0;
        nextion_commands.set_text_of_screen_component(p17_t7, "--");
    }
    if (inData == p17_c2_command_on) // enable damper 3 control
    {
        d3_enabled = true;
        nextion_commands.set_text_of_screen_component(p17_t9, String(d3_time_delay) + " сек");
    }
    if (inData == p17_c2_command_off) // disable damper 1 control
    {
        d3_enabled = false;
        d3_time_delay = 0;
        nextion_commands.set_text_of_screen_component(p17_t9, "--");
    }
    if (inData == p17_c3_command_on) // enable damper 4 control
    {
        d4_enabled = true;
        nextion_commands.set_text_of_screen_component(p17_t11, String(d4_time_delay) + " сек");
    }
    if (inData == p17_c3_command_off) // disable damper 1 control
    {
        d4_enabled = false;
        d4_time_delay = 0;
        nextion_commands.set_text_of_screen_component(p17_t11, "--");
    }
    if (inData == p17_t12_command) //show the help text box
    {
        nextion_commands.set_visibility_on_Nextion(p17_t13_vis, 1);
        nextion_commands.set_visibility_on_Nextion(p17_b0_vis, 0);
        nextion_commands.set_visibility_on_Nextion(p17_b1_vis, 0);
        nextion_commands.set_visibility_on_Nextion(p17_c0_vis, 0);
        nextion_commands.set_visibility_on_Nextion(p17_b2_vis, 0);
        nextion_commands.set_visibility_on_Nextion(p17_b3_vis, 0);
        nextion_commands.set_visibility_on_Nextion(p17_c1_vis, 0);
    }
    if (inData == p17_t13_command) // hide the help text box
    {
        nextion_commands.set_visibility_on_Nextion(p17_t13_vis, 0);
        nextion_commands.set_visibility_on_Nextion(p17_b0_vis, 1);
        nextion_commands.set_visibility_on_Nextion(p17_b1_vis, 1);
        nextion_commands.set_visibility_on_Nextion(p17_c0_vis, 1);
        nextion_commands.set_visibility_on_Nextion(p17_b2_vis, 1);
        nextion_commands.set_visibility_on_Nextion(p17_b3_vis, 1);
        nextion_commands.set_visibility_on_Nextion(p17_c1_vis, 1);
    }
}
void Dampers::save_settings()
{
    String _damper_settings = damper_settings;
    damper_settings = String(d1_enabled) + "," + String(d2_enabled) + "," + String(d3_enabled) + "," + String(d4_enabled) + "," + String(d1_time_delay) + "," + String(d2_time_delay) + "," + String(d3_time_delay) + "," + String(d4_time_delay);
    if (_damper_settings != damper_settings)
    {
        Serial.println("New Dampers Settings detected: " + damper_settings);
        File saved_values_dampers_settings;
        saved_values_dampers_settings = SPIFFS.open("/values_damp_settings.txt", FILE_WRITE);
        if (saved_values_dampers_settings.print(damper_settings))
        {
            Serial.println("New settings for the dampers have been changed and successfully written to the internal memory");
        }
        else
        {
            Serial.println("File write for the dampers settings failed");
        }
        saved_values_dampers_settings.close();
    }
}
void Dampers::load_settings()
{
    File saved_values_dampers_settings;
    saved_values_dampers_settings = SPIFFS.open("/values_damp_settings.txt", "r");
    if (!saved_values_dampers_settings)
    {
        Serial.println("Failed to open file for reading");
        return;
    }
    Serial.print("Dampers Settings: ");
    damper_settings = saved_values_dampers_settings.readString();
    saved_values_dampers_settings.close();
    Serial.println(damper_settings);
    StringSplitter *splitter = new StringSplitter(damper_settings, ',', 8); // new StringSplitter(string_to_split, delimiter, limit)
                                                                            // read display brightness
    String _d1_enabled = splitter->getItemAtIndex(0);
    String _d2_enabled = splitter->getItemAtIndex(1);
    String _d3_enabled = splitter->getItemAtIndex(2);
    String _d4_enabled = splitter->getItemAtIndex(3);
    String _d1_time_delay = splitter->getItemAtIndex(4);
    String _d2_time_delay = splitter->getItemAtIndex(5);
    String _d3_time_delay = splitter->getItemAtIndex(6);
    String _d4_time_delay = splitter->getItemAtIndex(7);

    d1_enabled = _d1_enabled.toInt();
    d2_enabled = _d2_enabled.toInt();
    d3_enabled = _d3_enabled.toInt();
    d4_enabled = _d4_enabled.toInt();
    d1_time_delay = _d1_time_delay.toInt();
    d2_time_delay = _d2_time_delay.toInt();
    d3_time_delay = _d3_time_delay.toInt();
    d4_time_delay = _d4_time_delay.toInt();
}
int Dampers::maximum_delay() // calculate the biggest positive delay
{
    max_delay = max(d1_time_delay, d2_time_delay);
    max_delay = max(max_delay, d3_time_delay);
    max_delay = max(max_delay, d4_time_delay);
    return max_delay;
}
int Dampers::minimum_delay() // calculate the biggest negative delay
{
    min_delay = min(d1_time_delay, d2_time_delay);
    min_delay = min(min_delay, d3_time_delay);
    min_delay = min(min_delay, d4_time_delay);
    //Serial.print( "minimum damper delay is: ");
    //Serial.println (min_delay);
    if (d1_time_delay == min_delay)
    {
        d2_initial_start_time_delay = d2_time_delay - min_delay;
        d3_initial_start_time_delay = d3_time_delay - min_delay;
        d4_initial_start_time_delay = d4_time_delay - min_delay;
    }
    if (d2_time_delay == min_delay)
    {
        d1_initial_start_time_delay = d1_time_delay - min_delay;
        d3_initial_start_time_delay = d3_time_delay - min_delay;
        d4_initial_start_time_delay = d4_time_delay - min_delay;
    }
    if (d3_time_delay == min_delay)
    {
        d1_initial_start_time_delay = d1_time_delay - min_delay;
        d2_initial_start_time_delay = d2_time_delay - min_delay;
        d4_initial_start_time_delay = d4_time_delay - min_delay;
    }
    if (d4_time_delay == min_delay)
    {
        d1_initial_start_time_delay = d1_time_delay - min_delay;
        d2_initial_start_time_delay = d2_time_delay - min_delay;
        d3_initial_start_time_delay = d3_time_delay - min_delay;
    }

    return min_delay;
}

void Dampers::dampers_start_routine() //should be started after loading the saved settings
{
    if (permission_for_the_unit_start_granted == true) // control the dampers if the pre-set time is 0
    {
        if (millis() > timer16 + (abs(minimum_delay()) * 1000) && d1_enabled == true && d1_time_delay == 0 && d1_run_once == true) // start damper 1 with the fans if the activation time is 0
        {
            d1_permission_fans_can_start = true; // Damper 1 grants permission to the fans
            Serial.println("Damper 1 permission granted for fans start");
            d1_run_once = false; //used as a run once variable
            turn_damper_1_on();
        }
        if (millis() > timer16 + (abs(minimum_delay()) * 1000) && d2_enabled == true && d2_time_delay == 0 && d2_run_once == true) // start damper 2 with the fans if the activation time is 0
        {
            d2_permission_fans_can_start = true;
            Serial.println("Damper 2 permission granted for fans start");
            d2_run_once = false; //used as a run once variable
            turn_damper_2_on();
        }
        if (millis() > timer16 + (abs(minimum_delay()) * 1000) && d3_enabled == true && d3_time_delay == 0 && d3_run_once == true) // start damper 3 with the fans if the activation time is 0
        {
            d3_permission_fans_can_start = true;
            Serial.println("Damper 3 permission granted for fans start");
            d3_run_once = false; //used as a run once variable
            turn_damper_3_on();
        }
        if (millis() > timer16 + (abs(minimum_delay()) * 1000) && d4_enabled == true && d4_time_delay == 0 && d4_run_once == true) // start damper 4 with the fans if the activation time is 0
        {
            d4_permission_fans_can_start = true;
            Serial.println("Damper 4 permission granted for fans start");
            d4_run_once = false; //used as a run once variable
            turn_damper_4_on();
        }
    }
    if (permission_for_the_unit_start_granted == true) // control the dampers is the pre-set period is positive
    {
        if (d1_enabled == true && d1_time_delay > 0 && d1_run_once == true) // permit the start of the fans and start the damper after the given time delay
        {
            d1_permission_fans_can_start = true;
            Serial.println("Damper 1 permission granted");
            d1_run_once = false;
        }
        if (millis() > timer16 + (d1_time_delay * 1000) && d1_run_once_2 == true && dampers_have_permission_from_fans == true && d1_time_delay > 0)
        {
            turn_damper_1_on();
            d1_run_once_2 = false; // used as a run once variable
        }
        if (d2_enabled == true && d2_time_delay > 0 && d2_run_once == true) // permit the start of the fans and start the damper after the given time delay
        {
            d2_permission_fans_can_start = true;
            Serial.println("Damper 2 permission granted");
            d2_run_once = false;
        }
        if (millis() > timer16 + (d2_time_delay * 1000) && d2_run_once_2 == true && dampers_have_permission_from_fans == true && d2_time_delay > 0)
        {
            turn_damper_2_on();
            d2_run_once_2 = false;
        }
        if (d3_enabled == true && d3_time_delay > 0 && d3_run_once == true) // permit the start of the fans and start the damper after the given time delay
        {
            d3_permission_fans_can_start = true;
            Serial.println("Damper 3 permission granted");
            d3_run_once = false;
        }
        if (millis() > timer16 + (d3_time_delay * 1000) && d3_run_once_2 == true && dampers_have_permission_from_fans == true && d3_time_delay > 0)
        {
            turn_damper_3_on();
            d3_run_once_2 = false;
        }
        if (d4_enabled == true && d4_time_delay > 0 && d4_run_once == true) // permit the start of the fans and start the damper after the given time delay
        {
            d4_permission_fans_can_start = true;
            Serial.println("Damper 4 permission granted");
            d4_run_once = false;
        }
        if (millis() > timer16 + (d4_time_delay * 1000) && d4_run_once_2 == true && dampers_have_permission_from_fans == true && d4_time_delay > 0)
        {
            turn_damper_4_on();
            d4_run_once_2 = false;
        }
    }
    /*
     with the start of the unit, a counter is initialized. If any damper is set with a negative time delay it will start prior to the fans with the set time period. All dampers start independently from one another. 
     The damper with the biggest negative delay starts first 
    The unit line of work is as follows: Unit Start --> Turn dampers (with negative delay) on --> negative delay over --> turn fans on --> start positive delay for dampers 
        */
    if (permission_for_the_unit_start_granted == true) // control the dampers and grant permission for the fans start when the pre-set time is negative
    {

        if (millis() > timer16 + (abs(minimum_delay()) + d1_time_delay) * 1000 && d1_run_once == true && d1_time_delay < 0 && d1_enabled == true) // start the damper
        {
            d1_run_once = false;
            turn_damper_1_on();
        }
        if (millis() > timer16 + (abs(d1_time_delay)) * 1000 && d1_run_once_2 == true && d1_time_delay < 0) //the damper grants permission to the fans after the pre-set period
        {
            d1_permission_fans_can_start = true;
            Serial.println("Damper 1 permission granted for fans start");
            d1_run_once_2 = false;
        }
        if (millis() > timer16 + (abs(minimum_delay()) + d2_time_delay) * 1000 && d2_run_once == true && d2_time_delay < 0 && d2_enabled == true) // start the damper
        {
            d2_run_once = false;
            turn_damper_2_on();
        }
        if (millis() > timer16 + (abs(d2_time_delay)) * 1000 && d2_run_once_2 == true && d2_time_delay < 0) //the damper grants permission to the fans after the pre-set period
        {
            d2_permission_fans_can_start = true;
            Serial.println("Damper 2 permission granted for fans start");
            d2_run_once_2 = false;
        }
        if (millis() > timer16 + (abs(minimum_delay()) + d3_time_delay) * 1000 && d3_run_once == true && d3_time_delay < 0 && d3_enabled == true) // start the damper
        {
            d3_run_once = false;
            turn_damper_3_on();
        }
        if (millis() > timer16 + (abs(d3_time_delay)) * 1000 && d3_run_once_2 == true && d3_time_delay < 0) //the damper grants permission to the fans after the pre-set period
        {
            d3_permission_fans_can_start = true;
            Serial.println("Damper 3 permission granted for fans start");
            d3_run_once_2 = false;
        }
        if (millis() > timer16 + (abs(minimum_delay()) + d4_time_delay) * 1000 && d4_run_once == true && d4_time_delay < 0 && d4_enabled == true) // start the damper
        {
            d4_run_once = false;
            turn_damper_4_on();
        }
        if (millis() > timer16 + (abs(d4_time_delay) * 1000) && d4_run_once_2 == true && d4_time_delay < 0) //the damper grants permission to the fans after the pre-set period
        {
            d4_permission_fans_can_start = true;
            Serial.println("Damper 4 permission granted for fans start");
            d4_run_once_2 = false;
        }
    }

    //if the dampers are not enabled they should grant permission to the fans instantly or else they will block the start of the fans
    if (d1_enabled == false && d1_run_once == true)
    {
        d1_permission_fans_can_start = true;
        Serial.println("Damper 1 permission granted for fans start");
        d1_run_once = false;
    }
    if (d2_enabled == false && d2_run_once == true)
    {
        d2_permission_fans_can_start = true;
        Serial.println("Damper 2 permission granted for fans start");
        d2_run_once = false;
    }
    if (d3_enabled == false && d3_run_once == true)
    {
        d3_permission_fans_can_start = true;
        Serial.println("Damper 3 permission granted for fans start");
        d3_run_once = false;
    }
    if (d4_enabled == false && d4_run_once == true)
    {
        d4_permission_fans_can_start = true;
        Serial.println("Damper 4 permission granted for fans start");
        d4_run_once = false;
    }
    if (permission_for_the_unit_start_granted == false)
    {
        if (d1_run_once == false || d2_run_once == false || d3_run_once == false || d4_run_once == false)
        {
            Serial.println("TEEEESTZ");
            dampers_control.turn_damper_1_off();
            dampers_control.turn_damper_2_off();
            dampers_control.turn_damper_3_off();
            dampers_control.turn_damper_4_off();
            d1_run_once = true;
            d2_run_once = true;
            d3_run_once = true;
            d4_run_once = true;
            d1_run_once_2 = true;
            d2_run_once_2 = true;
            d3_run_once_2 = true;
            d4_run_once_2 = true;
            d1_permission_fans_can_start = false;
            d2_permission_fans_can_start = false;
            d3_permission_fans_can_start = false;
            d4_permission_fans_can_start = false;
        }
    }
}

void Dampers::turn_damper_1_on() //switches the controller pin and sets the state to true for supply airline damper
{
    damper_1_on = true;
    digitalWrite(FP1, HIGH);
    Serial.println("Damper 1 - ON");
}
void Dampers::turn_damper_1_off() //switches the controller pin and sets the state to false for supply airline damper
{
    damper_1_on = false;
    digitalWrite(FP1, LOW);
    Serial.println("Damper 1 - OFF");
}
void Dampers::turn_damper_2_on() //switches the controller pin and sets the state to true for ambient airline damper
{
    damper_2_on = true;
    digitalWrite(FP2, HIGH);
    Serial.println("Damper 2 - ON");
}
void Dampers::turn_damper_2_off() //switches the controller pin and sets the state to false for ambient airline damper
{
    damper_2_on = false;
    digitalWrite(FP2, LOW);
    Serial.println("Damper 2 - OFF");
}
void Dampers::turn_damper_3_on() //switches the controller pin and sets the state to true for extract airline damper
{
    damper_3_on = true;
    digitalWrite(FP3, HIGH);
    Serial.println("Damper 3 - ON");
}
void Dampers::turn_damper_3_off() //switches the controller pin and sets the state to false for extract airline damper
{
    damper_3_on = false;
    digitalWrite(FP3, LOW);
    Serial.println("Damper 3 - OFF");
}
void Dampers::turn_damper_4_on() //switches the controller pin and sets the state to true for exhaust airline damper
{
    damper_4_on = true;
    digitalWrite(FP4, HIGH);
    Serial.println("Damper 4 - ON");
}
void Dampers::turn_damper_4_off() //switches the controller pin and sets the state to false for exhaust airline damper
{
    damper_4_on = false;
    digitalWrite(FP4, LOW);
    Serial.println("Damper 4 - OFF");
}

Dampers dampers_control;
