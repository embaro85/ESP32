#include <Arduino.h>
#include "Screen_saver.h"
#include "definitions.h"
#include "Nextion_commands.h"
#include "Heaters.h"
#include "Heater_settings.h"
#include "Temperatures.h"

void Screen_saver::working_stream()
{
    show_hide_indicators();
    refresh_screen();
    load_screen();
    commands_from_display();
}

void Screen_saver::show_hide_indicators()
{
    if (on_page_number == Screen_saver_24)
    {
        if (fans_have_permission_from_dampers == true && f1_already_on == false) //show the ON indicator for fan 1
        {
            nextion_commands.set_visibility_on_Nextion(p24_p15_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p10_vis, 1);
            f1_already_on = true;
            //Serial.println("Fan 1 on indicator displayed");
        }
        if (fans_have_permission_from_dampers == false && f1_already_on == true) //show the OFF indicator for fan 1
        {
            nextion_commands.set_visibility_on_Nextion(p24_p10_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p15_vis, 1);
            f1_already_on = false;
            //Serial.println("Fan 1 off indicator displayed"); //for debugging
        }
        if (fans_have_permission_from_dampers == true && f2_already_on == false) //show the ON indicator for fan 2
        {
            nextion_commands.set_visibility_on_Nextion(p24_p14_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p9_vis, 1);
            f2_already_on = true;
            //Serial.println("Fan 2 on indicator displayed"); //for debugging
        }
        if (fans_have_permission_from_dampers == false && f2_already_on == true) //show the OFF indicator for fan 2
        {
            nextion_commands.set_visibility_on_Nextion(p24_p9_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p14_vis, 1);
            f2_already_on = false;
            //Serial.println("Fan 2 off indicator displayed");
        }
        if (d1_enabled == false && d1_not_available == false) // show the NOT AVAILABLE indicator for Damper 1
        {
            nextion_commands.set_visibility_on_Nextion(p24_p3_vis, 0);  //on indicator
            nextion_commands.set_visibility_on_Nextion(p24_p13_vis, 0); //off indicator
            nextion_commands.set_visibility_on_Nextion(p24_p22_vis, 1); //not available indicator
            d1_not_available = true;                                    //used as a run once variable. Do not change without a good reason
        }
        if (damper_1_on == true && d1_already_on == false) // show the ON indicator for Damper 1
        {
            nextion_commands.set_visibility_on_Nextion(p24_p22_vis, 0); //not available
            nextion_commands.set_visibility_on_Nextion(p24_p13_vis, 0); //off
            nextion_commands.set_visibility_on_Nextion(p24_p3_vis, 1);  //on
            d1_already_on = true;
        }
        if (damper_1_on == false && d1_already_on == true && d1_enabled == true) // show the OFF indicator for Damper 1
        {
            nextion_commands.set_visibility_on_Nextion(p24_p3_vis, 0);  //not available
            nextion_commands.set_visibility_on_Nextion(p24_p22_vis, 0); //on
            nextion_commands.set_visibility_on_Nextion(p24_p13_vis, 1); //off
            d1_already_on = false;
        }
        if (d2_enabled == false && d2_not_available == false) // show the NOT AVAILABLE indicator for Damper 2
        {
            nextion_commands.set_visibility_on_Nextion(p24_p11_vis, 0); //on
            nextion_commands.set_visibility_on_Nextion(p24_p12_vis, 0); //off
            nextion_commands.set_visibility_on_Nextion(p24_p24_vis, 1); //not available
            d2_not_available = true;
        }
        if (damper_2_on && d2_already_on == false) // show the ON indicator for Damper 2
        {
            nextion_commands.set_visibility_on_Nextion(p24_p24_vis, 0); //not available
            nextion_commands.set_visibility_on_Nextion(p24_p12_vis, 0); //off
            nextion_commands.set_visibility_on_Nextion(p24_p11_vis, 1); //on
            d2_already_on = true;
        }
        if (damper_2_on == false && d2_already_on == true && d2_enabled == true) // show the OFF indicator for Damper 2
        {
            nextion_commands.set_visibility_on_Nextion(p24_p11_vis, 0); //on
            nextion_commands.set_visibility_on_Nextion(p24_p24_vis, 0); //not available
            nextion_commands.set_visibility_on_Nextion(p24_p12_vis, 1); //off
            d2_already_on = false;
        }
        if (d3_enabled == false && d3_not_available == false) // show the NOT AVAILABLE indicator for Damper 3
        {
            nextion_commands.set_visibility_on_Nextion(p24_p7_vis, 0);  //on
            nextion_commands.set_visibility_on_Nextion(p24_p17_vis, 0); //off
            nextion_commands.set_visibility_on_Nextion(p24_p27_vis, 1); //not available
            d3_not_available = true;
        }
        if (damper_3_on == true && d3_already_on == false) // show the ON indicator for Damper 3
        {
            nextion_commands.set_visibility_on_Nextion(p24_p27_vis, 0); // not available
            nextion_commands.set_visibility_on_Nextion(p24_p17_vis, 0); //off
            nextion_commands.set_visibility_on_Nextion(p24_p7_vis, 1);  //on
            d3_already_on = true;
        }
        if (damper_3_on == false && d3_already_on == true && d3_enabled == true) // show the OFF indicator for Damper 3
        {
            nextion_commands.set_visibility_on_Nextion(p24_p7_vis, 0);  //on
            nextion_commands.set_visibility_on_Nextion(p24_p27_vis, 0); // not available
            nextion_commands.set_visibility_on_Nextion(p24_p17_vis, 1); //off
            d3_already_on = false;
        }
        if (d4_enabled == false && d4_not_available == false) // show the NOT AVAILABLE indicator for Damper 3
        {
            nextion_commands.set_visibility_on_Nextion(p24_p8_vis, 0);  //on
            nextion_commands.set_visibility_on_Nextion(p24_p16_vis, 0); //off
            nextion_commands.set_visibility_on_Nextion(p24_p26_vis, 1); //not available
            d4_not_available = true;
        }
        if (damper_4_on == true && d4_already_on == false) // show the ON indicator for Damper 4
        {
            nextion_commands.set_visibility_on_Nextion(p24_p26_vis, 0); //not available
            nextion_commands.set_visibility_on_Nextion(p24_p16_vis, 0); // off
            nextion_commands.set_visibility_on_Nextion(p24_p8_vis, 1);  // on
            d4_already_on = true;
        }
        if (damper_4_on == false && d4_already_on == true && d4_enabled == true) // show the OFF indicator for Damper 4
        {
            nextion_commands.set_visibility_on_Nextion(p24_p26_vis, 0); //not available
            nextion_commands.set_visibility_on_Nextion(p24_p8_vis, 0);  //on
            nextion_commands.set_visibility_on_Nextion(p24_p16_vis, 1); //off
            d4_already_on = false;
        }
        if (h1_enabled == true && h1_not_available == false) //show the not available indicator for Heater 1
        {
            nextion_commands.set_visibility_on_Nextion(p24_p34_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p38_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p32_vis, 1);
            h1_not_available = true;
        }
        if (heater1_on_off_state == true && h1_already_on == false) //show the ON indicator for Heater 1
        {
            nextion_commands.set_visibility_on_Nextion(p24_p32_vis, 0); //not available
            nextion_commands.set_visibility_on_Nextion(p24_p38_vis, 0); //off
            nextion_commands.set_visibility_on_Nextion(p24_p34_vis, 1); //on
            h1_already_on = true;
        }
        if (heater1_on_off_state == false && h1_already_on == true) //show the OFF indicator for Heater 1
        {
            nextion_commands.set_visibility_on_Nextion(p24_p32_vis, 0); //not available
            nextion_commands.set_visibility_on_Nextion(p24_p38_vis, 1); //off
            nextion_commands.set_visibility_on_Nextion(p24_p34_vis, 0); //on
            h1_already_on = false;
        }
        if (h2_enabled == true && h2_not_available == false) //show the not available indicator for Heater 2
        {
            nextion_commands.set_visibility_on_Nextion(p24_p35_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p39_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p31_vis, 1);
            h2_not_available = true;
        }
        if (heater2_on_off_state == true && h2_already_on == false) //show the ON indicator for Heater 2
        {
            nextion_commands.set_visibility_on_Nextion(p24_p31_vis, 0); //not available
            nextion_commands.set_visibility_on_Nextion(p24_p39_vis, 0); //off
            nextion_commands.set_visibility_on_Nextion(p24_p35_vis, 1); //on
            h2_already_on = true;
        }
        if (heater2_on_off_state == false && h2_already_on == true) //show the OFF indicator for Heater 2
        {
            nextion_commands.set_visibility_on_Nextion(p24_p31_vis, 0); //not available
            nextion_commands.set_visibility_on_Nextion(p24_p39_vis, 1); //off
            nextion_commands.set_visibility_on_Nextion(p24_p35_vis, 0); //on
            h2_already_on = false;
        }
        if (h3_enabled == true && h3_not_available == false && antifreeze_ebanbled == false) //show the not available indicator for Heater 3 if antifreeze ISN'T selected
        {
            nextion_commands.set_visibility_on_Nextion(p24_p36_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p40_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p30_vis, 1); //not available
            h3_not_available = true;
            /* if antifreeze is not selected those are the pictures to hide from the screen*/
            nextion_commands.set_visibility_on_Nextion(p24_p30_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p40_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p36_vis, 0);
        }
        if (heater3_on_off_state == true && h3_already_on == false && antifreeze_ebanbled == false) //show the ON indicator for Heater 3 if antifreeze ISN'T selected
        {
            nextion_commands.set_visibility_on_Nextion(p24_p30_vis, 0); //not available
            nextion_commands.set_visibility_on_Nextion(p24_p40_vis, 0); //off
            nextion_commands.set_visibility_on_Nextion(p24_p36_vis, 1); //on
            h3_already_on = true;
            /* if antifreeze is not selected those are the pictures to hide from the screen*/
            nextion_commands.set_visibility_on_Nextion(p24_p30_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p40_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p36_vis, 0);
        }
        if (heater3_on_off_state == false && h3_already_on == true && antifreeze_ebanbled == false) //show the OFF indicator for Heater 3 if antifreeze ISN'T selected
        {
            nextion_commands.set_visibility_on_Nextion(p24_p30_vis, 0); //not available
            nextion_commands.set_visibility_on_Nextion(p24_p40_vis, 1); //off
            nextion_commands.set_visibility_on_Nextion(p24_p36_vis, 0); //on
            h3_already_on = false;
            /* if antifreeze is not selected those are the pictures to hide from the screen*/
            nextion_commands.set_visibility_on_Nextion(p24_p30_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p40_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p36_vis, 0);
        }
        if (h3_enabled == true && h3_not_available == false && antifreeze_ebanbled == true) //show the NOT AVAILABLE indicator for Heater 3 if antifreeze IS selected
        {
            nextion_commands.set_visibility_on_Nextion(p24_p37_vis, 0); //on
            nextion_commands.set_visibility_on_Nextion(p24_p41_vis, 0); //off
            nextion_commands.set_visibility_on_Nextion(p24_p33_vis, 1); //not available
            h3_not_available = true;
            /* if antifreeze is selected those are the pictures to hide from the screen*/
            nextion_commands.set_visibility_on_Nextion(p24_p36_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p40_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p30_vis, 0);
        }
        if (heater3_on_off_state == true && h3_already_on == false && antifreeze_ebanbled == true) //show the ON indicator for Heater 3 if antifreeze IS selected
        {
            nextion_commands.set_visibility_on_Nextion(p24_p37_vis, 1); //on
            nextion_commands.set_visibility_on_Nextion(p24_p41_vis, 0); //off
            nextion_commands.set_visibility_on_Nextion(p24_p33_vis, 0); //not available
            h3_already_on = true;
            /* if antifreeze is selected those are the pictures to hide from the screen*/
            nextion_commands.set_visibility_on_Nextion(p24_p36_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p40_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p30_vis, 0);
        }
        if (heater3_on_off_state == false && h3_already_on == true && antifreeze_ebanbled == true) //show the OFF indicator for Heater 3 if antifreeze IS selected
        {
            nextion_commands.set_visibility_on_Nextion(p24_p37_vis, 0); //on
            nextion_commands.set_visibility_on_Nextion(p24_p41_vis, 1); //off
            nextion_commands.set_visibility_on_Nextion(p24_p33_vis, 0); //not available
            h3_already_on = true;
            /* if antifreeze is selected those are the pictures to hide from the screen*/
            nextion_commands.set_visibility_on_Nextion(p24_p36_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p40_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p30_vis, 0);
        }
    }
}

