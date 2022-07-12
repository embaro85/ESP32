#include "Display.h"
#include "definitions.h"
#include "Fans.h"
#include "Nextion_commands.h"
#include "SPIFFS.h"
#include "StringSplitter.h"
#include "Dampers.h"

void Fans::working_stream()
{
  fans_control.load_screen();
  fans_control.commands_from_display();
  fans_control.fans_start_routine();
  fans_control.save_settings();
  //fans_control.turn_fans_off();
}
void f1_calculate_pwm_value(float pwm)
{
  /* Setting the desired voltage by setting the duty cycle:
 *  desired voltage(Vd) = logic high level voltage(Vc) X duty cycle(Dc)
 *  Vd = Vc X Dc or Dc = Vd/Vc
 *  With measured 3.2 directly from the ESP for 2 volts(Vd) we have:
 *  Dc= 2/3,2 = 0,623 or 255*0,623 = 159   
 *  
 *  fan_1_Vd = fan_1_0-10_voltage_input / 5 - five is the voltage gain from the opAmp
 *  Dc = fan_1_Vd / 3.21
 *  Dc = 255 * Dc
 */
  fan_1_Vd = f1_control_voltage / 5;
  fan_1_Dc = fan_1_Vd / 3.24;
  fan_1_Dc = 255 * fan_1_Dc;
  ledcWrite(fan_1_PWM_Channel, fan_1_Dc);
}
void f2_calculate_pwm_value(float pwm)
{

  /* Setting the desired voltage by setting the duty cycle:
 *  desired voltage(Vd) = logic high level voltage(Vc) X duty cycle(Dc)
 *  Vd = Vc X Dc or Dc = Vd/Vc
 *  With measured 3.2 directly from the ESP for 2 volts(Vd) we have:
 *  Dc= 2/3,2 = 0,623 or 255*0,623 = 159   
 *  
 *  fan_1_Vd = fan_1_0-10_voltage_input / 5
 *  Dc = fan_1_Vd / 3.21
 *  Dc = 255 * Dc
 */

  fan_2_Vd = f2_control_voltage / 5;
  fan_2_Dc = fan_1_Vd / 3.24;
  fan_2_Dc = 255 * fan_2_Dc;
  ledcWrite(fan_2_PWM_Channel, fan_2_Dc);
}
float Fans::fan1_control_voltage_up()
{
  if (f1_control_voltage <= 9.5)
  {
    f1_control_voltage += 0.5;
    Serial.println(f1_control_voltage);
    nextion_commands.set_text_of_screen_component(p6_tf1_text, String(f1_control_voltage * 10, 0) + String("%"));
    f1_calculate_pwm_value(f1_control_voltage);
    return f1_control_voltage;
  }
}
float Fans::fan1_control_voltage_down()
{
  if (f1_control_voltage >= 2.5)
  {
    f1_control_voltage -= 0.5;
    nextion_commands.set_text_of_screen_component(p6_tf1_text, String(f1_control_voltage * 10, 0) + String("%"));
    f1_calculate_pwm_value(f1_control_voltage);
    return f1_control_voltage;
  }
}
float Fans::fan2_control_voltage_up()
{
  if (f2_control_voltage <= 9.5)
  {
    f2_control_voltage += 0.5;
    nextion_commands.set_text_of_screen_component(p6_tf2_text, String(f2_control_voltage * 10, 0) + String("%"));
    f2_calculate_pwm_value(f2_control_voltage);
    return f2_control_voltage;
  }
}
float Fans::fan2_control_voltage_down()
{
  if (f2_control_voltage >= 2.5)
  {
    f2_control_voltage -= 0.5;
    nextion_commands.set_text_of_screen_component(p6_tf2_text, String(f2_control_voltage * 10, 0) + String("%"));
    f2_calculate_pwm_value(f2_control_voltage);
    return f2_control_voltage;
  }
}
void Fans::fan1_turn_on()
{
  f1_on_off_state = true;
  digitalWrite(F1, HIGH);
  Serial.println("Fan 1 is ON");
}
void Fans::fan1_turn_off()
{
  f1_on_off_state = false;
  Serial.println("Fan 1 is OFF");
  //heaters_on_conditions_met = false; //if one of the fans is off the heaters should not start
  digitalWrite(F1, LOW);
}
void Fans::fan2_turn_on()
{
  f2_on_off_state = true;
  digitalWrite(F2, HIGH);
  Serial.println("Fan 2 is ON");
  f2_permission_for_heaters_start_granted = true;
}
void Fans::fan2_turn_off()
{

  f2_on_off_state = false;
  Serial.println("Fan 2 is OFF");
  //heaters_on_conditions_met = false; //if one of the fans is off the heaters should not start
  digitalWrite(F2, LOW);
  f2_permission_for_heaters_start_granted = false;
}
void Fans::turn_fans_off()
{
  if (permission_for_the_unit_start_granted == false)
    fans_control.fan1_turn_off();
  fans_control.fan2_turn_off();
}
void Fans::save_settings()
{ // check if there is a change in the fans setup and control voltage

  String _save_fans_settings = save_fans_settings;
  save_fans_settings = String(f1_control_voltage, 1) + "," + String(f2_control_voltage, 1) + "," + String(f1_on_off_state) + "," + String(f2_on_off_state) + ",";
  if (save_fans_settings != _save_fans_settings)
  {
    Serial.println(save_fans_settings);
    File saved_values_fans;
    saved_values_fans = SPIFFS.open("/values_fans.txt", FILE_WRITE);
    if (saved_values_fans.print(save_fans_settings))
    {
      Serial.println("New settings for the fans have been successfully written to the internal memory");
    }
    else
    {
      Serial.println("File write for the fan settings failed");
    }
    saved_values_fans.close();
  }
} //end function
void Fans::Load_Saved_Settings_Fans()
{

  File saved_values_fans;
  saved_values_fans = SPIFFS.open("/values_fans.txt", "r");
  if (!saved_values_fans)
  {
    Serial.println("Failed to open file for reading");
    return;
  }
  Serial.print("Fan Settings: ");
  save_fans_settings = saved_values_fans.readString();
  saved_values_fans.close();
  Serial.println(save_fans_settings);
  StringSplitter *splitter = new StringSplitter(save_fans_settings, ',', 4); // new StringSplitter(string_to_split, delimiter, limit)
  String _f1_control_voltage = splitter->getItemAtIndex(0);
  String _f2_control_voltage = splitter->getItemAtIndex(1);
  String _f1_on_off_state = splitter->getItemAtIndex(2);
  String _f2_on_off_state = splitter->getItemAtIndex(3);
  f1_control_voltage = _f1_control_voltage.toFloat();
  f2_control_voltage = _f2_control_voltage.toFloat();
  f1_on_off_state = _f1_on_off_state.toInt();
  f2_on_off_state = _f2_on_off_state.toInt();
  f1_calculate_pwm_value(f1_control_voltage);
  f2_calculate_pwm_value(f2_control_voltage);
}
void Fans::Refresh_Screen()
{
  nextion_commands.set_text_of_screen_component(p6_tf2_text, String(f1_control_voltage * 10, 0) + String("%"));
  nextion_commands.set_text_of_screen_component(p6_tf1_text, String(f2_control_voltage * 10, 0) + String("%"));
  if (permission_for_the_unit_start_granted == true)
  {
    nextion_commands.set_value_of_screen_component(p6_bt0_value, f1_on_off_state);
    nextion_commands.set_value_of_screen_component(p6_bt1_value, f2_on_off_state);
  }
  if (permission_for_the_unit_start_granted == false)
  {
    nextion_commands.set_value_of_screen_component(p6_bt0_value, 0);
    nextion_commands.set_value_of_screen_component(p6_bt1_value, 0);
  }
}
void Fans::commands_from_display()
{
  if (inData == p6_b4_610) // navigate to home screen
  {
    nextion_commands.go_to_page_Nextion(1);
    nextion_commands.on_page(1);
    fans_screen_loaded = false;
  }
  if (inData == p6_b5_601) // increase the voltage to fan 1
  {
    fans_control.fan1_control_voltage_up();
  }
  if (inData == p6_b6_602) // decrease voltage to fan 1
  {
    fans_control.fan1_control_voltage_down();
  }
  if (inData == p6_b7_603) // increase voltage to fan 2
  {
    fans_control.fan2_control_voltage_up();
  }
  if (inData == p6_b8_604) // decrease voltage of fan 2
  {
    fans_control.fan2_control_voltage_down();
  }
  if (inData == p6_bt0_off_606) // turn fan 1 OFF
  {
    fans_control.fan1_turn_off();
  }
  if (inData == p6_bt0_on_607) //turn fan 1 ON
  {
    fans_control.fan1_turn_on();
  }
  if (inData == p6_bt1_off_608) // turn fan2 OFF
  {
    fans_control.fan2_turn_off();
  }
  if (inData == p6_bt1_on_609) // turn fan 2 ON
  {
    fans_control.fan2_turn_on();
  }
}

void Fans::load_screen()
{
  if (on_page_number == Fans_6 && fans_screen_loaded == false)
  {
    fans_control.Refresh_Screen();
    fans_screen_loaded = true;
  }
}

void Fans::fans_start_routine()
{
  if (permission_for_the_unit_start_granted == true)
  {
    if (d1_permission_fans_can_start == true && d2_permission_fans_can_start == true && d3_permission_fans_can_start == true && d4_permission_fans_can_start == true && fans_initial_start == true)
    {
      fans_have_permission_from_dampers = true;
      Serial.println("Fans start permission from dampers granted");
      dampers_have_permission_from_fans = true;
      timer16 = millis(); //used to reset the timer for dampers with a positive time delay period
    }
    if (fans_have_permission_from_dampers == true && fans_initial_start == true)
    {
      fans_initial_start = false;
      fans_control.fan1_turn_on();
      fans_control.fan2_turn_on();
    }
  }
  if (permission_for_the_unit_start_granted == false && fans_initial_start == false)
  {
    fans_control.fan1_turn_off();
    fans_control.fan2_turn_off();
    fans_initial_start = true;
    fans_have_permission_from_dampers = false;
  }
}

Fans fans_control;
