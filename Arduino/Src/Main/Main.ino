#define SERVODRIVER_MAIN 9 //wire controlling line
#define ultrasonic_trigger_pin_main 13
#define ultrasonic_echo_pin_main 12

#define HG7881_B_IA_main 10 // D10 --> Motor B Input A --> MOTOR B +
#define HG7881_B_IB_main 11 // D11 --> Motor B Input B --> MOTOR B -

//start target values
int targetDriveSpeed=0;
int currentDriveSpeed=0; //initalize to a stopped speed

int targetServoPos = 90;
int currentServoPos = 90;

//startSensorValues
long lastDistance = 0;

String lastCommand = "";

void setup()
{
  Serial.begin( 9600 );
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
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

  if(tempMessage.length() >0){
    Serial.println("Current Speed: "+String(currentDriveSpeed));
    Serial.println("Current ServoPos: "+String(currentServoPos));
  }
  //action
 // action();
 
  // Prints the distance on the Serial Monitor
//  Serial.println("Distance: "+String(lastDistance));
  
}

void checkSensors(){
  long lastDistance = readUltrasonic(); //returns in centimeters
}

//void action(){
//}

void makeDecisions(String command){
  if(command == "GoLeft"){
    lastCommand = command;
    targetDriveSpeed = 100;
    targetServoPos = 25;
  }
  else if(command == "GoStraight"){
    lastCommand = command;
    targetDriveSpeed = 100;
    targetServoPos = 90;
  }
  else if(command == "GoRight"){
    lastCommand = command;
    targetDriveSpeed = 100;
    targetServoPos = 135;
  }
  else if(command == "BackLeft"){
    lastCommand = command;
    targetDriveSpeed = -100;
    targetServoPos = 45;
  }
  else if(command == "BackStraight"){
    lastCommand = command;
    targetDriveSpeed = -100;
    targetServoPos = 90;
  }
  else if(command =="BackRight"){
    lastCommand = command;
    targetDriveSpeed = -100;
    targetServoPos = 135;
  }
  else if(command = "Stop"){
    lastCommand = command;
    targetDriveSpeed = 0;
    targetServoPos = 90;
  }
  currentServoPos = setSpeed(decideSpeed());
  currentServoPos = setServoPosition(decideDrivePos());
}

int decideDrivePos(){
  return targetServoPos;
}

//return target speed (%). NOTE: No wall protection for reverse speeds! 
int decideSpeed(){
  if(targetDriveSpeed < 0){
    return targetDriveSpeed;
  }
  int maxSpeed = 0;
   //decide speed
  if(lastDistance<20){
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    maxSpeed = 0;
  }
  else if (lastDistance<50){
     maxSpeed = 25;  
  }
  else if (lastDistance>=50){
    maxSpeed = 75;
  }
  else{
    Serial.println("ERROR - invalid distance choice");
  }

  if(targetDriveSpeed > maxSpeed){
    Serial.println("Overriding requested speed (last distance: "+String(lastDistance));
    return maxSpeed;
  }
  else{
    return targetDriveSpeed;
  }
}
