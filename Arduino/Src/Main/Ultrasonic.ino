#define ultrasonic_trigger_pin ultrasonic_trigger_pin_main
#define ultrasonic_echo_pin ultrasonic_echo_pin_main

int distance1=0;
int distance2=0;
int distance3=0;


void ultraSonicSetup(){
  pinMode(ultrasonic_trigger_pin, OUTPUT); // Sets the trigPin as an Output
  pinMode(ultrasonic_echo_pin, INPUT); // Sets the echoPin as an Input

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

  return (distance1+distance2+distance3)/3; //average the last three. Slows it down a bit but stops random stops
}
