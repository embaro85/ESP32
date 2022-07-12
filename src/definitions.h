#pragma once
#include <Arduino.h>
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
extern const int fan_1_PWM_Channel;
extern const int fan_1_PWM_resolution;
extern const int fan_1_PWM_frequency;
extern float fan_1_Vd;
extern float fan_1_Dc;
extern float f1_control_voltage;

//FAN 2
#define fan_2_PWM_pin 33
extern const int fan_2_PWM_Channel;
extern const int fan_2_PWM_resolution;
extern const int fan_2_PWM_frequency;
extern float fan_2_Vd;
extern float fan_2_Dc;
//extern String f2_Nextion_Text_Field;
extern float f2_control_voltage;

//VALVE 1
#define valve_1_PWM_pin 5
extern const int valve_1_PWM_Channel;
extern const int valve_1_PWM_resolution;
extern const int valve_1_PWM_frequency;
// VARIABLES FOR THE DISPLAY
extern unsigned long time_in_millis;
extern unsigned long elapsed_time_in_millis;
extern unsigned long timer_read_serial;
extern int read_serial_interval;
extern String inData; //main variable for incoming data from the display
//extern int inData2;

extern String outData; //main variable for outgoing data to the display

/////Temperatures/////
extern int devCount;
extern float T_1;
extern float T_2;
extern float T_3;
extern float T_4;
extern float T_5;
extern float T_6;
extern unsigned int DS18B20_PRECISION;
extern int temp_measure_interval;
////////TIMERS/////////////////
extern unsigned long timer1; //used for temperature measurement
extern unsigned long timer2;
extern unsigned long timer3;
extern unsigned long timer4;
extern unsigned long timer5;
extern unsigned long timer6;
extern unsigned long timer7;
extern unsigned long timer8;
extern unsigned long timer9;  //used in page 21 alarms list
extern unsigned long timer10; //used in screen lock time
extern unsigned long timer11; //used in screen idle time
extern unsigned long timer12; //used in fan 1  delayed start
extern unsigned long timer13; //used in fan 2  delayed start
extern unsigned long timer14; //used for refreshing the states and values of the screen saver page
//extern unsigned long timer15; //free to use
extern unsigned long timer16; //used to count time from the start of the machine in Dampers.cpp and Logic.cpp
//extern unsigned long timer17; //free to use

/////DISPLAY/////
extern int display_brightness;
extern String new_display_settings;
extern String old_display_settings;
extern String saved_values_display_settings;
extern String screen_lock_pin;
extern String screen_lock_pin_string;
extern String screen_lock_pin_confirm;
extern String screen_lock_pin_first_attemt;
extern const String master_pin;
extern uint8_t number_of_tries;
extern uint8_t number_of_tries_master_pin;
extern String master_pin_input;
extern int on_page_number;
extern uint8_t Start_page_1;
extern uint8_t Heaters1_2;
extern uint8_t Heaters2_3;
extern uint8_t Temperatures_4;
extern uint8_t Temperatures2_5;
extern uint8_t Fans_6;
extern uint8_t Settings_7;
extern uint8_t HeatersWarning_8;
extern uint8_t d_settings_9;
extern uint8_t t_settings_10;
extern uint8_t enter_pin_11;
extern uint8_t disable_pin_12;
extern uint8_t master_pin_13;
extern uint8_t h_settings_14;
extern uint8_t overview_1_15;
extern uint8_t Temperatures1_16;
extern uint8_t damp_settings_17;
extern uint8_t h1_settings_18;
extern uint8_t h2_settings_19;
extern uint8_t h3_settings_20;
extern uint8_t alarm_list_21;
extern uint8_t lock_screen_22;
extern uint8_t unlock_screen_23;
extern uint8_t Screen_saver_24;
extern bool main_screen_loaded;

/////TEMPERATURES/////
extern uint8_t threshold_temperature_heating;
extern uint8_t threshold_temperature_antifreeze;
extern String temperature_settings;
extern uint8_t temperature_setpoint_1;
extern uint8_t temperature_setpoint_2;
extern uint8_t temperature_setpoint_3;
extern String supply_air_temperature_sensor_address[];
extern String extract_air_temperature_sensor_address[];
extern String ambient_air_temperature_sensor_address[];
extern String exhaust_air_temperature_sensor_address[];
extern String device_0_address;
extern String device_1_address;
extern String device_2_address;
extern String device_3_address;
extern uint8_t extract_air_temperature_device_index;
extern uint8_t supply_air_temperature_device_index;
extern uint8_t ambient_air_temperature_device_index;
extern uint8_t exhaust_air_temperature_device_index;

