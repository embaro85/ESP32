#include "definitions.h"
#define temp_bus 19 // DS18B20 pin
#define Pressure1 35
#define Pressure2 34
#define FP1 27 // free programable 1 or Damper 4 exhaust air
#define FP2 15 // free programable 2 or Damper 3 ambient air
#define FP3 13 // free programable 3 or Damper 2 extract air
#define FP4 2  // free programable 4 or Damper 1 supply air
#define F1 26  // fan 1 0N/OFF
#define F2 14  // fan 2 ON/OFF
#define H1 32  // heater section 1
#define H2 18  // heater section 2
#define H3 25  // heater section 3
//FAN 1 extract air - exhaust air line
#define fan_1_PWM_pin 4
const int fan_1_PWM_Channel = 0;
const int fan_1_PWM_resolution = 8;
const int fan_1_PWM_frequency = 5000;
float f1_control_voltage;
float fan_1_Vd;
float fan_1_Dc;

//FAN 2 ambient air - supply air line
#define fan_2_PWM_pin 33
const int fan_2_PWM_Channel = 1;
const int fan_2_PWM_resolution = 8;
const int fan_2_PWM_frequency = 5000;
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

/////Temperatures/////
int devCount;
float T_1 = 0.00; // supply air
float T_2 = 0.00; // exctract air
float T_3 = 0.00; // ambient air
float T_4 = 0.00; // exhaust air
//float T_5 = 0.00; // valve temperature uncomment if valve temperature measuring is available
//float T_6 = 0.00; //uncomment if other temperature sensors are connected

unsigned int DS18B20_PRECISION = 10;
//int temperature_sensor = 1;

////////TIMERS/////////////////
unsigned long timer1 = 10; //used for temperature measurement
unsigned long timer2 = 10; //used for overview page
unsigned long timer3 = 10;
unsigned long timer4 = 10;
unsigned long timer5 = 10;   //used for heaters settings in Heater_Settings.cpp - heater 1
unsigned long timer6 = 10;   //used for heaters settings in Heater_Settings.cpp - heater 2
unsigned long timer7 = 10;   //used for heaters settings in Heater_Settings.cpp - heater 3
unsigned long timer8 = 1000; // used for the alarm indicator in void too_low_ambient_temperature_alarm()
unsigned long timer9 = 10;   //used in page 21 alarms list
unsigned long timer10 = 10;  //used in screen lock time
unsigned long timer11 = 10;  //used in screen idle time
unsigned long timer12 = 10;  //used in fan 1  delayed start
unsigned long timer13 = 10;  //used in fan 2  delayed start
unsigned long timer14 = 10;  //used for refreshing the states and values of the screen saver page
//unsigned long timer15 = 10;  //free to use
unsigned long timer16 = 10; //used to count time from the start of the machine in Dampers.cpp and Logic.cpp
//unsigned long timer17 = 10;  //free to use

/////DISPLAY/////
int display_brightness;
String new_display_settings;
String old_display_settings;
String saved_values_display_settings;
String screen_lock_pin_first_attemt;
String screen_lock_pin_confirm;
String screen_lock_pin;
String screen_lock_pin_string;
const String master_pin = "9307";
uint8_t number_of_tries = 3;
uint8_t number_of_tries_master_pin = 3;
String master_pin_input;
int on_page_number;
uint8_t Start_page_1 = 1;
uint8_t Heaters1_2 = 2;
uint8_t Heaters2_3 = 3;
uint8_t Temperatures_4 = 4;
uint8_t Temperatures2_5 = 5;
uint8_t Fans_6 = 6;
uint8_t Settings_7 = 7;
uint8_t HeatersWarning_8 = 8;
uint8_t d_settings_9 = 9;
uint8_t t_settings_10 = 10;
uint8_t enter_pin_11 = 11;
uint8_t disable_pin_12 = 12;
uint8_t master_pin_13 = 13;
uint8_t h_settings_14 = 14;
uint8_t overview_1_15 = 15;
uint8_t Temperatures1_16 = 16;
uint8_t damp_settings_17 = 17;
uint8_t h1_settings_18 = 18;
uint8_t h2_settings_19 = 19;
uint8_t h3_settings_20 = 20;
uint8_t alarm_list_21 = 21;
uint8_t lock_screen_22 = 22;
uint8_t unlock_screen_23 = 23;
uint8_t Screen_saver_24 = 24;
bool main_screen_loaded = false;


