#include "Display.h"
#include "definitions.h"
#include "Fans.h"



void Fans::fan1_control()
{

  if (inData == "f1_pl")
  { // incerase fan 1 voltage
    if (fan1_0_10_voltage_input <= 10.0)
    {
      fan1_0_10_voltage_input = fan1_0_10_voltage_input + 0.1;
      outData = "tf1.txt=\"" + String(fan1_0_10_voltage_input, 1) + String(" V") + "\""; // generate string for the display

      display_control.sendDataToDisplay();
      f1_calculate_pwm_value();
      
    }
  }

  if (inData == "f1_mi")
  { // decrease fan 1 voltage
    if (fan1_0_10_voltage_input >= 0.1)
    {
      fan1_0_10_voltage_input = fan1_0_10_voltage_input - 0.1;
      outData = "tf1.txt=\"" + String(fan1_0_10_voltage_input, 1) + String(" V") + "\""; // generate string for the display
      display_control.sendDataToDisplay();
      f1_calculate_pwm_value();
    }
  }

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
void Fans::f1_calculate_pwm_value()
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
  fan_1_Vd = fan1_0_10_voltage_input / 5;
  fan_1_Dc = fan_1_Vd / 3.21;
  fan1_0_10_voltage_output = 255 * fan_1_Dc;
  ledcWrite(fan_1_PWM_Channel, fan1_0_10_voltage_output);
}
void Fans::fan2_control()
{

  if (inData == "f2_pl")
  { // increase fan 2 voltage
    if (fan2_0_10_voltage_input <= 10.0)
    {
      fan2_0_10_voltage_input = fan2_0_10_voltage_input + 0.1;
      outData = "tf2.txt=\"" + String(fan2_0_10_voltage_input, 1) + String(" V") + "\"";
      display_control.sendDataToDisplay();
      f2_calculate_pwm_value();
    }
  }

  if (inData == "f2_mi")
  { // decrease fan 2 voltage
    if (fan2_0_10_voltage_input >= 0.1)
    {
      fan2_0_10_voltage_input = fan2_0_10_voltage_input - 0.1;
      outData = "tf2.txt=\"" + String(fan2_0_10_voltage_input, 1) + String(" V") + "\"";
      display_control.sendDataToDisplay();
      f2_calculate_pwm_value();
    }
  }

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
}
void Fans::f2_calculate_pwm_value()
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
};

Fans fans_control;