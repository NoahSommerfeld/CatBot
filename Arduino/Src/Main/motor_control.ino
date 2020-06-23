// wired connections
#define HG7881_B_IA HG7881_B_IA_main // D10 --> Motor B Input A --> MOTOR B +
#define HG7881_B_IB HG7881_B_IB_main // D11 --> Motor B Input B --> MOTOR B -

// functional connections
#define MOTOR_B_PWM HG7881_B_IA // Motor B PWM Speed
#define MOTOR_B_DIR HG7881_B_IB // Motor B Direction

// the actual values for "fast" and "slow" depend on the motor
#define PWM_SLOW 250  // arbitrary slow speed PWM duty cycle
#define PWM_FAST 2 // arbitrary fast speed PWM duty cycle

#define DIR_DELAY 1000 // brief delay for abrupt motor changes
#define CONTROL_PAUSE 2000 // to pause between steps for dramatic effect



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

void motorSetup()
{
 pinMode( MOTOR_B_DIR, OUTPUT );
  pinMode( MOTOR_B_PWM, OUTPUT );
  digitalWrite( MOTOR_B_DIR, LOW );
  digitalWrite( MOTOR_B_PWM, LOW );
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


//newSpeed - percentage of speed to drive (-100 full back, 0 = stop, 100 full forward)
int setSpeed(int newSpeed){
  if(newSpeed == currentDriveSpeed){
    return;
  }
  int candidateSpeed = abs(newSpeed);
  boolean direction = true;
  int PWM_Setting = 0;
  if(newSpeed <0){
    direction = false;
   PWM_Setting = (PWM_SLOW - ((PWM_SLOW*(newSpeed*-1))/100)+1); //speed inversely correlated to PWM
  }
  else{
    direction = true;
    PWM_Setting = (PWM_SLOW - ((PWM_SLOW*(newSpeed))/100)+1);
  }
    
  //set the speed
  
  if(newSpeed == (currentDriveSpeed*-1)){
    stopBMotor();
    delay(1000); //let the car stop
  }
  if(newSpeed==currentDriveSpeed){
    // Serial.println("do nothing");
    //do nothing
  }
  else if(abs(newSpeed)>abs(currentDriveSpeed)){
    Serial.println("speed up to"+String(newSpeed)+" and "+String(PWM_Setting));
    driveBMotor(direction, PWM_FAST); //to get the car moving
    delay(150);
    driveBMotor(direction, PWM_Setting);
    currentDriveSpeed = newSpeed;
  }
  else if(newSpeed == 0){
    Serial.println("wall: stopping"+String(newSpeed)+" and "+String(PWM_Setting));
    stopBMotor();
    currentDriveSpeed = newSpeed;
  }
  else{
    Serial.println("slow down to "+String(newSpeed)+" and "+String(PWM_Setting));
    driveBMotor(direction, PWM_Setting);
    currentDriveSpeed = newSpeed;
  }
  return newSpeed;
}
 