/////TEMPERATURES/////
int temp_measure_interval = 10;
uint8_t threshold_temperature_heating; //used when the heaters are installed at the ambient air duct as antifreeze protection
uint8_t threshold_temperature_antifreeze;
String temperature_settings;
String supply_air_temperature_sensor_address[] =
    {"xxxxxxxxx", "xxxxxxxxx", "xxxxxxxxx", "4066411481518339"};
String extract_air_temperature_sensor_address[] =
    {"xxxxxxxxx", "xxxxxxxxx", "xxxxxxxxx", "402164214815118328"};
String ambient_air_temperature_sensor_address[] =
    {"xxxxxxxxx", "xxxxxxxxx", "xxxxxxxxx", "40263514815123242"};
String exhaust_air_temperature_sensor_address[] =
    {"xxxxxxxxx", "xxxxxxxxx", "xxxxxxxxx", "4090591481518334"};
String device_0_address;
String device_1_address;
String device_2_address;
String device_3_address;
uint8_t extract_air_temperature_device_index;
uint8_t supply_air_temperature_device_index;
uint8_t ambient_air_temperature_device_index;
uint8_t exhaust_air_temperature_device_index;

/////HEATERS/////
bool heater1_on_off_state;
bool heater2_on_off_state;
bool heater3_on_off_state;
bool manual_control_button_state;
//bool heaters_on;
//bool heaters_last_state;

//page_1_Main_screen//
String p1_b0 = "h_m";
String p1_b1 = "f_m";
String p1_b2 = "t_m";
String p1_b3 = "s_m";
String p1_bt0_command_on_2 = "2";
String p1_bt0_command_off_1 = "1";
String p1_bt0_value = "bt0.val=";
String p1_b5_command_5 = "5";
String p1_b5_visibility = "b5";
bool too_low_ambient_temperature;
bool clogged_filter_1;
bool clogged_filter_2;
uint8_t filter_1_raw_value;
uint8_t filter_2_raw_value;
bool alarm_button_visible;
bool alarm_button_last_state;
bool alarm_button_new_state;
//bool on_page_1 = true;
//String p1_b0_touch = "b0";
String p1_b1_touch = "b1";
String p1_b2_touch = "b2";
String p1_b3_touch = "b3";
String p1_b4_touch = "b4";
String p1_t1_touch = "t1";
String p1_b5_touch = "b5";
String p1_t0_touch = "t0";
int going_to; //used if lock screen is on, to access the menus
bool permission_for_the_unit_start_granted;

//page_2_Heaters_1//
String p2_t5 = "t5.txt=\"";
String p2_t6 = "t6.txt=\"";
String p2_t7 = "t7.txt=\"";
String p2_c0_value = "c0.val=";
String p2_c0_on = "202";
String p2_c0_off = "203";
//bool on_page_2;
String p2_b0_command = "201";

//page3_Heaters_manual_control//
String p3_b1_on = "301";
String p3_b1_off = "302";
String p3_b1_value = "b1.val=";
String p3_b1_text = "b1.txt=\"";
String p3_b2_on = "303";
String p3_b2_off = "304";
String p3_b2_value = "b2.val=";
String p3_b2_text = "b2.txt=\"";
String p3_b3_on = "305";
String p3_b3_off = "306";
String p3_b3_value = "b3.val=";
String p3_b3_text = "b3.txt=\"";
String p3_c0_on = "308";
String p3_c0_off = "307";
String p3_c0_value = "c0.val=";
//bool on_page_3;
bool heaters_manual_control_enabled;
String p3_b0_command = "309";
String save_settings_p3;
String load_settings_p3;

//page_4_temperatures//
String p4_tt1 = "tt1.txt=\"";
String p4_tt2 = "tt2.txt=\"";
String p4_tt3 = "tt3.txt=\"";
String p4_tt4 = "tt4.txt=\"";
String p4_b2_command = "401";
//bool on_page_4;

