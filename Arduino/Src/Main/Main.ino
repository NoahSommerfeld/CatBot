#include <Servo.h>

/*
  HG7881_Motor_Driver_Example - Arduino sketch
   
  This example shows how to drive a motor with using HG7881 (L9110) Dual
  Channel Motor Driver Module.  For simplicity, this example shows how to
  drive a single motor.  Both channels work the same way.
   
  This example is meant to illustrate how to operate the motor driver
  and is not intended to be elegant, efficient or useful.
   
  Connections:
   
    Arduino digital output D10 to motor driver input B-IA.
    Arduino digital output D11 to motor driver input B-IB.
    Motor driver VCC to operating voltage 5V.
    Motor driver GND to common ground.
    Motor driver MOTOR B screw terminals to a small motor.
     
  Related Banana Robotics items:
   
    BR010038 HG7881 (L9110) Dual Channel Motor Driver Module
    https://www.BananaRobotics.com/shop/HG7881-(L9110)-Dual-Channel-Motor-Driver-Module
 
  https://www.BananaRobotics.com
*/
 
// wired connections
#define HG7881_B_IA 10 // D10 --> Motor B Input A --> MOTOR B +
#define HG7881_B_IB 11 // D11 --> Motor B Input B --> MOTOR B -
#define SERVODRIVER 9 //wire controlling line
#define ultrasonic_trigger_pin 13
#define ultrasonic_echo_pin 12

// functional connections
#define MOTOR_B_PWM HG7881_B_IA // Motor B PWM Speed
#define MOTOR_B_DIR HG7881_B_IB // Motor B Direction
 
// the actual values for "fast" and "slow" depend on the motor
#define PWM_SLOW 150  // arbitrary slow speed PWM duty cycle
#define PWM_FAST 2 // arbitrary fast speed PWM duty cycle
#define DIR_DELAY 1000 // brief delay for abrupt motor changes
#define CONTROL_PAUSE 2000 // to pause between steps for dramatic effect

//configured servo values
#define FULL_LEFT -25
#define FULL_RIGHT 155
#define STRAIGHT (FULL_RIGHT+FULL_LEFT)/2

Servo myservo; // create servo object to control a servo
int ServoPos = 0;

// defines variables
long duration;
int distance1=0;
int distance2=0;
int distance3=0;

void setup()
{
  myservo.attach(SERVODRIVER);
  Serial.begin( 9600 );
  pinMode(ultrasonic_trigger_pin, OUTPUT); // Sets the trigPin as an Output
  pinMode(ultrasonic_echo_pin, INPUT); // Sets the echoPin as an Input
  pinMode( MOTOR_B_DIR, OUTPUT );
  pinMode( MOTOR_B_PWM, OUTPUT );
  digitalWrite( MOTOR_B_DIR, LOW );
  digitalWrite( MOTOR_B_PWM, LOW );
  pinMode(LED_BUILTIN, OUTPUT);
   // delay(3000); //always start with a delay so I can move the wheels if needed
  myservo.write(FULL_LEFT);
  delay(1000);
  myservo.write(FULL_RIGHT);
  delay(1000);
  myservo.write(STRAIGHT);
 // delay(2000);
}


void loop(){
 //myservo.write(90) //arbitrary point?
long tempDistance = readUltrasonic(); //returns in centimeters

// Prints the distance on the Serial Monitor
Serial.print("Distance: tempDistance");

if(tempDistance<30){
  Serial.println("wall: stopping");
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  stopBMotor();
}
else{
Serial.println("Distance: driving");
  driveSlow();
}

  
  /*Serial.println( "st0arting" );;
  Serial.println( "slow forward..." );
   // always stop motors briefly before abrupt changes
   driveSlow();
   delay(CONTROL_PAUSE);
   
   Serial.println( " fast forward..." );
    driveBMotor(true, PWM_FAST);
    delay(CONTROL_PAUSE);
    Serial.println( "stoppingd..." );
   stopBMotor();
    delay(CONTROL_PAUSE);
*/
}

long readUltrasonic(){
  // Clears the trigPin
  digitalWrite(ultrasonic_trigger_pin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(ultrasonic_trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonic_trigger_pin, LOW);

  //push them down by one
  distance3 = distance2;
  distance2 = distance1;
  
  // Reads the echoPin, returns the sound wave travel time in microseconds  (0.340197 centimeters /microsecond at sea level, round trip)
  distance1 = pulseIn(ultrasonic_echo_pin, HIGH) * 0.034/2;

  return (distance1+distance2+distance3)/3;
}

void driveSlow(){
   driveBMotor(true, PWM_FAST); //to get started rolling
   delay(150);
   driveBMotor(true, PWM_SLOW);
}
void stopBMotor(){
  digitalWrite( MOTOR_B_DIR, LOW );
  digitalWrite( MOTOR_B_PWM, LOW );
  delay(DIR_DELAY);
}

//true = forward
void driveBMotor(boolean direction, int speed){
  if(direction){
     digitalWrite( MOTOR_B_DIR, HIGH );
  }else{
     digitalWrite( MOTOR_B_DIR, LOW );
  }
  analogWrite( MOTOR_B_PWM, speed);
}
