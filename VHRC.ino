#include <AS5600.h>
#include <Wire.h>
#include <Joystick.h>

AS5600 as5600;   //  use default Wire

//Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
//  JOYSTICK_TYPE_MULTI_AXIS, 1, 0,
//  false, false, false, false, false, false,
//  false, false, true, true, true);

  Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_GAMEPAD, 1, 0,
  true, true, true, false, false, false,
  false, false, false, false, false);

int center;

void setup()
{
  center = 60;
  
  pinMode(21, OUTPUT);
  pinMode(20, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  digitalWrite(21, HIGH);
  
  as5600.begin(4);  //  set direction pin.
  as5600.setDirection(AS5600_CLOCK_WISE);  // default, just be explicit.
  
  Joystick.begin();
//  Joystick.setSteeringRange(80, 280);
//  Joystick.setAcceleratorRange(20, 520);
//  Joystick.setBrakeRange(540, 1020);

  Joystick.setXAxisRange(80, 280);
  Joystick.setYAxisRange(20, 520);
  Joystick.setZAxisRange(540, 1020);
  
  Wire.begin();
}

void loop()
{
//  if(digitalRead(15))
//    Joystick.pressButton(1);
    
  int thBr = analogRead(19);
  
//  if(thBr > 10 && thBr < 520) {
//    Joystick.setBrake(0);
//    Joystick.setAccelerator(520 - thBr);
//  }
//  else if(thBr > 540) {
//    Joystick.setAccelerator(0);
//    Joystick.setBrake(thBr);
//  }
//  else if(thBr >= 520 && thBr <= 540) {
//    Joystick.setBrake(0);
//    Joystick.setAccelerator(0);
//  }
//  
//  Joystick.setSteering((as5600.rawAngle() * AS5600_RAW_TO_DEGREES) - center);
//  Joystick.sendState();

  if(thBr > 10 && thBr < 520) {
    Joystick.setZAxis(0);
    Joystick.setYAxis(520 - thBr);
  }
  else if(thBr > 540) {
    Joystick.setYAxis(0);
    Joystick.setZAxis(thBr);
  }
  else if(thBr >= 520 && thBr <= 540) {
    Joystick.setZAxis(0);
    Joystick.setYAxis(0);
  }
  
  Joystick.setXAxis((as5600.rawAngle() * AS5600_RAW_TO_DEGREES) - center);
  Joystick.sendState();
}
