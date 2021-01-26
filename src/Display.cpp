#include <definitions.h>
#include "Display.h"
#include "Temperatures.h"
#include "Heaters.h"
#include "Logic.h"
#include "Nextion_commands.h"
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
// set the heaters temperature control page button states and text fields
void set_properties_page_temperature_control()
{

    if (heater1_on_off_state == true)
    {
        outData = "Heaters1.th1.txt=\"" + String("включен") + "\"";
        nextion_commands.send_data_to_display();
    }
    else if (heater1_on_off_state == false)
    {
        outData = "Heaters1.th1.txt=\"" + String("OFF") + "\"";
        nextion_commands.send_data_to_display();
    }
    else if (heater2_on_off_state == true)
    {
        outData = "Heaters1.th2.txt=\"" + String("ON") + "\"";
        nextion_commands.send_data_to_display();
    }
    else if (heater2_on_off_state == false)
    {
        outData = "Heaters1.th2.txt=\"" + String("OFF") + "\"";
        nextion_commands.send_data_to_display();
    }
    else if (heater3_on_off_state == true)
    {
        outData = "Heaters1.th3.txt=\"" + String("ON") + "\"";
        nextion_commands.send_data_to_display();
    }
    else if (heater3_on_off_state == false)
    {
        outData = "Heaters1.th3.txt=\"" + String("OFF") + "\"";
        nextion_commands.send_data_to_display();
    }
    outData = "Heaters1.bhmanual.val=" + String(h_manual_control_state_new); // set the check button to unchecked
    nextion_commands.send_data_to_display();
}

void Display::Refresh_Fans_Screen(String Nextion_Text_Field_f1, float f1_control_voltage, String Nextion_Text_Field_f2, float f2_control_voltage, String ref_fans_screen_cmd)
{
    if (ref_fans_screen_cmd == inData)
    {
        nextion_commands.go_to_page_Nextion(6);
        outData = Nextion_Text_Field_f1 + String(f1_control_voltage, 1) + String(" V") + "\"";
        nextion_commands.send_data_to_display();
        Serial.println(outData);
        outData = Nextion_Text_Field_f2 + String(f2_control_voltage, 1) + String(" V") + "\"";
        nextion_commands.send_data_to_display();
        nextion_commands.set_value_of_screen_component("bt0", f1_on_off_state);
        Serial.println("Fan 1 state is: " + String(f1_on_off_state));
        nextion_commands.set_value_of_screen_component("bt1", f2_on_off_state);
        Serial.println("Fan 2 state is: " + String(f2_on_off_state));
    }
}

void Display::menu_navigation_Nextion()
{
    if (inData == "f_m")
    {
        // go_to_page_Nextion(6);
    }
    if (inData == "t_m")
    {
        nextion_commands.go_to_page_Nextion(4);
    }
    if (inData == "t_m_1")
    {
        nextion_commands.go_to_page_Nextion(5);
    }
    if (inData == "h_m")
    {
        if (h_manual_control_state_new == true)
        {
            nextion_commands.go_to_page_Nextion(3);
            set_properties_page_manual_control();
        }
        else if (h_manual_control_state_new == false)
        {
            nextion_commands.go_to_page_Nextion(2);
            set_properties_page_temperature_control();
        }
        Serial.println(outData);
    }
    if (inData == "h_man_on") //navigates to warning page
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
        set_properties_page_temperature_control();
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
    if (inData == go_to_page_set_temperatures)
    {
        nextion_commands.go_to_page_Nextion(10);

    }
}
void Display::refresh_heaters_screen()
{
    h_manual_control_state_new = false;
    set_properties_page_temperature_control();
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
            nextion_commands.set_visibility_on_Nextion("b11",0);
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


Display display_control;
