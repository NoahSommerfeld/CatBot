#include <Servo.h>
#define SERVODRIVER SERVODRIVER_MAIN

Servo myservo; // create servo object to control a servo
int ServoPos = 0;

//configured servo values
#define CALIBRATIONOFFSET -25

void servoSetup()
{
  myservo.attach(SERVODRIVER);

  myservo.write(CALIBRATIONOFFSET);
  delay(1000);
  myservo.write(CALIBRATIONOFFSET+180);
  delay(1000);
  myservo.write(90+CALIBRATIONOFFSET);
  delay(1000);
}

//arg input pos from -90 (full left) to 90 (full right)
void setServoPosition(int pos){
  myservo.write(pos+90+CALIBRATIONOFFSET);
  
}