//page_1_Main_screen//
extern String p1_b0;
extern String p1_b1;
extern String p1_b2;
extern String p1_b3;
extern String p1_b5_command_5;
extern String p1_bt0_command_on_2;
extern String p1_bt0_command_off_1;
extern String p1_bt0_value;
extern String p1_b5_visibility;
extern bool too_low_ambient_temperature;
extern bool clogged_filter_1;
extern bool clogged_filter_2;
extern uint8_t filter_1_raw_value;
extern uint8_t filter_2_raw_value;
extern bool alarm_button_visible;
extern bool alarm_button_last_state;
extern bool alarm_button_new_state;
//extern bool on_page_1;
extern String p1_b0_touch;
extern String p1_b1_touch;
extern String p1_b2_touch;
extern String p1_b3_touch;
extern String p1_b4_touch;
extern String p1_t1_touch;
extern String p1_b5_touch;
extern String p1_t0_touch;
extern int going_to; //used if lock screen is on, to access the menus
//extern bool main_START_button;
extern bool permission_for_the_unit_start_granted;

//page_2_Heaters_1//
extern String p2_t5;
extern String p2_t6;
extern String p2_t7;
extern String p2_c0_value;
extern String p2_c0_on;
extern String p2_c0_off;
//extern bool on_page_2;
extern String p2_b0_command;

//page3_Heaters_manual_control//
extern String p3_b1_on;
extern String p3_b1_off;
extern String p3_b1_value;
extern String p3_b1_text;
extern String p3_b2_on;
extern String p3_b2_off;
extern String p3_b2_value;
extern String p3_b2_text;
extern String p3_b3_on;
extern String p3_b3_off;
extern String p3_b3_value;
extern String p3_b3_text;
extern String p3_c0_on;
extern String p3_c0_off;
extern String p3_c0_value;
// extern bool on_page_3;
extern bool heaters_manual_control_enabled;
extern String p3_b0_command;
extern String save_settings_p3;
extern String load_settings_p3;

//page_4_temperatures//
extern String p4_tt1;
extern String p4_tt2;
extern String p4_tt3;
extern String p4_tt4;
extern String p4_b2_command;
// extern bool on_page_4;

/////HEATERS/////
extern bool heater1_on_off_state;
extern bool heater2_on_off_state;
extern bool heater3_on_off_state;
extern bool manual_control_button_state;
//extern bool heaters_on;
//extern bool heaters_last_state;

//page_6_fans//
extern String p6_tf1_text;
extern String p6_tf2_text;
extern String p6_b4;
extern String p6_b5;
extern String p6_b6;
extern String p6_b7;
extern String p6_b8;
extern String p6_bt0_on;
extern String p6_bt0_off;
extern String p6_bt1_on;
extern String p6_bt1_off;
extern String p6_bt1_value;
extern String p6_bt0_value;
extern bool f1_on_off_state;
extern bool f2_on_off_state;
extern String save_fans_settings;
//extern bool f1_permission_for_heaters_start_granted;
extern bool f2_permission_for_heaters_start_granted;

//page_6_fans//
extern String p6_tf1;
extern String p6_tf2;
extern String p6_b4_610;
extern String p6_b5_601;
extern String p6_b6_602;
extern String p6_b7_603;
extern String p6_b8_604;
extern String p6_bt0_on_607;
extern String p6_bt0_off_606;
extern String p6_bt1_on_609;
extern String p6_bt1_off_608;
extern String p6_bt1_value;
extern String p6_bt0_value;
extern bool fans_initial_start; //start the fans after damper opening time
extern bool f1_initial_start;
extern bool f2_initial_start;
extern bool fans_have_permission_from_dampers;
//extern bool on_page_6;
extern bool fans_screen_loaded;

//page_7_Settings//
extern String p7_b5_command;
extern String p7_b6_command;
extern String p7_b2_command; // go_to_page_set_temperatures_p10 = "set_temperatures";
extern String p7_b3_command; //go_to_heaters_settings_page_p14 = "set_heaters";
extern String p7_b4_command; //go back button
extern String p7_b0_command; //go to display settings button

//page_8_Warning_page//
extern String p8_b0_command;
extern String p8_b1_command;

//page_9_Display_settings//
extern String p9_b0_command_901;
extern String p9_b1_command_902;
extern String p9_b2_command_903;
extern String p9_b3_command_904;
extern String p9_b4_command_905;
extern String p9_c0_value;
extern String p9_c0_on_910;
extern String p9_c0_off_911;
extern String p9_c1_value;
extern String p9_c1_on_906;
extern String p9_c1_off_907;
extern String p9_c2_on; // there is no off command for this button
extern String p9_t4_text;
extern String p9_t5_text;
extern bool display_auto_off;
extern int display_auto_off_period;
extern bool screen_lock_on;
extern bool temporary_unlock;
extern bool idle;
extern const int screen_lock_interval_fixed;
extern int screen_lock_interval;

