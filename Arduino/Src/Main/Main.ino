/* Takes in a packet via serial connection and echoes it back.
- uses a made-up protocol:
- packet start symbol - '|'
- packet end symbol - '+'
- packet structure: TBD
*/

void setup()
{
   Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
 
}


void loop(){
String nextCMD = readNext();
//parse packet

if(nextCMD != ""){
  Serial.println("I heard: "+nextCMD);
}
//do stuff (echo it back?)

}

//parses any pending commands 
String readNext(){
  //serial.println("starting read");
  String tempCmd = "";
  int parseCount=0;
  String data = "";
  if (Serial.available() > 0) {
    int tempData = Serial.read();
    char tempChar = tempData;
    data = String(tempChar);
    
    Serial.println("got a character: "+data);
  }
  if(data.equals("|")){ //start of packet
    Serial.println("got a startOfPacket");
    while(parseCount<1000){ //to avoid an infinite loop
 
      int tempData2 = Serial.read();
      char tempChar2 = tempData2;
      data = String(tempChar2);
      Serial.println("data = "+data);
      if(data.equals("+")){ //end of packet
        Serial.println("got an endofpacket");
        break;
      }
      else if(data.equals("|") || data.equals('⸮') || data.equals('\n')){
        //repeating start symbol or non text, do nothing
      }
      else{
        tempCmd += data;
      }

      parseCount+=1;
    }
  }

  return tempCmd;
}

/*
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

  return (distance1+distance2+distance3)/3; //average the last three. Slows it down a bit but stops random stops
}

*/
/*
//newSpeed - percentage of speed to drive (0 = full stop)
void setSpeed(int newSpeed){
int PWM_Setting = (PWM_SLOW - ((PWM_SLOW*newSpeed)/100)+1); //speed inversely correlated to PWM
  
  //set the speed
if(newSpeed==currentDriveSpeed){
 // Serial.println("do nothing");
  //do nothing
}
else if(newSpeed>currentDriveSpeed){
  Serial.println("speed up to"+String(newSpeed)+" and "+String(PWM_Setting));
  driveBMotor(true, PWM_FAST); //to get the car moving
  delay(150);
  driveBMotor(true, PWM_Setting);
  currentDriveSpeed = newSpeed;
}
else if(newSpeed == 0){
  Serial.println("wall: stopping"+String(newSpeed)+" and "+String(PWM_Setting));
  stopBMotor();
  currentDriveSpeed = newSpeed;
}
else{
  Serial.println("slow down to "+String(newSpeed)+" and "+String(PWM_Setting));
     driveBMotor(true, PWM_Setting);
     currentDriveSpeed = newSpeed;
}
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
*/
