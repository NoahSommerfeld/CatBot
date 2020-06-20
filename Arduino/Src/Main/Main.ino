#include <Servo.h>

#define SERVODRIVER_MAIN 9 //wire controlling line
#define ultrasonic_trigger_pin_main 13
#define ultrasonic_echo_pin_main 12

#define HG7881_B_IA_main 10 // D10 --> Motor B Input A --> MOTOR B +
#define HG7881_B_IB_main 11 // D11 --> Motor B Input B --> MOTOR B -

//start target values
int targetDriveSpeed=0;
int targetServoPos = 90;


//startSensorValues
long lastDistance = 0;

void setup()
{
  Serial.begin( 9600 );
  ultraSonicSetup();
  motorSetup();
  servoSetup();
  pinMode(LED_BUILTIN, OUTPUT);
   // delay(3000); //always start with a delay so I can move the wheels if needed
}


void loop(){

  //receive message
  String tempMessage = refreshMailbox();
  if(tempMessage.length() >0){
    Serial.println("Receved Message: "+tempMessage);
  }

 //check sensors
  checkSensors();

 //make decisions
  makeDecisions(tempMessage);

  //action
  action();
 
  // Prints the distance on the Serial Monitor
  Serial.println("Distance: "+String(lastDistance));
  
}

void checkSensors(){
  long lastDistance = readUltrasonic(); //returns in centimeters
}

void action(){
  setSpeed(targetDriveSpeed);
  setServoPosition(targetServoPos);
}

void makeDecisions(String command){
  targetDriveSpeed = decideSpeed();
  targetServoPos = decideDrivePos();
}

int decideDrivePos(){
  return 90;
}

//return target speed (%)
int decideSpeed(){
   //decide speed
  if(lastDistance<20){
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    return 0;
  }
  else if (lastDistance<50){
     return 25;  
  }
  else if (lastDistance>=50){
    return 75;
  }
  else{
    Serial.println("ERROR - invalid distance choice");
  }
}