void Screen_saver::refresh_screen()
{
    if (millis() > (timer14 + 5000) && on_page_number == Screen_saver_24)
    {
        nextion_commands.set_text_of_screen_component(p24_t1_text, String(T_1, 1) + String("œC"));
        nextion_commands.set_text_of_screen_component(p24_t2_text, String(T_2, 1) + String("œC"));
        nextion_commands.set_text_of_screen_component(p24_t0_text, String(T_4, 1) + String("œC"));
        nextion_commands.set_text_of_screen_component(p24_t3_text, String(T_3, 1) + String("œC"));
        nextion_commands.set_text_of_screen_component(p24_t4_text, String(f1_control_voltage * 10, 0) + String("%"));
        nextion_commands.set_text_of_screen_component(p24_t5_text, String(f2_control_voltage * 10, 0) + String("%"));
        if (clogged_filter_1 == true)
        {
            nextion_commands.set_visibility_on_Nextion(p24_p4_vis, 1);
        }
        if (clogged_filter_1 == false)
        {
            nextion_commands.set_visibility_on_Nextion(p24_p4_vis, 0);
        }
        if (clogged_filter_2 == true)
        {
            nextion_commands.set_visibility_on_Nextion(p24_p5_vis, 1);
        }
        if (clogged_filter_2 == false)
        {
            nextion_commands.set_visibility_on_Nextion(p24_p5_vis, 0);
        }
        if (clogged_filter_1 == true || clogged_filter_2 == true || T_3 <= 4)
        {
            nextion_commands.set_visibility_on_Nextion(p24_p6_vis, 1);
            nextion_commands.set_visibility_on_Nextion(p24_t9_vis, 1);
            // nextion_commands.set_text_of_screen_component(p24_t9_text, "??????? ??????");
        }
        if (clogged_filter_1 == false && clogged_filter_2 == false && T_3 > 4)
        {
            nextion_commands.set_visibility_on_Nextion(p24_p6_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_t9_vis, 0);
        }
        if (heater1_on_off_state == false && heater2_on_off_state == false && heater3_on_off_state == false)
        {
            nextion_commands.set_visibility_on_Nextion(p24_t10_vis, 1);
            nextion_commands.set_text_of_screen_component(p24_t10_text, String(temperatures_control.calculate_heat_exchanger_efficiency(), 0) + "%");
        }
        if (heater1_on_off_state == true || heater2_on_off_state == true || heater3_on_off_state == true)
        {
            nextion_commands.set_visibility_on_Nextion(p24_t10_vis, 0);
        }
        timer14 = millis();
    }
}
void Screen_saver::load_screen()
{
    if (on_page_number == Screen_saver_24 && screen_loaded == false)
    {
        if (d1_enabled == false)
        {
            nextion_commands.set_visibility_on_Nextion(p24_p3_vis, 0);  //on indicator
            nextion_commands.set_visibility_on_Nextion(p24_p13_vis, 0); //off indicator
            nextion_commands.set_visibility_on_Nextion(p24_p22_vis, 1); //not available indicator
        }
        if (damper_1_on == true)
        {
            nextion_commands.set_visibility_on_Nextion(p24_p13_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p22_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p3_vis, 1);
        }
        if (damper_1_on == false && d1_enabled == true)
        {
            nextion_commands.set_visibility_on_Nextion(p24_p3_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p22_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p13_vis, 1);
        }
        if (d2_enabled == false)
        {
            nextion_commands.set_visibility_on_Nextion(p24_p11_vis, 0); //on
            nextion_commands.set_visibility_on_Nextion(p24_p12_vis, 0); //off
            nextion_commands.set_visibility_on_Nextion(p24_p24_vis, 1); // not available
        }
        if (damper_2_on == true) // show the ON indicator for Damper 2
        {
            nextion_commands.set_visibility_on_Nextion(p24_p24_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p12_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p11_vis, 1);
        }
        if (damper_2_on == false && d2_enabled == true) // show the OFF indicator for Damper 2
        {
            nextion_commands.set_visibility_on_Nextion(p24_p11_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p24_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p12_vis, 1);
        }
        if (d3_enabled == false) // show the NOT AVAILABLE indicator for Damper 3
        {
            nextion_commands.set_visibility_on_Nextion(p24_p7_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p17_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p27_vis, 1);
        }
        if (damper_3_on == true) // show the ON indicator for Damper 3
        {
            nextion_commands.set_visibility_on_Nextion(p24_p27_vis, 0); // not available
            nextion_commands.set_visibility_on_Nextion(p24_p17_vis, 0); //off
            nextion_commands.set_visibility_on_Nextion(p24_p7_vis, 1);  //on
        }
        if (damper_3_on == false && d3_enabled == true) // show the OFF indicator for Damper 3
        {
            nextion_commands.set_visibility_on_Nextion(p24_p7_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p27_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p17_vis, 1);
        }
        if (d4_enabled == false) // show the NOT AVAILABLE indicator for Damper 4
        {
            nextion_commands.set_visibility_on_Nextion(p24_p8_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p16_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p26_vis, 1);
        }
        if (damper_4_on == true) // show the ON indicator for Damper 4
        {
            nextion_commands.set_visibility_on_Nextion(p24_p26_vis, 0); //not available
            nextion_commands.set_visibility_on_Nextion(p24_p16_vis, 0); // off
            nextion_commands.set_visibility_on_Nextion(p24_p8_vis, 1);  // on
        }
        if (damper_4_on == false && d4_enabled == true) // show the OFF indicator for Damper 4
        {
            nextion_commands.set_visibility_on_Nextion(p24_p26_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p8_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p16_vis, 1);
        }
        if (fans_have_permission_from_dampers == true && f1_on_off_state == true)
        {
            nextion_commands.set_visibility_on_Nextion(p24_p15_vis, 0); // off
            nextion_commands.set_visibility_on_Nextion(p24_p10_vis, 1); // on
        }
        if (fans_have_permission_from_dampers == true && f2_on_off_state == true)
        {
            nextion_commands.set_visibility_on_Nextion(p24_p14_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p9_vis, 1);
        }
        if (fans_have_permission_from_dampers == false)
        {
            nextion_commands.set_visibility_on_Nextion(p24_p10_vis, 0); // on indicator fan 1
            nextion_commands.set_visibility_on_Nextion(p24_p9_vis, 0);  // on indicator fan 2
            nextion_commands.set_visibility_on_Nextion(p24_p15_vis, 1); // off indicator fan 1
            nextion_commands.set_visibility_on_Nextion(p24_p14_vis, 1); // off indicator fan 2
        }
        if (h1_enabled == false) // show the NOT AVAILABLE indicator for Heater 1
        {
            nextion_commands.set_visibility_on_Nextion(p24_p34_vis, 0); //on
            nextion_commands.set_visibility_on_Nextion(p24_p38_vis, 0); //off
            nextion_commands.set_visibility_on_Nextion(p24_p32_vis, 1); // not available
        }
        if (heater1_on_off_state == true) // show the ON indicator for Heater 1
        {
            nextion_commands.set_visibility_on_Nextion(p24_p34_vis, 1); //on
            nextion_commands.set_visibility_on_Nextion(p24_p38_vis, 0); //off
            nextion_commands.set_visibility_on_Nextion(p24_p32_vis, 0); // not available
        }
        if (heater1_on_off_state == false && h1_enabled == true) // show the OFF indicator for Heater 1
        {
            nextion_commands.set_visibility_on_Nextion(p24_p34_vis, 0); //on
            nextion_commands.set_visibility_on_Nextion(p24_p38_vis, 1); //off
            nextion_commands.set_visibility_on_Nextion(p24_p32_vis, 0); // not available
        }
        if (h2_enabled == false) // show the NOT AVAILABLE indicator for Heater 2
        {
            nextion_commands.set_visibility_on_Nextion(p24_p35_vis, 0); //on
            nextion_commands.set_visibility_on_Nextion(p24_p39_vis, 0); //off
            nextion_commands.set_visibility_on_Nextion(p24_p31_vis, 1); //not available
        }
        if (heater2_on_off_state == true) // show the ON indicator for Heater 2
        {
            nextion_commands.set_visibility_on_Nextion(p24_p35_vis, 1);
            nextion_commands.set_visibility_on_Nextion(p24_p39_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p31_vis, 0);
        }
        if (heater2_on_off_state == false && h2_enabled == true) // show the OFF indicator for Heater 2
        {
            nextion_commands.set_visibility_on_Nextion(p24_p35_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p39_vis, 1);
            nextion_commands.set_visibility_on_Nextion(p24_p31_vis, 0);
        }
        if (h3_enabled == false && antifreeze_ebanbled == false) // show the NOT AVAILABLE indicator for Heater 3 if antifreeze isn't selected as an option
        {
            nextion_commands.set_visibility_on_Nextion(p24_p36_vis, 0); //on
            nextion_commands.set_visibility_on_Nextion(p24_p40_vis, 0); //off
            nextion_commands.set_visibility_on_Nextion(p24_p30_vis, 1); //not available
            /* if antifreeze is not selected those are the pictures to hide from the screen*/
            nextion_commands.set_visibility_on_Nextion(p24_p37_vis, 0); //on
            nextion_commands.set_visibility_on_Nextion(p24_p41_vis, 0); //off
            nextion_commands.set_visibility_on_Nextion(p24_p33_vis, 0); //not available
        }
        if (heater3_on_off_state == true) // show the ON indicator for Heater 3 if antifreeze ISN'T selected as an option
        {
            nextion_commands.set_visibility_on_Nextion(p24_p36_vis, 1);
            nextion_commands.set_visibility_on_Nextion(p24_p40_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p30_vis, 0);
            /* if antifreeze is not selected those are the pictures to hide from the screen*/
            nextion_commands.set_visibility_on_Nextion(p24_p37_vis, 0); //on
            nextion_commands.set_visibility_on_Nextion(p24_p41_vis, 0); //off
            nextion_commands.set_visibility_on_Nextion(p24_p33_vis, 0); //not available
        }
        if (heater3_on_off_state == false && h3_enabled == true) // show the OFF indicator for Heater 3 if antifreeze ISN'T selected as an option
        {
            nextion_commands.set_visibility_on_Nextion(p24_p36_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p40_vis, 1);
            nextion_commands.set_visibility_on_Nextion(p24_p30_vis, 0);
            /* if antifreeze is not selected those are the pictures to hide from the screen*/
            nextion_commands.set_visibility_on_Nextion(p24_p37_vis, 0); //on
            nextion_commands.set_visibility_on_Nextion(p24_p41_vis, 0); //off
            nextion_commands.set_visibility_on_Nextion(p24_p33_vis, 0); //not available
        }
        if (h3_enabled == true && antifreeze_ebanbled == true) //show the not available indicator for Heater 3 if antifreeze IS selected
        {
            nextion_commands.set_visibility_on_Nextion(p24_p37_vis, 0); //on
            nextion_commands.set_visibility_on_Nextion(p24_p41_vis, 0); //off
            nextion_commands.set_visibility_on_Nextion(p24_p33_vis, 1); //not available
            /* if antifreeze is selected those are the pictures to hide from the screen*/
            nextion_commands.set_visibility_on_Nextion(p24_p36_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p40_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p30_vis, 0);
        }
        if (heater3_on_off_state == true && antifreeze_ebanbled == true) //show the ON indicator for Heater 3 if antifreeze IS selected
        {
            nextion_commands.set_visibility_on_Nextion(p24_p37_vis, 1); //on
            nextion_commands.set_visibility_on_Nextion(p24_p41_vis, 0); //off
            nextion_commands.set_visibility_on_Nextion(p24_p33_vis, 0); //not available
            /* if antifreeze is selected those are the pictures to hide from the screen*/
            nextion_commands.set_visibility_on_Nextion(p24_p36_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p40_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p30_vis, 0);
        }
        if (heater3_on_off_state == false && antifreeze_ebanbled == true) //show the ON indicator for Heater 3 if antifreeze IS selected
        {
            nextion_commands.set_visibility_on_Nextion(p24_p37_vis, 0); //on
            nextion_commands.set_visibility_on_Nextion(p24_p41_vis, 1); //off
            nextion_commands.set_visibility_on_Nextion(p24_p33_vis, 0); //not available
            /* if antifreeze is selected those are the pictures to hide from the screen*/
            nextion_commands.set_visibility_on_Nextion(p24_p36_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p40_vis, 0);
            nextion_commands.set_visibility_on_Nextion(p24_p30_vis, 0);
        }
        nextion_commands.set_text_of_screen_component(p24_t1_text, String(T_1, 1) + String("œC"));
        nextion_commands.set_text_of_screen_component(p24_t2_text, String(T_2, 1) + String("œC"));
        nextion_commands.set_text_of_screen_component(p24_t0_text, String(T_4, 1) + String("œC"));
        nextion_commands.set_text_of_screen_component(p24_t3_text, String(T_3, 1) + String("œC"));
        nextion_commands.set_text_of_screen_component(p24_t4_text, String(f1_control_voltage * 10, 0) + String("%"));
        nextion_commands.set_text_of_screen_component(p24_t5_text, String(f2_control_voltage * 10, 0) + String("%"));
        screen_loaded = true;
    }
}
void Screen_saver::commands_from_display()
{
    if (inData == p24_screen_touch)
    {
        nextion_commands.go_to_page_Nextion(1);
        nextion_commands.on_page(1);
        screen_loaded = false;
    }
    if (inData == p24_alarm_touch) // navigate to the alarms page
    {
        screen_loaded = false;
        nextion_commands.on_page(21);
        nextion_commands.go_to_page_Nextion(21);
    }
}
Screen_saver screen_saver_control;