//page_6_fans//
String p6_tf1_text = "tf1.txt=\"";
String p6_tf2_text = "tf2.txt=\"";
String p6_b4_610 = "610";
String p6_b5_601 = "601";
String p6_b6_602 = "602";
String p6_b7_603 = "603";
String p6_b8_604 = "604";
String p6_bt0_on_607 = "607";
String p6_bt0_off_606 = "606";
String p6_bt1_on_609 = "609";
String p6_bt1_off_608 = "608";
String p6_bt1_value = "bt1.val=";
String p6_bt0_value = "bt0.val=";
bool f1_on_off_state;
bool f2_on_off_state;
String save_fans_settings;
bool fans_initial_start = true; //used as a run once variable
bool f1_initial_start = false;
bool f2_initial_start = false;
bool fans_have_permission_from_dampers = false;
//bool f1_permission_for_heaters_start_granted = false;
bool f2_permission_for_heaters_start_granted = false;
//bool on_page_6;
bool fans_screen_loaded = false;

//page_7_Settings//
String p7_b5_command = "705";
String p7_b6_command = "706";
String p7_b2_command = "set_temperatures";// go_to_page_set_temperatures_p10 = "set_temperatures";
String p7_b3_command = "set_heaters"; //go_to_heaters_settings_page_p14 = "set_heaters";
String p7_b4_command = "704"; //go back button
String p7_b0_command = "display"; //go to display settings button

//page_8_Warning_page//
String p8_b0_command = "801";
String p8_b1_command = "802";

//page_9_Display_settings//
String p9_b0_command_901 = "901";
String p9_b1_command_902 = "902";
String p9_b2_command_903 = "903";
String p9_b3_command_904 = "904";
String p9_b4_command_905 = "905";
String p9_c0_value = "c0.val=";
String p9_c0_on_910 = "910";
String p9_c0_off_911 = "911";
String p9_c1_value = "c1.val=";
String p9_c1_on_906 = "906";
String p9_c1_off_907 = "907";
String p9_c2_on = "909"; // there is no off command for this button
String p9_t4_text = "t4.txt=\"";
String p9_t5_text = "t5.txt=\"";
bool display_auto_off;
int display_auto_off_period;
bool screen_lock_on;
bool temporary_unlock;
bool idle;
const int screen_lock_interval_fixed = 10000; //the period until screen is locked
int screen_lock_interval;

//page_10_temperatures_settings//
String p10_b5_command_101 = "101"; //increase the threshold temperature for turning the heaters off
String p10_b6_command = "102";     // decrease the threshold temperature for turning the heaters off
String p10_b1_command = "103";     // increase the threshold temperature for the antifreeze protection
String p10_b0_command = "104";     // decrease the threshold temperature for the antifreeze protection
String p10_b5 = "b5";
String p10_b6 = "b6";
String p10_b1 = "b1";
String p10_b0 = "b0";
String p10_c0 = "c0";
String p10_c1 = "c1";
String p10_c0_value = "c0.val=";
String p10_c1_value = "c1.val=";
String p10_t4_command = "105"; // display the additional information
String p10_t5_t6_command = "106";
String p10_t7_command = "107"; // display the additional information
String p10_b2_command = "108";
String p10_b3_command = "109";
String summer_mode_p10_bt0 = "110";
String winter_mode_p10_bt1 = "111";
String p10_bt0_value = "bt0.val=";
String p10_bt1_value = "bt1.val=";
String p10_t1 = "t1.txt=\"";
String p10_t3 = "t3.txt=\"";
bool winter_mode;
bool heating_enabled;
bool antifreeze_ebanbled;
String p10_c0_enabled_112 = "112";
String p10_c0_disabled_113 = "113";
String p10_c1_enabled_114 = "114";
String p10_c1_disabled_115 = "115";

//page_12_disable_lock_pin//
//bool on_page_12;
String p12_b3_command = "1201";

//page_13_pin_input_page//
String p13_n0;
String p13_b3_command = "1301";

