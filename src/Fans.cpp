#include "Display.h"
#include "definitions.h"
#include "Fans.h"

void turn_fan2_on_or_off(uint8_t fan_number, String on_or_off) //F1 or F2
{
  if (on_or_off == "ON")
  {
    digitalWrite(fan_number, HIGH);
    f2_on_off_state = true;
    Serial.println(fan_number + " is: " + String(on_or_off));
  }
  if (on_or_off == "OFF")
  {
    digitalWrite(fan_number, LOW);
    f2_on_off_state = false;
    Serial.println(fan_number + " is: " + on_or_off);
  }
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
  fan_1_Vd = fan1_0_10_voltage_input / 5;
  fan_1_Dc = fan_1_Vd / 3.21;
  fan1_0_10_voltage_output = 255 * fan_1_Dc;
  ledcWrite(fan_1_PWM_Channel, fan1_0_10_voltage_output);
}

float Fans::fan1_control_voltage_up(String Nextion_Text_Field_f1, float f1_control_voltage, String cmd)
{
  if (cmd == inData)
  {
    // incerase fan 1 voltage
    if (f1_control_voltage <= 10.0)
    {
      f1_control_voltage += 0.1;
      outData = Nextion_Text_Field_f1 + String(f1_control_voltage, 1) + String(" V") + "\""; // generate string for the display
      display_control.sendDataToDisplay();
      f1_calculate_pwm_value(f1_control_voltage);
      return f1_control_voltage;
    }
  }
}

float Fans::fan1_control_voltage_down(String Nextion_Text_Field_f1, float f1_control_voltage, String cmd)
{
  if (cmd == inData)
  { // decrease fan 1 voltage
    if (f1_control_voltage >= 0.1)
    {
      f1_control_voltage -= 0.1;
      outData = Nextion_Text_Field_f1 + String(f1_control_voltage, 1) + String(" V") + "\""; // generate string for the display
      display_control.sendDataToDisplay();
      f1_calculate_pwm_value(f1_control_voltage);
      return f1_control_voltage;
    }
  }
}

void Fans::fan1_control_on_off()
{
  if (inData == "f1_on")
  { // toggle ON/OFF fan1
    digitalWrite(F1, HIGH);
    f1_on_off_state = true;
    Serial.println("Fan 1 is ON");
  }
  else if (inData == "f1_off")
  {
    digitalWrite(F1, LOW);
    f1_on_off_state = false;
    Serial.println("Fan 1 is OFF");
  }
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

  fan_2_Vd = fan1_0_10_voltage_input / 5;
  fan_2_Dc = fan_1_Vd / 3.21;
  fan2_0_10_voltage_output = 255 * fan_2_Dc;
  ledcWrite(fan_2_PWM_Channel, fan2_0_10_voltage_output);
}

float Fans::fan2_control_voltage_up(String Nextion_Text_Field_f2, float f2_control_voltage, String cmd)
{

  if (cmd == inData)
  { // increase fan 2 voltage
    if (f2_control_voltage <= 10.0)
    {
      f2_control_voltage += 0.1;
      outData = Nextion_Text_Field_f2 + String(f2_control_voltage, 1) + String(" V") + "\"";
      display_control.sendDataToDisplay();
      f2_calculate_pwm_value(f2_control_voltage);
      return f2_control_voltage;
    }
  }
}

float Fans::fan2_control_voltage_down(String Nextion_Text_Field_f2, float f2_control_voltage, String cmd)
{
  if (cmd == inData)
  { // decrease fan 2 voltage
    if (f2_control_voltage >= 0.1)
    {
      f2_control_voltage -= 0.1;
      outData = Nextion_Text_Field_f2 + String(f2_control_voltage, 1) + String(" V") + "\"";
      display_control.sendDataToDisplay();
      f2_calculate_pwm_value(f2_control_voltage);
      return f2_control_voltage;
    }
  }
}

void Fans::fan2_control_on_off()
{
  if (inData == "f2_on")
  {
    digitalWrite(F2, HIGH);
    f2_on_off_state = true;
    Serial.println("Fan 2 is ON");
  }
  else if (inData == "f2_off")
  {
    digitalWrite(F2, LOW);
    f2_on_off_state = false;
    Serial.println("Fan 2 is OFF");
  }
};

Fans fans_control;
