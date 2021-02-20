#include "definitions.h"
#define temp_bus 19 // DS18B20 pin
#define Pressure1 35
#define Pressure2 34
#define FP1 27 // free programable 1
#define FP2 15 // free programable 2
#define FP3 13 // free programable 3
#define FP4 2  // free programable 4
#define F1 26  // fan 1 0N/OFF
#define F2 14  // fan 2 ON/OFF
#define H1 32  // heater section 1
#define H2 18  // heater section 2
#define H3 25  // heater section 3
//FAN 1
#define fan_1_PWM_pin 4
const int fan_1_PWM_Channel = 0;
const int fan_1_PWM_resolution = 8;
const int fan_1_PWM_frequency = 5000;
float fan1_0_10_voltage_input; //input from display
int fan1_0_10_voltage_output;
float f1_control_voltage;
float fan_1_Vd;
float fan_1_Dc;

//FAN 2
#define fan_2_PWM_pin 33
const int fan_2_PWM_Channel = 1;
const int fan_2_PWM_resolution = 8;
const int fan_2_PWM_frequency = 5000;
float fan2_0_10_voltage_input;
int fan2_0_10_voltage_output;
float fan_2_Vd;
float fan_2_Dc;
float f2_control_voltage;

//VALVE 1
#define valve_1_PWM_pin 5
const int valve_1_PWM_Channel = 2;
const int valve_1_PWM_resolution = 8;
const int valve_1_PWM_frequency = 5000;
// VARIABLES FOR THE DISPLAY
unsigned long time_in_millis = 0;
unsigned long elapsed_time_in_millis = 0;
unsigned long timer_read_serial = 0;
int read_serial_interval = 15000;
String inData; //main variable for incoming data from the display
//int inData2;
String outData; //main variable for outgoing data to the display
bool f1_on_off_state;
bool f2_on_off_state;
String new_settings_fans;
String old_settings_fans;
String saved_settings_fans;
String f1_on_off_state_string;
String f2_on_off_state_string;
/////Temperatures/////
int devCount;
float T_1 = 0.00;
float T_2 = 0.00;
float T_3 = 0.00;
float T_4 = 0.00;
float T_5 = 0.00;
float T_6 = 0.00;

unsigned int DS18B20_PRECISION = 10;
int temperature_sensor = 1;

////////TIMERS/////////////////
unsigned long timer1 = 1; //used for temperature measurement
unsigned long timer2 = 1; //used for overview page
unsigned long timer3 = 1; //not used
unsigned long timer4 = 1; //not used
unsigned long timer5 = 1; //not used
unsigned long timer6 = 1; //not used
/////DISPLAY/////
String f1_Nextion_Text_Field = "tf1.txt=\"";
String f1_plus_cmd = "f1_pl";
String f1_minus_cmd = "f1_mi";
String f2_Nextion_Text_Field = "tf2.txt=\"";
String f2_plus_cmd = "f2_pl";
String f2_minus_cmd = "f2_mi";
String ref_fans_screen_cmd = "f_m";
String ref_temp1_screen_cmd = "t_m";
String ref_temp2_screen_cmd = "t_m_1";
String t1_Nextion_Text_Field = "tt1.txt=\"";
String t2_Nextion_Text_Field = "tt2.txt=\"";
String t3_Nextion_Text_Field = "tt3.txt=\"";
String t4_Nextion_Text_Field = "tt4.txt=\"";
String on_temp_screen_one;
int display_brightness;
String display_brightness_string;
int auto_off_period;
String auto_off_period_string;
int ten_seconds;
int twenty_seconds;
int sixty_seconds;
int hudredAndTwenty_seconds;
bool calculate_time_for_auto_screen_off;
bool display_auto_on_off_state;
String display_auto_on_off_state_string;
bool display_screen_lock_on_off_state;
String display_screen_lock_on_off_state_string;
String new_display_settings;
String old_display_settings;
String saved_values_display_settings;
String screen_lock_pin_first_attemt;
String screen_lock_pin_confirm;
String screen_lock_pin;
String screen_lock_pin_string;
const String master_pin = "9307";
int display_screen_lock_period;
String display_screen_lock_period_string;
uint16_t number_of_tries = 3;
uint16_t number_of_tries_master_pin = 3;
String master_pin_input;

/////TEMPERATURES/////
int temp_measure_interval = 200;
String h_manual_on_off = "ok_h_man";
bool h_manual_control_state_new;
bool h_manual_control_state_old;
String h1_manual_on = "h1_on";
String h1_manual_off = "h1_off";
String h2_manual_on = "h2_on";
String h2_manual_off = "h2_off";
String h3_manual_on = "h3_on";
String h3_manual_off = "h3_off";
//String h1_Nextion_Text_Field = "th1.txt=\"";
String h2_Nextion_Text_Field = "th2.txt=\"";
String h3_Nextion_Text_Field = "th3.txt=\"";
uint8_t threshold_temperature=2;
uint8_t threshold_temperature_saved;
uint8_t turn_everything_off_temperature_threshold=2;
uint8_t turn_everything_off_temperature_threshold_saved; 
String new_temperature_settings;


