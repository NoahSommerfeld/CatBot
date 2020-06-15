/* TCP-level functionality to handle serial connections and abstract all non-payload logic from MAIN
- uses a made-up protocol:
- packet start symbol - '|'
- packet end symbol - '+'
- packet structure: TBD
*/

#define PACKETSTARTSYMBOL '|'
#define PACKETENDSYMBOL '+'
#define TIMEOUT 2000 //timeout value in milliseconds

long lastUpdateTime = 99999999;
boolean isRecording = false;
String pendingPacket = "";

//parses any pending commands 
String refreshMailbox(){
  char tempChar = '\0';
  while(Serial.available() > 0) {
    int tempData = Serial.read();
    tempChar = tempData;  
   //  Serial.println("got a character: '"+String(tempChar)+"' Ascii:"+tempData);
  
    if(tempChar ==PACKETSTARTSYMBOL){ //start of packet
      //   Serial.println("got a startOfPacket");
      isRecording = true;
      lastUpdateTime = millis();
      continue;
    }
    if(tempChar==PACKETENDSYMBOL){ //end of packet
      //Serial.println("got an endofpacket");
      String tempCmd = pendingPacket;
      isRecording = false; 
      pendingPacket = "";
      return tempCmd;
    }
    else if(tempChar == PACKETSTARTSYMBOL || tempChar == 10){
      //  Serial.println("discarding char: '"+String(tempChar)+"'");
      //repeating start symbol or non text, do nothing
    }
    else if(isRecording){
      //  Serial.println("adding char '"+String(tempChar)+"'");
      if(tempChar != '\0'){
        pendingPacket += tempChar;
        lastUpdateTime = millis();
      }
    }      
  }
  if(isRecording && pendingPacket.length() != 0 && (millis() - lastUpdateTime)>TIMEOUT){
      pendingPacket="";
      isRecording = false;
      return "TIMEOUT";    //timeout - drop the data that had been received
  }
  else{
    return "";
  }
}
