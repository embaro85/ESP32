#include <definitions.h>
#include "Display.h"
#include "Temperatures.h"
#include "Heaters.h"
#include "Logic.h"
#include "Nextion_commands.h"
#include "Settings.h"
#include "Overview.h"
#include "Temperature_settings.h"

void Display::working_stream()
{
    display_control.menu_navigation_Nextion();
    display_control.display_settings_menu();
    display_control.send_threshold_temperature_to_screen_field();
    display_control.send_everything_off_threshold_temperature_to_screen_field();
    display_control.send_h1_power_to_screen_field();
    display_control.send_h2_power_to_screen_field();
    display_control.send_h3_power_to_screen_field();
}

//switches only the button value and text on the display, not the heater itself.
void h1_switch_Nextion_btn_on_or_off(String switch_on_or_off)
{
    if (switch_on_or_off == "ON")
    {
        outData = "h1btn.val=1";
        nextion_commands.send_data_to_display();
        outData = "h1btn.txt=\"" + String("ON") + "\"";
        nextion_commands.send_data_to_display();
    }
    if (switch_on_or_off == "OFF")
    {
        outData = "h1btn.val=0";
        nextion_commands.send_data_to_display();
        outData = "h1btn.txt=\"" + String("OFF") + "\"";
        nextion_commands.send_data_to_display();
    }
    Serial.println(outData); //for debugging
}
//switches only the button value and text on the display, not the heater itself.
void h2_switch_Nextion_btn_on_or_off(String switch_on_or_off)
{
    if (switch_on_or_off == "ON")
    {
        outData = "h2btn.val=1";
        nextion_commands.send_data_to_display();
        outData = "h2btn.txt=\"" + String("ON") + "\"";
        nextion_commands.send_data_to_display();
    }
    if (switch_on_or_off == "OFF")
    {
        outData = "h2btn.val=0";
        nextion_commands.send_data_to_display();
        outData = "h2btn.txt=\"" + String("OFF") + "\"";
        nextion_commands.send_data_to_display();
    }
    Serial.println(outData); //for debugging
}
//switches only the button value and text on the display, not the heater itself.
void h3_switch_Nextion_btn_on_or_off(String switch_on_or_off)
{
    if (switch_on_or_off == "ON")
    {
        outData = "h3btn.val=1";
        nextion_commands.send_data_to_display();
        outData = "h3btn.txt=\"" + String("ON") + "\"";
        nextion_commands.send_data_to_display();
    }
    if (switch_on_or_off == "OFF")
    {
        outData = "h3btn.val=0";
        nextion_commands.send_data_to_display();
        outData = "h3btn.txt=\"" + String("OFF") + "\"";
        nextion_commands.send_data_to_display();
    }
    Serial.println(outData); //for debugging
}
//set the  heaters manual control page button states
void set_properties_page_manual_control()
{
    h_manual_control_state_new = true;
    //Heater 1
    if (heater1_on_off_state == true)
    {
        h1_switch_Nextion_btn_on_or_off("ON");
    }
    else if (heater1_on_off_state == false)
    {
        h1_switch_Nextion_btn_on_or_off("OFF");
    }
    //Heater 2
    if (heater2_on_off_state == true)
    {
        h2_switch_Nextion_btn_on_or_off("ON");
    }
    else if (heater2_on_off_state == false)
    {
        h2_switch_Nextion_btn_on_or_off("OFF");
    }
    //Heater 3
    if (heater3_on_off_state == true)
    {
        h3_switch_Nextion_btn_on_or_off("ON");
    }
    else if (heater3_on_off_state == false)
    {
        h3_switch_Nextion_btn_on_or_off("OFF");
    }
    outData = "Heaters2.bhmanual.val=" + String(h_manual_control_state_new); // set the check button to checked
    nextion_commands.send_data_to_display();

    Serial.println(outData);
}

void Display::Refresh_Fans_Screen()
{
    outData = p6_tf1 + String(fan1_0_10_voltage_input * 10, 0) + String(" %") + "\"";
    nextion_commands.send_data_to_display();
    outData = p6_tf2 + String(fan2_0_10_voltage_input * 10, 0) + String(" %") + "\"";
    nextion_commands.send_data_to_display();
    nextion_commands.set_value_of_screen_component(p6_bt0_value, f1_on_off_state);
    Serial.println("Fan 1 state is: " + String(f1_on_off_state));
    nextion_commands.set_value_of_screen_component(p6_bt1_value, f2_on_off_state);
    Serial.println("Fan 2 state is: " + String(f2_on_off_state));
    Serial.println(f1_on_off_state);
    Serial.println(f2_on_off_state);
}

