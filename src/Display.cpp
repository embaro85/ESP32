#include <definitions.h>
#include "Display.h"
#include "Temperatures.h"
#include "Heaters.h"
//switches only the button value and text on the display, not the heater itself.
void h1_switch_Nextion_btn_on_or_off(String switch_on_or_off)
{
    if (switch_on_or_off == "ON")
    {
        outData = "h1btn.val=1";
        display_control.sendDataToDisplay();
        outData = "h1btn.txt=\"" + String("ON") + "\"";
        display_control.sendDataToDisplay();
    }
    if (switch_on_or_off == "OFF")
    {
        outData = "h1btn.val=0";
        display_control.sendDataToDisplay();
        outData = "h1btn.txt=\"" + String("OFF") + "\"";
        display_control.sendDataToDisplay();
    }
    Serial.println(outData); //for debugging
}
//switches only the button value and text on the display, not the heater itself.
void h2_switch_Nextion_btn_on_or_off(String switch_on_or_off)
{
    if (switch_on_or_off == "ON")
    {
        outData = "h2btn.val=1";
        display_control.sendDataToDisplay();
        outData = "h2btn.txt=\"" + String("ON") + "\"";
        display_control.sendDataToDisplay();
    }
    if (switch_on_or_off == "OFF")
    {
        outData = "h2btn.val=0";
        display_control.sendDataToDisplay();
        outData = "h2btn.txt=\"" + String("OFF") + "\"";
        display_control.sendDataToDisplay();
    }
    Serial.println(outData); //for debugging
}
//switches only the button value and text on the display, not the heater itself.
void h3_switch_Nextion_btn_on_or_off(String switch_on_or_off)
{
    if (switch_on_or_off == "ON")
    {
        outData = "h3btn.val=1";
        display_control.sendDataToDisplay();
        outData = "h3btn.txt=\"" + String("ON") + "\"";
        display_control.sendDataToDisplay();
    }
    if (switch_on_or_off == "OFF")
    {
        outData = "h3btn.val=0";
        display_control.sendDataToDisplay();
        outData = "h3btn.txt=\"" + String("OFF") + "\"";
        display_control.sendDataToDisplay();
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
    display_control.sendDataToDisplay();
    Serial.println(outData);
}
// set the heaters temperature control page button states and text fields
void set_properties_page_temperature_control()
{

    if (heater1_on_off_state == true)
    {
        outData = "Heaters1.th1.txt=\"" + String("включен") + "\"";
        display_control.sendDataToDisplay();
    }
    else if (heater1_on_off_state == false)
    {
        outData = "Heaters1.th1.txt=\"" + String("OFF") + "\"";
        display_control.sendDataToDisplay();
    }
    else if (heater2_on_off_state == true)
    {
        outData = "Heaters1.th2.txt=\"" + String("ON") + "\"";
        display_control.sendDataToDisplay();
    }
    else if (heater2_on_off_state == false)
    {
        outData = "Heaters1.th2.txt=\"" + String("OFF") + "\"";
        display_control.sendDataToDisplay();
    }
    else if (heater3_on_off_state == true)
    {
        outData = "Heaters1.th3.txt=\"" + String("ON") + "\"";
        display_control.sendDataToDisplay();
    }
    else if (heater3_on_off_state == false)
    {
        outData = "Heaters1.th3.txt=\"" + String("OFF") + "\"";
        display_control.sendDataToDisplay();
    }
    outData = "Heaters1.bhmanual.val=" + String(h_manual_control_state_new); // set the check button to unchecked
    display_control.sendDataToDisplay();
}

void Display::sendDataToDisplay()
{ //send data to display
    Serial2.print(outData);
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.write(0xff);
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
void Display::Refresh_Fans_Screen(String Nextion_Text_Field_f1, float f1_control_voltage, String Nextion_Text_Field_f2, float f2_control_voltage, String ref_fans_screen_cmd)
{
    if (ref_fans_screen_cmd == inData)
    {
        go_to_page_Nextion(6);
        outData = Nextion_Text_Field_f1 + String(f1_control_voltage, 1) + String(" V") + "\"";
        sendDataToDisplay();
        Serial.println(outData);
        outData = Nextion_Text_Field_f2 + String(f2_control_voltage, 1) + String(" V") + "\"";
        sendDataToDisplay();
        outData = "bt0.val=" + String(f1_on_off_state);
        sendDataToDisplay();
        outData = "bt1.val=" + String(f2_on_off_state);
        sendDataToDisplay();
    }
}

void Display::set_visibility_on_Nextion(String Element_name, String Visibility_toggle)
{
    outData = "vis " + Element_name + "," + Visibility_toggle;
    display_control.sendDataToDisplay();
}
void Display::go_to_page_Nextion(int Page_number)
{
    outData = "page " + String(Page_number);
    sendDataToDisplay();
}
void Display::menu_navigation_Nextion()
{
    if (inData == "f_m")
    {
        // go_to_page_Nextion(6);
    }
    if (inData == "t_m")
    {
        go_to_page_Nextion(4);
    }
    if (inData == "t_m_1")
    {
        go_to_page_Nextion(5);
    }
    if (inData == "h_m")
    {
        if (h_manual_control_state_new == true)
        {
            go_to_page_Nextion(3);
            set_properties_page_manual_control();
        }
        else if (h_manual_control_state_new == false)
        {
            go_to_page_Nextion(2);
            set_properties_page_temperature_control();
        }
        Serial.println(outData);
    }
    if (inData == "h_man_on") //navigates to warning page
    {
        display_control.go_to_page_Nextion(8);
    }
    if (inData == "ok_h_man") //turns the manual control ON
    {
        go_to_page_Nextion(3);
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
        go_to_page_Nextion(2);
        set_properties_page_temperature_control();
    }
    if (inData == "s_m")
    {
        go_to_page_Nextion(7);
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
        display_control.sendDataToDisplay();
    }
    if (inData == "display")
    {

    }
}

void Display::refresh_heaters_screen()
{
    h_manual_control_state_new = false;
    set_properties_page_temperature_control();
}

Display display_control;
