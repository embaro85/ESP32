#include "Display.h"
#include "definitions.h"
#include "Fans.h"

void f1_calculate_pwm_value()
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

void Fans::fan1_control_voltage_up(String Nextion_Text_Field_f1, float f1_control_voltage, String cmd)
{
  if (cmd == inData)
  
  { 
    Serial.println(f1_control_voltage);
    // incerase fan 1 voltage
    if (f1_control_voltage <= 10.0)
    { 
    Serial.println(f1_control_voltage);
      f1_control_voltage = f1_control_voltage + 0.1;
      Serial.print("the new value is: ");
      Serial.println(f1_control_voltage);
      outData = Nextion_Text_Field_f1 + String(f1_control_voltage, 1) + String(" V") + "\""; // generate string for the display
      Serial.print("the new link is: ");
      Serial.println(outData);
      display_control.sendDataToDisplay();
      f1_calculate_pwm_value();
    }
  }
}

/*void Fans::fan1_control_voltage_up(String Nextion_Text_Field_f1, float f1_control_voltage, String cmd)
{
  if (cmd == inData)
  { // incerase fan 1 voltage
    if (fan1_0_10_voltage_input <= 10.0)
    {
      fan1_0_10_voltage_input = fan1_0_10_voltage_input + 0.1;
      outData = Nextion_Text_Field_f1 + String(f1_control_voltage, 1) + String(" V") + "\""; // generate string for the display

      display_control.sendDataToDisplay();
      f1_calculate_pwm_value();
    }
  }
}*/

void Fans::fan1_control_voltage_down(String Nextion_Text_Field_f1, float f1_control_voltage, String cmd)
{
  if (cmd == inData)
  { // decrease fan 1 voltage
    if (f1_control_voltage >= 0.1)
    {
      f1_control_voltage = f1_control_voltage - 0.1;
      outData = Nextion_Text_Field_f1 + String(fan1_0_10_voltage_input, 1) + String(" V") + "\""; // generate string for the display
      display_control.sendDataToDisplay();
      f1_calculate_pwm_value();
    }
  }
}

void Fans::fan1_control_on_off()
{
  if (inData == "f1_on_off")
  { // toggle ON/OFF fan1
    f1_on_off_state = !f1_on_off_state;
    Serial.print("Fan 1 is: ");
    if (f1_on_off_state == true)
    {
      Serial.println("ON");
    }
    else
    {
      Serial.println("OFF");
    }
  }
}

void f2_calculate_pwm_value()
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

void Fans::fan2_control_voltage_up(String Nextion_Text_Field_f2, float f2_control_voltage, String cmd)
{

  if (cmd == inData)
  { // increase fan 2 voltage
    if (fan2_0_10_voltage_input <= 10.0)
    {
      fan2_0_10_voltage_input = fan2_0_10_voltage_input + 0.1;
      outData = Nextion_Text_Field_f2 + String(f2_control_voltage, 1) + String(" V") + "\"";
      display_control.sendDataToDisplay();
      f2_calculate_pwm_value();
    }
  }
}

void Fans::fan2_control_voltage_down(String Nextion_Text_Field_f2, float f2_control_voltage, String cmd)
{
  if (cmd == inData)
  { // decrease fan 2 voltage
    if (fan2_0_10_voltage_input >= 0.1)
    {
      fan2_0_10_voltage_input = fan2_0_10_voltage_input - 0.1;
      outData = Nextion_Text_Field_f2 + String(f2_control_voltage, 1) + String(" V") + "\"";
      display_control.sendDataToDisplay();
      f2_calculate_pwm_value();
    }
  }
}

void Fans::fan2_control_on_off()
{
  if (inData == "f2_on_off")
  { // toggle ON/OFF fan2
    f2_on_off_state = !f2_on_off_state;
    Serial.print("Fan 2 is: ");
    if (f2_on_off_state == true)
    {
      Serial.println("ON");
    }
    else
    {
      Serial.println("OFF");
    }
  }
};

Fans fans_control;
