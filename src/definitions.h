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
extern float fan1_0_10_voltage_input; //input from display
extern int fan1_0_10_voltage_output;
extern float fan_1_Vd;
extern float fan_1_Dc;
extern String f1_Nextion_Text_Field;
extern String ref_fans_screen_cmd;

//FAN 2
#define fan_2_PWM_pin 33
extern const int fan_2_PWM_Channel;
extern const int fan_2_PWM_resolution;
extern const int fan_2_PWM_frequency;
extern float fan2_0_10_voltage_input;
extern int fan2_0_10_voltage_output;
extern float fan_2_Vd;
extern float fan_2_Dc;
extern String f2_Nextion_Text_Field;

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
extern bool f1_on_off_state;
extern bool f2_on_off_state;
extern String new_settings_fans;
extern String old_settings_fans;
extern String saved_settings_fans;
extern String f1_voltage_string;
extern String f2_voltage_string;
extern String f1_on_off_state_string;
extern String f2_on_off_state_string;
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
/////DISPLAY/////
extern String f1_Nextion_Text_Field;
extern String f1_plus_cmd;
extern String f1_minus_cmd;
extern String f2_Nextion_Text_Field;
extern String f2_plus_cmd;
extern String f2_minus_cmd;
extern String ref_fans_screen_cmd;
extern String ref_temp1_screen_cmd;
extern String ref_temp2_screen_cmd;
extern String t1_Nextion_Text_Field;
extern String t2_Nextion_Text_Field;
extern String t3_Nextion_Text_Field;
extern String t4_Nextion_Text_Field;
extern String on_temp_screen_one;
extern int temperature_sensor;
extern int display_brightness;
extern String display_brightness_string;
extern int auto_off_period;
extern String auto_off_period_string;

extern int ten_seconds;
extern int twenty_seconds;
extern int sixty_seconds;
extern int hudredAndTwenty_seconds;
extern bool calculate_time_for_auto_screen_off;
extern bool display_auto_on_off_state;
extern String display_auto_on_off_state_string;
extern bool display_screen_lock_on_off_state;
extern String display_screen_lock_on_off_state_string;
extern String new_display_settings;
extern String old_display_settings;
extern String saved_values_display_settings;
extern String screen_lock_pin;
extern String screen_lock_pin_string;

extern String screen_lock_pin_confirm;
extern String screen_lock_pin_first_attemt;

extern const String master_pin;
extern int display_screen_lock_period;
extern String display_screen_lock_period_string;
extern uint16_t number_of_tries;
extern uint16_t number_of_tries_master_pin;
extern String master_pin_input;

/////TEMPERATURES/////
extern String h_manual_on_off;
extern bool h_manual_control_state_new;
extern bool h_manual_control_state_old;
extern String h1_manual_on;
extern String h1_manual_off;
extern String h2_manual_on;
extern String h2_manual_off;
extern String h3_manual_on;
extern String h2_manual_off;
extern String h1_Nextion_Text_Field;
extern String h2_Nextion_Text_Field;
extern String h3_Nextion_Text_Field;
extern uint8_t threshold_temperature;
extern uint8_t turn_everything_off_temperature_threshold;


/////HEATERS/////
extern bool new_state_h1;
extern bool heater1_on_off_state;
extern bool heater2_on_off_state;
extern bool heater3_on_off_state;
extern bool manual_control_button_state;

///Display components variables///
extern String p9_n0;
extern String p9_h0;
extern String p9_c0;
extern String p9_c1;
extern String p13_n0;

///incoming pre set commands from the nextion display///
extern String turn_heater_on_temp_limit_plus;    //increase the threshold temperature for turning the heaters on
extern String turn_heater_on_temp_limit_minus;   // decrease the threshold temperature for turning the heaters on
extern String turn_unit_off_on_temp_limit_plus;  // increase the threshold temperature for turning the unit off
extern String turn_unit_off_on_temp_limit_minus; // decrease the threshold temperature for turning the unit off
extern String go_to_page_set_temperatures;
extern String info_button_push_p10_t4; // display the additional information
extern String turn_off_info_text_p10_t5_and_t6;
extern String info_button_push_p10_t7; // display the additional information