//page_2_Heaters_1//
String p2_t5 = "t5.txt=\"";
String p2_t6 = "t6.txt=\"";
String p2_t7 = "t7.txt=\"";
String p2_bhmanual = "bhmanual.val=";
bool on_page_2;
String p2_b0_command = "201";

//page_4_temperatures//
String p4_tt1 = "tt1.txt=\"";
String p4_tt2 = "tt2.txt=\"";
String p4_tt3 = "tt3.txt=\"";
String p4_tt4 = "tt4.txt=\"";
String p4_b2_command = "401";
bool on_page_4;


/////HEATERS/////
bool new_state_h1 = true;
bool heater1_on_off_state = false;
bool heater2_on_off_state;
bool heater3_on_off_state;
bool manual_control_button_state;
String new_heaters_settings;

///Display components variables///
String p9_n0 = "n0.val=";
String p9_h0 = "h0.val=";
String p9_c0 = "c0.val=";
String p9_c1 = "c1.val=";
String p13_n0 = "n0.val=";


//page_7_Settings//
String p7_b5_command = "705";
String p7_b6_command = "706"; 




//page_10_temperatures_settings//
String p10_b5_command = "101";    //increase the threshold temperature for turning the heaters on
String p10_b6_command = "102";   // decrease the threshold temperature for turning the heaters on
String p10_b1_command = "103";  // increase the threshold temperature for turning the unit off
String p10_b0_command = "104"; // decrease the threshold temperature for turning the unit off
String p10_b5 = "b5";
String p10_b6 = "b6";
String p10_b1 = "b1";
String p10_b0 = "b0";
String info_button_push_p10_t4 = "105"; // display the additional information
String turn_off_info_text_p10_t5_and_t6 ="106";
String info_button_push_p10_t7 = "107"; // display the additional information
String p10_b2_command = "108";
String p10_b3_command = "109";
String p10_b2 = "b2";
String p10_b3 = "b3";
String summer_mode_p10_bt0 = "110";
String winter_mode_p10_bt1 = "111";
String p10_bt0 = "bt0.val=";
String p10_bt1 = "bt1.val=";
String p10_t1 = "t1.txt=\"";
String p10_t3 = "t3.txt=\"";
bool summer_mode_activated;
bool winter_mode_activated;

//page_14_heaters_settings//
String p14_t0 = "t0";
String p14_t3;
String p14_t4;
String p14_t5;
String p14_t7_info_button = "9";
String p14_c0 = "c0.val=";
String p14_c1 = "c1.val=";
String p14_c2 = "c2.val=";
String p14_b5 = "10";
String p14_b6 = "11";
String p14_b1 = "13";
String p14_b2 = "12";
String p14_b0 = "14";
String p14_b7 = "15";
String p14_b3 = "16";
String p14_c0_on = "p14_c0_on";
String p14_c0_off = "p14_c0_off";
String p14_c1_on = "p14_c1_on";
String p14_c1_off = "p14_c1_off";
String p14_c2_on = "p14_c2_on";
String p14_c2_off = "p14_c2_off";
bool h1_available;
bool h2_available;
bool h3_available;
float h1_power;
float h2_power;
float h3_power;

//page_15_Overview//
String p15_t9 = "t9.txt=\"";
String p15_t10 = "t10.txt=\"";
String p15_t11 = "t11.txt=\"";
String p15_t12 = "t12.txt=\"";
String p15_t13 = "t13.txt=\"";
String p15_t14 = "t14.txt=\"";
String p15_t15 = "t15.txt=\"";
String p15_t16 = "t16.txt=\"";
String p15_t17 = "t17.txt=\"";
String p15_t19 = "t19.txt=\"";
boolean on_page_15 = false;
String p15_b4 = "1501";



//page_6_fans//
String p6_tf1 = "tf1.txt=\"";
String p6_tf2 = "tf2.txt=\"";
String p6_b4;
String p6_b5 ="f1_pl";
String p6_b6 = "f1_mi";
String p6_b7 = "f2_pl";
String p6_b8 = "f2_mi";
String p6_bt0_on = "f1_on";
String p6_bt0_off = "f1_off";
String p6_bt1_on = "f2_on";
String p6_bt1_off = "f2_off";
String p6_bt1_value = "bt1.val=";
String p6_bt0_value = "bt0.val=";



///Menu Navigation///
String go_to_page_heaters_p2 ="h_m";
String go_to_page_temperatures_p4 ="t_m";
String go_to_page_temperatures_p5 ="t_m_1";
String go_to_page_heaters_warning_p8 = "h_man_on";
String go_to_page_set_temperatures_p10 = "set_temperatures";
String go_to_heaters_settings_page_p14 = "set_heaters";