//page_10_temperatures_settings//
extern String p10_b5_command_101; //increase the threshold temperature for turning the heaters on
extern String p10_b6_command;     // decrease the threshold temperature for turning the heaters on
extern String p10_b1_command;     // increase the threshold temperature for turning the unit off
extern String p10_b0_command;     // decrease the threshold temperature for turning the unit off
extern String p10_b5;
extern String p10_b6;
extern String p10_b1;
extern String p10_b0;
extern String p10_c0;
extern String p10_c1;
extern String p10_t4_command; // display the additional information
extern String p10_t5_t6_command;
extern String p10_t7_command; // display the additional information
extern String p10_b2_command;
extern String p10_b3_command;
extern String summer_mode_p10_bt0;
extern String winter_mode_p10_bt1;
extern String p10_c0_value;
extern String p10_c1_value;
extern String p10_bt0_value;
extern String p10_bt1_value;
extern String p10_t1;
extern String p10_t3;
//extern bool summer_mode_activated;
extern bool winter_mode;
extern bool heating_enabled;
extern bool antifreeze_ebanbled;
extern String p10_c0_enabled_112;
extern String p10_c0_disabled_113;
extern String p10_c1_enabled_114;
extern String p10_c1_disabled_115;

//page_12_disable_lock_pin//
//extern bool on_page_12;
extern String p12_b3_command;

//page_13_pin_input_page
extern String p13_n0;
extern String p13_b3_command;

//page_14_heaters_settings//
extern String p14_c0_value;
extern String p14_c1_value;
extern String p14_c2_value;
extern String p14_b5_command;
extern String p14_b1_command;
extern String p14_b0_command;
extern String p14_b7_command;
extern String p14_b4_command;
extern String p14_c0_on_1406;
extern String p14_c0_off_1407;
extern String p14_c1_on_1408;
extern String p14_c1_off_1409;
extern String p14_c2_on_1410;
extern String p14_c2_off_1411;
extern bool h1_enabled;
extern bool h2_enabled;
extern bool h3_enabled;
extern String heaters_settings;
// extern bool on_page_14;
extern bool H3_antifreeze_enabled;
//extern bool heaters_on_conditions_met;

//page_15_Overview//
extern String p15_t9;
extern String p15_t10;
extern String p15_t11;
extern String p15_t12;
extern String p15_t13;
extern String p15_t14;
extern String p15_t15;
extern String p15_t16;
extern String p15_t17;
extern String p15_t19;
// extern bool on_page_15;
extern String p15_b4;
extern float heat_exchanger_efficiency;

//page_17_dampers//
extern String p17_b0_command;
extern String p17_b1_command;
extern String p17_b2_command;
extern String p17_b3_command;
extern String p17_b4_command;
extern String p17_b5_command;
extern String p17_b6_command;
extern String p17_b7_command;
extern String p17_b8_command;
extern String p17_c0_command_on;
extern String p17_c0_command_off;
extern String p17_c1_command_on;
extern String p17_c1_command_off;
extern String p17_c2_command_on;
extern String p17_c2_command_off;
extern String p17_c3_command_on;
extern String p17_c3_command_off;
extern String p17_t12_command;
extern String p17_t13_vis;
extern String p17_t13_command;
extern String p17_t5;
extern String p17_t7;
extern String p17_t9;
extern String p17_t11;
extern String p17_c0;
extern String p17_c1;
extern String p17_c2;
extern String p17_c3;
extern bool d1_enabled;
extern bool d2_enabled;
extern bool d3_enabled;
extern bool d4_enabled;
extern int d1_time_delay;
extern int d2_time_delay;
extern int d3_time_delay;
extern int d4_time_delay;
extern String damper_settings;
// extern bool on_page_17;
extern String p17_b0_vis;
extern String p17_b1_vis;
extern String p17_c0_vis;
extern String p17_b2_vis;
extern String p17_b3_vis;
extern String p17_c1_vis;
extern int max_delay;
extern int min_delay;
extern bool damper_1_on;
extern bool damper_2_on;
extern bool damper_3_on;
extern bool damper_4_on;
extern bool d1_initial_start;
extern bool d2_initial_start;
extern bool d3_initial_start;
extern bool d4_initial_start;
extern bool d1_run_once;   //used as a run once variable
extern bool d2_run_once;   //used as a run once variable
extern bool d3_run_once;   //used as a run once variable
extern bool d4_run_once;   //used as a run once variable
extern bool d1_run_once_2; //used as a run once variable
extern bool d2_run_once_2; //used as a run once variable
extern bool d3_run_once_2; //used as a run once variable
extern bool d4_run_once_2; //used as a run once variable
extern int d1_initial_start_time_delay;
extern int d2_initial_start_time_delay;
extern int d3_initial_start_time_delay;
extern int d4_initial_start_time_delay;
extern bool d1_permission_fans_can_start;
extern bool d2_permission_fans_can_start;
extern bool d3_permission_fans_can_start;
extern bool d4_permission_fans_can_start;
extern bool dampers_have_permission_from_fans;