//page_14_heaters_settings//
String p14_c0_value = "c0.val=";
String p14_c1_value = "c1.val=";
String p14_c2_value = "c2.val=";
String p14_b5_command = "1401";
String p14_b1_command = "1402";
String p14_b0_command = "1403";
String p14_b7_command = "1404";
String p14_b4_command = "1405";
String p14_c0_on_1406 = "1406";
String p14_c0_off_1407 = "1407";
String p14_c1_on_1408 = "1408";
String p14_c1_off_1409 = "1409";
String p14_c2_on_1410 = "1410";
String p14_c2_off_1411 = "1411";
bool h1_enabled;
bool h2_enabled;
bool h3_enabled;
String heaters_settings;
//bool on_page_14;
bool H3_antifreeze_enabled;
//bool heaters_on_conditions_met;

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
//bool on_page_15;
String p15_b4 = "1501";
float heat_exchanger_efficiency;

//page_17_dampers//
String p17_b0_command = "1702";
String p17_b1_command = "1703";
String p17_b2_command = "1704";
String p17_b3_command = "1705";
String p17_b4_command = "1706";
String p17_b5_command = "1707";
String p17_b6_command = "1708";
String p17_b7_command = "1709";
String p17_b8_command = "1701";
String p17_c0_command_on = "1710";
String p17_c0_command_off = "1711";
String p17_c1_command_on = "1712";
String p17_c1_command_off = "1713";
String p17_c2_command_on = "1714";
String p17_c2_command_off = "1715";
String p17_c3_command_on = "1716";
String p17_c3_command_off = "1717";
String p17_t12_command = "1718";
String p17_t13_vis = "t13";
String p17_t13_command = "1719";
String p17_t5 = "t5.txt=\"";
String p17_t7 = "t7.txt=\"";
String p17_t9 = "t9.txt=\"";
String p17_t11 = "t11.txt=\"";
String p17_c0 = "c0.val=";
String p17_c1 = "c1.val=";
String p17_c2 = "c2.val=";
String p17_c3 = "c3.val=";
bool d1_enabled;
bool d2_enabled;
bool d3_enabled;
bool d4_enabled;
int d1_time_delay;
int d2_time_delay;
int d3_time_delay;
int d4_time_delay;
String damper_settings;
//bool on_page_17;
String p17_b0_vis = "b0";
String p17_b1_vis = "b1";
String p17_c0_vis = "c0";
String p17_b2_vis = "b2";
String p17_b3_vis = "b3";
String p17_c1_vis = "c1";
int max_delay;
int min_delay;
bool damper_1_on;
bool damper_2_on;
bool damper_3_on;
bool damper_4_on;
bool d1_initial_start = true;
bool d2_initial_start = true;
bool d3_initial_start = true;
bool d4_initial_start = true;
bool d1_run_once = true;   //used as a run once variable
bool d2_run_once = true;   //used as a run once variable
bool d3_run_once = true;   //used as a run once variable
bool d4_run_once = true;   //used as a run once variable
bool d1_run_once_2 = true; //used as a run once variable
bool d2_run_once_2 = true; //used as a run once variable
bool d3_run_once_2 = true; //used as a run once variable
bool d4_run_once_2 = true; //used as a run once variable
int d1_initial_start_time_delay;
int d2_initial_start_time_delay;
int d3_initial_start_time_delay;
int d4_initial_start_time_delay;
bool d1_permission_fans_can_start = false;
bool d2_permission_fans_can_start = false;
bool d3_permission_fans_can_start = false;
bool d4_permission_fans_can_start = false;
bool dampers_have_permission_from_fans = false;

//page_18_Heater_1_settings//
String p18_b5_command = "1801";
String p18_b6_command = "1802";
String p18_b1_command = "1803";
String p18_b0_command = "1804";
String p18_b7_command = "1805";
String p18_b3_command = "1806";
String p18_b4_command = "1807";
String p18_t3 = "t3.txt=\"";
String p18_t4 = "t4.txt=\"";
String p18_t5 = "t5.txt=\"";
int h1_time_period;
String heater1_settings;
uint8_t temperature_setpoint_1; //used when heaters are installed at the supply air duct as heating.
uint8_t temperature_setpoint_2;
uint8_t temperature_setpoint_3;