void Display::menu_navigation_Nextion()
{
    if (inData == "f_m")
    {
        nextion_commands.go_to_page_Nextion(6);
        display_control.Refresh_Fans_Screen();
    }
    if (inData == go_to_page_temperatures_p4)
    {
        nextion_commands.go_to_page_Nextion(4);
        on_page_4 = true;
    }
    if (inData == go_to_page_temperatures_p5)
    {
        nextion_commands.go_to_page_Nextion(5);
    }
    if (inData == go_to_page_heaters_p2)
    {
        nextion_commands.go_to_page_Nextion(2);
        on_page_2 = true;
        /*if (h_manual_control_state_new == true)
        {
            nextion_commands.go_to_page_Nextion(3);
           heaters_control.resfresh_page();
            //set_properties_page_manual_control();
        }
        else if (h_manual_control_state_new == false)
        {
            nextion_commands.go_to_page_Nextion(2);
            //set_properties_page_temperature_control();
            heaters_control.resfresh_page();
        }*/
    }
    if (inData == go_to_page_heaters_warning_p8) //navigates to warning page
    {
        nextion_commands.go_to_page_Nextion(8);
    }
    if (inData == "ok_h_man") //turns the manual control ON
    {
        nextion_commands.go_to_page_Nextion(3);
        set_properties_page_manual_control();
        if (heater1_on_off_state == true)
        {
            h1_switch_Nextion_btn_on_or_off("ON");
        }
        if (heater1_on_off_state == false)
        {
            h1_switch_Nextion_btn_on_or_off("OFF");
        }
        if (heater2_on_off_state == true)
        {
            h2_switch_Nextion_btn_on_or_off("ON");
        }
        if (heater2_on_off_state == false)
        {
            h2_switch_Nextion_btn_on_or_off("OFF");
        }
        if (heater3_on_off_state == true)
        {
            h3_switch_Nextion_btn_on_or_off("ON");
        }
        if (heater3_on_off_state == false)
        {
            h3_switch_Nextion_btn_on_or_off("OFF");
        }
    }
    if (inData == "h_man_off" || inData == "back_h_man") // turns the manual control OFF and sets the page properties
    {
        h_manual_control_state_new = false;
        nextion_commands.go_to_page_Nextion(2);
        //set_properties_page_temperature_control();
        heaters_control.resfresh_page();
    }
    if (inData == "s_m")
    {
        nextion_commands.go_to_page_Nextion(7);
    }
    if (inData == "h1_off")
    {
        heater1_on_off_state = false;
        h1_switch_Nextion_btn_on_or_off("OFF");
    }
    if (inData == "h1_on")
    {
        heater1_on_off_state = true;
        h1_switch_Nextion_btn_on_or_off("ON");
    }
    if (inData == "reboot")
    {
        outData = "rest";
        nextion_commands.send_data_to_display();
    }
    if (inData == "display")
    {
        nextion_commands.go_to_page_Nextion(9);
        load_display_screen_settings();
    }
    if (inData == "master_unlock")
    {
        nextion_commands.go_to_page_Nextion(13);
    }
    if (inData == go_to_page_set_temperatures_p10)
    {
        nextion_commands.go_to_page_Nextion(10);
        temperature_settings_control.refresh_screen();
    }
    if (inData == info_button_push_p10_t4)
    {
        nextion_commands.set_visibility_on_Nextion("t5", 1);
        nextion_commands.set_visibility_on_Nextion("b2", 0);
    }
    if (inData == turn_off_info_text_p10_t5_and_t6)
    {
        nextion_commands.set_visibility_on_Nextion("t5", 0);
        nextion_commands.set_visibility_on_Nextion("t6", 0);
        //   nextion_commands.set_visibility_on_Nextion("b2", 0);
    }
    if (inData == info_button_push_p10_t7)
    {
        nextion_commands.set_visibility_on_Nextion("t6", 1);
        nextion_commands.set_visibility_on_Nextion("b2", 0);
    }
    if (inData == go_to_heaters_settings_page_p14)
    {
        nextion_commands.go_to_page_Nextion(14);
    }
    if (inData == p7_b6_command)
    {
        nextion_commands.go_to_page_Nextion(15);
        on_page_15 = true;
    }
}
void Display::refresh_heaters_screen()
{
    h_manual_control_state_new = false;
    //set_properties_page_temperature_control();
    heaters_control.resfresh_page();
}
void Display::calculate_auto_off_period()
{
    auto_off_period = ten_seconds + twenty_seconds + sixty_seconds + hudredAndTwenty_seconds;
    Serial.println(auto_off_period);
    outData = "t2.txt=\"" + String(auto_off_period) + " seconds" + "\"";
    nextion_commands.send_data_to_display();
}
void Display::display_settings_menu()
{
    if (inData == "pl_display_brightness")
    {
        if (display_brightness < 100)
        {
            display_brightness = display_brightness + 10;
            nextion_commands.set_value_of_screen_component(p9_h0, display_brightness);
            nextion_commands.set_value_of_screen_component(p9_n0, display_brightness);
            outData = "dims=" + String(display_brightness);
            nextion_commands.send_data_to_display();
            Serial.println(display_brightness); //for debugging
        }
    }
    if (inData == "mi_display_brightness")
    {
        if (display_brightness >= 30)
        {
            display_brightness = display_brightness - 10;
            nextion_commands.set_value_of_screen_component(p9_h0, display_brightness);
            nextion_commands.set_value_of_screen_component(p9_n0, display_brightness);
            outData = "dims=" + String(display_brightness);
            nextion_commands.send_data_to_display();
            Serial.println(display_brightness); //for debugging
        }
    }
    if (inData == "auto_off_on")
    {
        nextion_commands.set_visibility_on_Nextion("bt0", 1);
        nextion_commands.set_visibility_on_Nextion("bt1", 1);
        nextion_commands.set_visibility_on_Nextion("bt2", 1);
        nextion_commands.set_visibility_on_Nextion("bt3", 1);
        nextion_commands.set_visibility_on_Nextion("bt7", 1);
        nextion_commands.set_visibility_on_Nextion("t2", 1);
        nextion_commands.set_visibility_on_Nextion("t3", 0);
        nextion_commands.set_visibility_on_Nextion("c1", 0);
    }
    if (inData == "auto_off_off")
    {
        nextion_commands.set_visibility_on_Nextion("bt0", 0);
        nextion_commands.set_visibility_on_Nextion("bt1", 0);
        nextion_commands.set_visibility_on_Nextion("bt2", 0);
        nextion_commands.set_visibility_on_Nextion("bt3", 0);
        nextion_commands.set_visibility_on_Nextion("b7", 0);
        nextion_commands.set_visibility_on_Nextion("t2", 0);
        nextion_commands.set_visibility_on_Nextion("t3", 1);
        nextion_commands.set_visibility_on_Nextion("c1", 1);
        auto_off_period = 0;
        display_auto_on_off_state = false;
        outData = "thsp=0";
        nextion_commands.send_data_to_display();
        outData = "thup=0";
    }
    if (inData == "time_ok")
    {
        nextion_commands.set_visibility_on_Nextion("bt0", 0);
        nextion_commands.set_visibility_on_Nextion("bt1", 0);
        nextion_commands.set_visibility_on_Nextion("bt2", 0);
        nextion_commands.set_visibility_on_Nextion("bt3", 0);
        nextion_commands.set_visibility_on_Nextion("b7", 0);
        nextion_commands.set_visibility_on_Nextion("t2", 0);
        nextion_commands.set_visibility_on_Nextion("t3", 1);
        nextion_commands.set_visibility_on_Nextion("c1", 1);
        if (auto_off_period > 0)
        {
            //store the value
            outData = "thsp=" + String(auto_off_period);
            nextion_commands.send_data_to_display();
            outData = "thup=1";
            nextion_commands.send_data_to_display();
            display_auto_on_off_state = true;
            outData = "t4.txt=\"" + String(auto_off_period) + "s" + "\"";
            nextion_commands.send_data_to_display();
        }
        else
        {
            outData = "thsp=0";
            nextion_commands.send_data_to_display();
            display_auto_on_off_state = false;
        }
    }
    if (inData == "10_seconds")
    {
        ten_seconds = 10;
        calculate_auto_off_period();
    }
    if (inData == "minus_10_seconds")
    {
        ten_seconds = 0;
        calculate_auto_off_period();
    }
    if (inData == "20_seconds")
    {
        twenty_seconds = 20;
        calculate_auto_off_period();
    }
    if (inData == "minus_20_seconds")
    {
        twenty_seconds = 0;
        calculate_auto_off_period();
    }
    if (inData == "60_seconds")
    {
        sixty_seconds = 60;
        calculate_auto_off_period();
    }
    if (inData == "minus_60_seconds")
    {
        sixty_seconds = 0;
        calculate_auto_off_period();
    }
    if (inData == "120_seconds")
    {
        hudredAndTwenty_seconds = 120;
        calculate_auto_off_period();
    }
    if (inData == "minus_120_seconds")
    {
        hudredAndTwenty_seconds = 0;
        calculate_auto_off_period();
    }
    if (inData == "d_lock_on")
    {
        nextion_commands.go_to_page_Nextion(11);
    }
    if (inData == "d_lock_off")
    {
        nextion_commands.go_to_page_Nextion(12);
    }
    if (inData.substring(0, 4) == "pin_")
    {
        compare_screen_lock_pin();
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
    if (inData.substring(0, 5) == "pin2_")
    {
        screen_lock_pin_confirm = inData.substring(5);
        if (screen_lock_pin_confirm == screen_lock_pin_first_attemt)
        {
            Serial.println("pins are matching and can be saved to the SPIFFS");
            nextion_commands.set_visibility_on_Nextion("t5", 1);
            delay(2000);
            nextion_commands.set_visibility_on_Nextion("t5", 0);
            screen_lock_pin = screen_lock_pin_confirm;
            display_screen_lock_on_off_state = true;
            logic_control.check_and_save_data_display_settings();
            nextion_commands.go_to_page_Nextion(9);
            load_display_screen_settings();
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
void Display::load_display_screen_settings()
{
    nextion_commands.set_value_of_screen_component(p9_n0, display_brightness);
    nextion_commands.set_value_of_screen_component(p9_h0, display_brightness);
    nextion_commands.set_value_of_screen_component(p9_c0, display_auto_on_off_state);
    nextion_commands.set_value_of_screen_component(p9_c1, display_screen_lock_on_off_state);
    outData = "t4.txt=\"" + String(auto_off_period) + "s" + "\"";
    nextion_commands.send_data_to_display();
}
void Display::compare_screen_lock_pin()
{
    String _pin_input;
    _pin_input = inData.substring(4);
    if (_pin_input == screen_lock_pin)
    {
        display_screen_lock_on_off_state = false;
        screen_lock_pin = "";
        nextion_commands.go_to_page_Nextion(9);
        load_display_screen_settings();
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
            nextion_commands.go_to_page_Nextion(9);
            load_display_screen_settings();
            number_of_tries = 3;
        }
    }
}
void Display::unlock_screen_with_master_pin()
{

    if (master_pin_input == master_pin)
    {
        display_screen_lock_on_off_state = false;
        screen_lock_pin = "";
        nextion_commands.go_to_page_Nextion(9);
        display_control.load_display_screen_settings();
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
void Display::send_threshold_temperature_to_screen_field()
{
    if (!temperatures_control.handle_threshold_temperature())
    {
        outData = p10_t1 + String(threshold_temperature) + "\"";
        nextion_commands.send_data_to_display();
        nextion_commands.set_visibility_on_Nextion("t5", 0);
        nextion_commands.set_visibility_on_Nextion("t6", 0);
        nextion_commands.set_visibility_on_Nextion("b3", 1);
    }
}
void Display::send_everything_off_threshold_temperature_to_screen_field()
{
    if (!temperatures_control.handle_everything_off_threshold_temperature())
    {
        outData = p10_t3 + String(turn_everything_off_temperature_threshold) + "\"";
        nextion_commands.send_data_to_display();
        nextion_commands.set_visibility_on_Nextion("t5", 0);
        nextion_commands.set_visibility_on_Nextion("t6", 0);
        nextion_commands.set_visibility_on_Nextion("b2", 1);
    }
}

void Display::send_h1_power_to_screen_field()
{
    float _h1_power = h1_power;
    settings_control.increase_decrease_heater_1_power();
    if (_h1_power != h1_power)
    {
        outData = "t3.txt=\"" + String(h1_power) + "kW" + "\"";
        nextion_commands.send_data_to_display();
        Serial.println("Heater 1 power is: " + String(h1_power));
    }
}
void Display::send_h2_power_to_screen_field()
{
    float _h2_power = h2_power;
    settings_control.increase_decrease_heater_2_power();
    if (_h2_power != h2_power)
    {
        outData = "t4.txt=\"" + String(h2_power) + "kW" + "\"";
        nextion_commands.send_data_to_display();
        Serial.println("Heater 2 power is: " + String(h2_power));
    }
}
void Display::send_h3_power_to_screen_field()
{
    float _h3_power = h3_power;
    settings_control.increase_decrease_heater_3_power();
    if (_h3_power != h3_power)
    {
        outData = "t5.txt=\"" + String(h3_power) + "kW" + "\"";
        nextion_commands.send_data_to_display();
        Serial.println("Heater 3 power is: " + String(h3_power));
    }
}
void Display::refresh_heaters_settings_screen()
{
    outData = "t3.txt=\"" + String(h1_power) + "kW" + "\"";
    nextion_commands.send_data_to_display();
    Serial.println("yes");
    outData = "t4.txt=\"" + String(h2_power) + "kW" + "\"";
    nextion_commands.send_data_to_display();
    outData = "t5.txt=\"" + String(h3_power) + "kW" + "\"";
    nextion_commands.send_data_to_display();
    nextion_commands.set_value_of_screen_component(p14_c0, h1_available);
    nextion_commands.set_value_of_screen_component(p14_c1, h2_available);
    nextion_commands.set_value_of_screen_component(p14_c2, h3_available);
}

Display display_control;
