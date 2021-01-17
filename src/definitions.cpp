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
String inData;  //main variable for incoming data from the display
String outData; //main variable for outgoing data to the display
bool f1_on_off_state;
bool f2_on_off_state;
String new_settings_fans;
String old_settings_fans;
String saved_settings_fans;
String f1_voltage_string;
String f2_voltage_string;
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
unsigned long timer1 = 0; //used for temperature measurement
unsigned long timer2 = 0; //not used
unsigned long timer3 = 0; //not used
unsigned long timer4 = 0; //not used
unsigned long timer5 = 0; //not used
unsigned long timer6 = 0; //not used
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
int auto_off_period;
int ten_seconds;
int twenty_seconds;
int sixty_seconds;
int hudredAndTwenty_seconds;
bool calculate_time_for_auto_screen_off;
bool display_auto_on_off_state;
bool display_screen_lock_on_off_state;
String new_display_settings;
String old_display_settings;
String saved_values_display_settings;
uint16_t screen_lock_pin;
uint8_t screen_lock_pin_confirm;

const uint8_t screen_lock_master_pin = 9307;
String display_screen_lock_period;

/////TEMPERATURES/////
int temp_measure_interval = 100;
String h_manual_on_off = "ok_h_man";
bool h_manual_control_state_new;
bool h_manual_control_state_old;
String h1_manual_on = "h1_on";
String h1_manual_off = "h1_off";
String h2_manual_on = "h2_on";
String h2_manual_off = "h2_off";
String h3_manual_on = "h3_on";
String h3_manual_off = "h3_off";
String h1_Nextion_Text_Field = "th1.txt=\"";
String h2_Nextion_Text_Field = "th2.txt=\"";
String h3_Nextion_Text_Field = "th3.txt=\"";
byte threshhold_temperature = 27;

/////HEATERS/////
bool new_state_h1 = true;
bool heater1_on_off_state = false;
bool heater2_on_off_state;
bool heater3_on_off_state;
bool manual_control_button_state;
