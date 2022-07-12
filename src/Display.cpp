#include <definitions.h>
#include "Display.h"
#include "Temperatures.h"
#include "Heaters.h"
#include "Logic.h"
#include "Nextion_commands.h"
#include "Settings.h"
#include "Overview.h"
#include "Temperature_settings.h"
#include "Heater_settings.h"
#include "Dampers.h"
#include <Fans.h>
#include <cmath>

void Display::working_stream()
{
    display_control.menu_navigation_Nextion();
    display_control.commands_from_display();
    display_control.lock_screen();
    display_control.idle();
    display_control.load_screen();
}

void Display::menu_navigation_Nextion()
{
    if (inData == p1_b0) // go to electric heaters screen
    {
        if (screen_lock_on == false || temporary_unlock == true)
        {
            if (heaters_manual_control_enabled == false)
            {
                nextion_commands.on_page(Heaters1_2);
                nextion_commands.go_to_page_Nextion(2);
            }
            if (heaters_manual_control_enabled == true)
            {
                nextion_commands.go_to_page_Nextion(3);
                heaters_control.refresh_page_p3();
                nextion_commands.on_page(3);
            }
        }
        if (screen_lock_on == true && temporary_unlock == false) //navigate to screen lock page
        {
            nextion_commands.go_to_page_Nextion(23);
            nextion_commands.on_page(23);
           
            if (heaters_manual_control_enabled == false)
            {
                going_to = 2;
            }
            if (heaters_manual_control_enabled == true)
            {
                going_to = 3;
            }
        }
    }
    if (inData == p1_b1) // go to fans screen
    {
        if (screen_lock_on == false || temporary_unlock == true) // navigate to home screen
        {
            nextion_commands.go_to_page_Nextion(6);
            nextion_commands.on_page(6);
            fans_control.Refresh_Screen();
        }
        if (screen_lock_on == true && temporary_unlock == false) //navigate to screen lock page
        {
            nextion_commands.go_to_page_Nextion(23);
            nextion_commands.on_page(23);
            going_to = 6;
        }
    }
    if (inData == p1_b2) // go to temperatures screen
    {
        if (screen_lock_on == false || temporary_unlock == true) // navigate to home screen
        {
            nextion_commands.go_to_page_Nextion(4);
            nextion_commands.on_page(4);
        }
        if (screen_lock_on == true && temporary_unlock == false) //navigate to screen lock page
        {
            nextion_commands.on_page(23);
            nextion_commands.go_to_page_Nextion(23);
            going_to = 4;
        }
    }
    if (inData == p1_b3) // go to settings screen
    {
        if (screen_lock_on == false || temporary_unlock == true) // navigate to home screen
        {
            nextion_commands.go_to_page_Nextion(7);
            nextion_commands.on_page(7);
        }
        if (screen_lock_on == true && temporary_unlock == false) //navigate to screen lock page
        {
            nextion_commands.go_to_page_Nextion(23);
            nextion_commands.on_page(23);
            going_to = 7;
        }
    }
    if (inData == p1_b5_command_5) // go to errors list page
    {
        if (screen_lock_on == false || screen_lock_on == true) // navigate alarms page
        {
            nextion_commands.go_to_page_Nextion(21);
            nextion_commands.on_page(21);
        }
        /*  if (screen_lock_on == true) //navigate to screen lock page
        {
            nextion_commands.go_to_page_Nextion(23);
            going_to = 21;
        }*/
    }
    if (inData == "reboot") // restarts the display and the controller
    {
        outData = "rest";
        nextion_commands.send_data_to_display();
        ESP.restart();
    }
    if (inData == p7_b0_command) // go to display settings screen
    {
        nextion_commands.go_to_page_Nextion(9);
        refresh_display_screen_settings();
    }
    if (inData == "master_unlock") // go to the master pin settings screen
    {
        nextion_commands.go_to_page_Nextion(13);
    }
    if (inData == p7_b2_command) // go to the temperature settings screen
    {
        nextion_commands.go_to_page_Nextion(10);
        temperature_settings_control.refresh_screen();
    }
    if (inData == p7_b3_command)
    {
        nextion_commands.go_to_page_Nextion(14);
        heaters_settings_control.refresh_page();
    }
    if (inData == p7_b4_command)
    {
        nextion_commands.go_to_page_Nextion(1);
        nextion_commands.on_page(1);
    }
    if (inData == p7_b6_command) //go to the overview screen
    {
        nextion_commands.go_to_page_Nextion(15);
        nextion_commands.on_page(15);
    }
    if (inData == p7_b5_command) // go to damper settings page
    {
        nextion_commands.go_to_page_Nextion(17);
        dampers_control.refresh_screen();
    }
    if (inData == p9_b4_command_905)
    {
        nextion_commands.go_to_page_Nextion(7);
    }
    if (inData == p23_b3_command || inData == p12_b3_command || inData == p13_b3_command) // navigate to the screen saver page with the "return" buttons from pin input pages
    {
        nextion_commands.on_page(24);
        //on_page_24 = true;
        //screen_loaded = false;
        nextion_commands.go_to_page_Nextion(24);
    }
}
void Display::commands_from_display()
{
    if (inData == p1_bt0_command_on_2) // turn main switch ON
    {
        permission_for_the_unit_start_granted = true;
        timer16 = millis(); //initiate a counter for the start of the dampers if the dampers start before the fans
    }
    if (inData == p1_bt0_command_off_1) // turn main switch OFF
    {
        permission_for_the_unit_start_granted = false;
    }
    if (inData == p9_b1_command_902) // increase display brightness
    {
        if (display_brightness < 100)
        {
            display_brightness = display_brightness + 10;
            nextion_commands.set_text_of_screen_component(p9_t4_text, String(display_brightness) + "%");
            outData = "dims=" + String(display_brightness);
            nextion_commands.send_data_to_display();
        }
    }
    if (inData == p9_b0_command_901) // decrease display brightness
    {
        if (display_brightness >= 30)
        {
            display_brightness = display_brightness - 10;
            nextion_commands.set_text_of_screen_component(p9_t4_text, String(display_brightness) + "%");
            outData = "dims=" + String(display_brightness);
            nextion_commands.send_data_to_display();
        }
    }
    if (inData == p9_c0_on_910) //turn on the "auto off" screen feature
    {
        display_auto_off = true;
        Serial.println("Display sleep function on");
        display_control.turn_screen_sleep_mode_on_or_off();
    }
    if (inData == p9_c0_off_911) //turn off the "auto off" screen feature
    {
        display_auto_off = false;
        Serial.println("Display sleep function off");
        display_control.turn_screen_sleep_mode_on_or_off();
    }
    if (inData == p9_b2_command_903) //increase the time before the screen sleeps
    {
        if (display_auto_off_period < 300)
        {
            display_auto_off_period = display_auto_off_period + 5;
            display_control.refresh_display_screen_settings();
            display_control.turn_screen_sleep_mode_on_or_off();
        }
    }
    if (inData == p9_b3_command_904) //decrease the time before the screen sleeps
    {
        if (display_auto_off_period >= 25)
        {
            display_auto_off_period = display_auto_off_period - 5;
            display_control.refresh_display_screen_settings();
            display_control.turn_screen_sleep_mode_on_or_off();
        }
    }
    if (inData == p9_c1_on_906) // navigate to the pin input page
    {
        //screen_lock_on = true;
        nextion_commands.go_to_page_Nextion(11);
    }
    if (inData == p9_c1_off_907) //turn the screen lock off, navigate to the unlock page
    {

        nextion_commands.go_to_page_Nextion(12);
        nextion_commands.on_page(12);
    }
    if (inData == p9_c2_on) // calibrate the display
    {
        outData = "touch_j";
        nextion_commands.send_data_to_display();
    }
    /*   if (inData == p22_b4_command) // navigate to the PIN unlock page
    {
        on_page_22 = false;
        on_page_23 = true;
        nextion_commands.go_to_page_Nextion(23);
    }*/
    if (inData.substring(0, 4) == "pin_")
    {
        display_control.compare_screen_lock_pin();
        display_control.unlock_screen();
    }
    // the next functions/methods handle the pin verification and storage
    if (inData.substring(0, 5) == "pin1_")
    {
        screen_lock_pin_first_attemt = inData.substring(5);
        Serial.println(screen_lock_pin_first_attemt);

        if (screen_lock_pin_first_attemt.length() == 4)
        {
            nextion_commands.set_visibility_on_Nextion("b15", 0);
            nextion_commands.set_visibility_on_Nextion("b11", 1);
            nextion_commands.set_visibility_on_Nextion("t1", 0);
            nextion_commands.set_visibility_on_Nextion("t2", 1);
            outData = "t0.txt=\"" + String("") + "\"";
            nextion_commands.send_data_to_display();
        }
        else
        {
            nextion_commands.set_visibility_on_Nextion("t0", 0);
            nextion_commands.set_visibility_on_Nextion("t3", 1);
            delay(2000);
            nextion_commands.set_visibility_on_Nextion("t3", 0);
            nextion_commands.set_visibility_on_Nextion("t0", 1);
        }
    }
    if (inData.substring(0, 5) == "pin2_") //lock screen if second pin input matches the first
    {
        screen_lock_pin_confirm = inData.substring(5);
        if (screen_lock_pin_confirm == screen_lock_pin_first_attemt)
        {
            Serial.println("pins are matching and can be saved to the SPIFFS");
            nextion_commands.set_visibility_on_Nextion("t5", 1);
            delay(2000);
            nextion_commands.set_visibility_on_Nextion("t5", 0);
            screen_lock_pin = screen_lock_pin_confirm;
            screen_lock_on = true;
            logic_control.check_and_save_data_display_settings();
            nextion_commands.go_to_page_Nextion(9);
            refresh_display_screen_settings();
        }
        else
        {
            nextion_commands.set_visibility_on_Nextion("t4", 1);
            delay(2000);
            nextion_commands.set_visibility_on_Nextion("t4", 0);
        }
    }
    if (inData.substring(0, 6) == "m_pin_")
    {
        master_pin_input = inData.substring(6);
        display_control.unlock_screen_with_master_pin();
    }
}
void Display::refresh_display_screen_settings()
{
    nextion_commands.set_text_of_screen_component(p9_t4_text, String(display_brightness) + "%");
    nextion_commands.set_text_of_screen_component(p9_t5_text, String(display_auto_off_period) + "s");
    nextion_commands.set_value_of_screen_component(p9_c0_value, display_auto_off);
    nextion_commands.set_value_of_screen_component(p9_c1_value, screen_lock_on);
    //   nextion_commands.set_value_of_screen_component(p9_c0, display_auto_on_off_state);
    //nextion_commands.set_value_of_screen_component(p9_c1, display_screen_lock_on_off_state);
}
void Display::compare_screen_lock_pin() // compare pin and disable the scree lock if input is correct
{
    if (on_page_number == disable_pin_12)
    {
        String _pin_input;
        _pin_input = inData.substring(4);
        if (_pin_input == screen_lock_pin)
        {
            screen_lock_on = false;
            screen_lock_pin = "";
            nextion_commands.go_to_page_Nextion(9);
            display_control.refresh_display_screen_settings();
            number_of_tries = 3;
        }
        else
        {
            number_of_tries--;
            if (number_of_tries < 4)
            {

                nextion_commands.set_visibility_on_Nextion("t2", 1);
                delay(2000);
                nextion_commands.set_visibility_on_Nextion("t2", 0);
                nextion_commands.set_visibility_on_Nextion("b11", 0);
                nextion_commands.set_visibility_on_Nextion("t3", 1);
                nextion_commands.set_visibility_on_Nextion("n0", 1);
                outData = "n0.val=" + String(number_of_tries);
                nextion_commands.send_data_to_display();
            }
            if (number_of_tries == 0)
            {
                nextion_commands.go_to_page_Nextion(1);
                display_control.refresh_display_screen_settings();
                number_of_tries = 3;
            }
        }
    }
}
void Display::unlock_screen() // compare pin and unlock the screen the scree lock if input is correct
{
    if (on_page_number == unlock_screen_23)

    {
        outData = "dims=" + String(display_brightness);
        nextion_commands.send_data_to_display();
        String _pin_input;
        _pin_input = inData.substring(4);
        if (_pin_input == screen_lock_pin)
        {
            Serial.println("PIN matched");
            temporary_unlock = true;
            nextion_commands.on_page(going_to);
            nextion_commands.go_to_page_Nextion(going_to);
            number_of_tries = 3;
            going_to = 0;
        }
        else
        {
            number_of_tries--;
            if (number_of_tries < 4)
            {

                nextion_commands.set_visibility_on_Nextion("t2", 1);
                delay(2000);
                nextion_commands.set_visibility_on_Nextion("t2", 0);
                nextion_commands.set_visibility_on_Nextion("b11", 0);
                nextion_commands.set_visibility_on_Nextion("t3", 1);
                nextion_commands.set_visibility_on_Nextion("n0", 1);
                outData = "n0.val=" + String(number_of_tries);
                nextion_commands.send_data_to_display();
            }
            if (number_of_tries == 0)
            {
                //on_page_24 = true;
                screen_loaded = false;
                nextion_commands.on_page(24);
                nextion_commands.go_to_page_Nextion(24);
                number_of_tries = 3;
                //on_page_23 = false;
                display_control.lock_screen();
                going_to = 0;
            }
        }
    }
}
void Display::unlock_screen_with_master_pin()
{

    if (master_pin_input == master_pin)
    {
        screen_lock_on = false;
        screen_lock_pin = "";
        nextion_commands.go_to_page_Nextion(9);
        display_control.refresh_display_screen_settings();
        number_of_tries_master_pin = 3;
    }
    else
    {
        number_of_tries_master_pin--;
        if (number_of_tries_master_pin < 4)
        {
            nextion_commands.set_visibility_on_Nextion("t2", 1);
            delay(2000);
            nextion_commands.set_visibility_on_Nextion("t2", 0);
            nextion_commands.set_value_of_screen_component(p13_n0, number_of_tries_master_pin);
            nextion_commands.set_visibility_on_Nextion("n0", 1);
            nextion_commands.set_visibility_on_Nextion("t3", 1);
        }
        if (number_of_tries_master_pin == 0)
        {
            nextion_commands.go_to_page_Nextion(1);
            //display_control.load_display_screen_settings();
            number_of_tries_master_pin = 3;
        }
    }
}
void Display::turn_screen_sleep_mode_on_or_off()
{
    if (display_auto_off == true)
    {
        outData = "thsp=" + String(display_auto_off_period);
        nextion_commands.send_data_to_display();
        outData = "thup=" + String(1);
        nextion_commands.send_data_to_display();
    }
    if (display_auto_off == false)
    {
        outData = "thsp=" + String(0);
        nextion_commands.send_data_to_display();
        outData = "thup=" + String(0);
        nextion_commands.send_data_to_display();
    }
}
void Display::lock_screen() // screen saver screen
{
    if (screen_lock_on == true)
    {
        if (display_auto_off == true)
        {
            screen_lock_interval = display_auto_off_period * 1000 - 5000;
        }
        if (display_auto_off == false)
        {
            screen_lock_interval = display_auto_off_period;
        }
        if (millis() > screen_lock_interval * 1000 + timer10 && on_page_number != Screen_saver_24)
        {
            nextion_commands.go_to_page_Nextion(24);
            nextion_commands.send_data_to_display();
            nextion_commands.on_page(24);
            temporary_unlock = false;
            timer10 = millis();

            //set up variables needed for screen loading of different pages
            fans_screen_loaded = false;
        }
    }
}
void Display::idle()
{
    if (screen_lock_on == false && display_auto_off == false && on_page_number != Screen_saver_24)
    {
        if (millis() > timer11 + display_auto_off_period * 1000)
        {
            nextion_commands.go_to_page_Nextion(24);
            nextion_commands.on_page(24);
            fans_screen_loaded = false;
            timer11 = millis();
        }
    }
}

void Display::load_screen()
{
    if (on_page_number == 1 && main_screen_loaded == false)
    {
        nextion_commands.set_value_of_screen_component(p10_bt0_value, permission_for_the_unit_start_granted);
        main_screen_loaded = true;
    }
    if (on_page_number != 1 && main_screen_loaded == true)
    {
        main_screen_loaded = false;
    }
}
Display display_control;