//page_19_Heater_2_settings//
String p19_b5_command_1901 = "1901";
String p19_b6_command = "1902";
String p19_b1_command = "1903";
String p19_b0_command = "1904";
String p19_b7_command = "1905";
String p19_b3_command = "1906";
String p19_b4_command = "1907";
String p19_t3 = "t3.txt=\"";
String p19_t4 = "t4.txt=\"";
String p19_t5 = "t5.txt=\"";
int h2_time_period;
String heater2_settings;

//page_20_Heater_3_settings//
String p20_b5_command = "2001";
String p20_b6_command = "2002";
String p20_b1_command = "2003";
String p20_b0_command = "2004";
String p20_b7_command = "2005";
String p20_b3_command = "2006";
String p20_b4_command = "2007";
String p20_t3 = "t3.txt=\"";
String p20_t4 = "t4.txt=\"";
String p20_t5 = "t5.txt=\"";
int h3_time_period;
String heater3_settings;

//page_21_Alarm_list//
//bool on_page_21;
String p21_b4_command_2101 = "2101";
String p21_t1 = "t1.txt=\"";
String p21_t2 = "t2.txt=\"";
String alarm_message;

//page_22_lock_screen//
//String p22_b4_command = "2201";
//String p22_t0_text = "t0.txt=\"";
//String p22_t3_text = "t3.txt=\"";
//bool on_page_22;
//uint16_t screen_flicker;

//page_23_unlock_screen_with_pin//
//bool on_page_23;
String p23_b3_command = "2301";

//page_24_ScreenSaver//
//bool on_page_24 = false;
String p24_t0_text = "t0.txt=\"";
String p24_t1_text = "t1.txt=\"";
String p24_t2_text = "t2.txt=\"";
String p24_t3_text = "t3.txt=\"";
String p24_t4_text = "t4.txt=\"";
String p24_t5_text = "t5.txt=\"";
String p24_t9_text = "t9.txt=\"";
String p24_t10_text = "t10.txt=\"";
String p24_t9_vis = "t9";
String p24_t10_vis = "t10";

String p24_p3_vis = "p3";
String p24_p4_vis = "p4";
String p24_p5_vis = "p5";
String p24_p6_vis = "p6";
String p24_p36_vis = "p36";
String p24_p35_vis = "p35";
String p24_p34_vis = "p34";
String p24_p7_vis = "p7";
String p24_p8_vis = "p8";
String p24_p9_vis = "p9";
String p24_p10_vis = "p10";
String p24_p11_vis = "p11";
String p24_p12_vis = "p12";
String p24_p13_vis = "p13";
String p24_p14_vis = "p14";
String p24_p15_vis = "p15";
String p24_p16_vis = "p16";
String p24_p17_vis = "p17";
String p24_p40_vis = "p40";
String p24_p39_vis = "p39";
String p24_p38_vis = "p38";
String p24_p30_vis = "p30";
String p24_p22_vis = "p22";
String p24_p23_vis = "p23";
String p24_p24_vis = "p24";
String p24_p25_vis = "p25";
String p24_p26_vis = "p26";
String p24_p27_vis = "p27";
String p24_p31_vis = "p31";
String p24_p32_vis = "p32";
String p24_p33_vis = "p33";
String p24_p37_vis = "p37";
String p24_p41_vis = "p41";

bool f1_already_on = false;
bool f2_already_on = false;
bool d1_already_on = false;
bool d1_not_available = false;
bool d2_already_on = false;
bool d2_not_available = false;
bool d3_already_on = false;
bool d3_not_available = false;
bool d4_already_on = false;
bool d4_not_available = false;
bool h1_already_on;
bool h1_not_available = false;
bool h2_already_on;
bool h2_not_available = false;
bool h3_already_on;
bool h3_not_available = false;
bool screen_loaded = false;
String p24_screen_touch = "2401";
String p24_alarm_touch = "2402";




