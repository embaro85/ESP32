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
extern String inData;  //main variable for incoming data from the display
extern String outData; //main variable for outgoing data to the display
extern bool f1_on_off_state;
extern bool f2_on_off_state;
extern String new_settings;
extern String old_settings;
extern String saved_settings;
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
extern unsigned long timer2; //used for temperature measurement
extern unsigned long timer3; //used for temperature measurement
extern unsigned long timer4; //used for temperature measurement
extern unsigned long timer5; //used for temperature measurement
extern unsigned long timer6; //used for temperature measurement
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