//page_18_Heater_1_settings//
extern String p18_b5_command;
extern String p18_b6_command;
extern String p18_b1_command;
extern String p18_b0_command;
extern String p18_b7_command;
extern String p18_b3_command;
extern String p18_b4_command;
extern String p18_t3;
extern String p18_t4;
extern String p18_t5;
extern int h1_on_temp;
extern int h1_off_temp;
extern int h1_time_period;
extern String heater1_settings;

//page_19_Heater_2_settings//
extern String p19_b5_command_1901;
extern String p19_b6_command;
extern String p19_b1_command;
extern String p19_b0_command;
extern String p19_b7_command;
extern String p19_b3_command;
extern String p19_b4_command;
extern String p19_t3;
extern String p19_t4;
extern String p19_t5;
extern int h2_on_temp;
extern int h2_off_temp;
extern int h2_time_period;
extern String heater2_settings;

//page_20_Heater_3_settings//
extern String p20_b5_command;
extern String p20_b6_command;
extern String p20_b1_command;
extern String p20_b0_command;
extern String p20_b7_command;
extern String p20_b3_command;
extern String p20_b4_command;
extern String p20_t3;
extern String p20_t4;
extern String p20_t5;
extern int h3_on_temp;
extern int h3_off_temp;
extern int h3_time_period;
extern String heater3_settings;

//page_21_Alarm_list//
//extern bool on_page_21;
extern String p21_b4_command_2101;
extern String p21_t1;
extern String p21_t2;
extern String alarm_message;

//page_22_lock?screen//
//extern String p22_b4_command;
//extern String p22_t0_text;
//extern String p22_t3_text;
//extern bool on_page_22;
//extern uint16_t screen_flicker;

//page_23_unlock_screen_with_pin//
//extern bool on_page_23;
extern String p23_b3_command;

//page_24_ScreenSaver//
//extern bool on_page_24;
extern String p24_t0_text;
extern String p24_t1_text;
extern String p24_t2_text;
extern String p24_t3_text;
extern String p24_t4_text;
extern String p24_t5_text;
extern String p24_t9_text;
extern String p24_t10_text;
extern String p24_t9_vis;
extern String p24_t10_vis;
extern String p24_p3_vis;
extern String p24_p4_vis;
extern String p24_p5_vis;
extern String p24_p6_vis;
extern String p24_p36_vis;
extern String p24_p35_vis;
extern String p24_p34_vis;
extern String p24_p7_vis;
extern String p24_p8_vis;
extern String p24_p9_vis;
extern String p24_p10_vis;
extern String p24_p11_vis;
extern String p24_p12_vis;
extern String p24_p13_vis;
extern String p24_p14_vis;
extern String p24_p15_vis;
extern String p24_p16_vis;
extern String p24_p17_vis;
extern String p24_p40_vis;
extern String p24_p39_vis;
extern String p24_p38_vis;
extern String p24_p30_vis;
extern String p24_p22_vis;
extern String p24_p23_vis;
extern String p24_p24_vis;
extern String p24_p25_vis;
extern String p24_p26_vis;
extern String p24_p27_vis;
extern String p24_p31_vis;
extern String p24_p32_vis;
extern String p24_p33_vis;
extern String p24_p37_vis;
extern String p24_p41_vis;
extern bool f1_already_on;
extern bool f2_already_on;
extern bool d1_already_on;
extern bool d1_not_available;
extern bool d2_already_on;
extern bool d2_not_available;
extern bool d3_already_on;
extern bool d3_not_available;
extern bool d4_already_on;
extern bool d4_not_available;
extern bool h1_already_on;
extern bool h1_not_available;
extern bool h2_already_on;
extern bool h2_not_available;
extern bool h3_already_on;
extern bool h3_not_available;
extern bool screen_loaded;
extern String p24_screen_touch;
extern String p24_alarm_touch;


