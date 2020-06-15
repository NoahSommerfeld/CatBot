/* Takes in a packet via serial connection and echoes it back.
- uses a made-up protocol:
- packet start symbol - '|'
- packet end symbol - '+'
- packet structure: TBD
*/






//parses any pending commands 
String refreshMailbox(){
  //serial.println("starting read");
  String tempCmd = "";
  int parseCount=0;
  char tempChar = '\0';
  if (Serial.available() > 0) {
    int tempData = Serial.read();
    tempChar = tempData;  
  //  Serial.println("got a character: '"+String(tempChar)+"' Ascii:"+tempData);
  }
  else{
    return "";
  }

  if(tempChar =='|'){ //start of packet
 //   Serial.println("got a startOfPacket");
    while(parseCount<10000){ //to avoid an infinite loop. TODO - update to use millis vs arb. clock cycles
      parseCount+=1;
      char tempChar = '\0'; 
      if (Serial.available() > 0) {
        int tempData2 = Serial.read();
        tempChar = tempData2;
       }
       else{
        continue;
       }

      if(tempChar=='+'){ //end of packet
        //Serial.println("got an endofpacket");
        return tempCmd;
      }
      else if(tempChar == '|' || tempChar == 10){
      //  Serial.println("discarding char: '"+String(tempChar)+"'");
        //repeating start symbol or non text, do nothing
      }
      else{
      //  Serial.println("adding char '"+String(tempChar)+"'");
        if(tempChar != '\0'){
          tempCmd += tempChar;
        }
      }      
    }
  }
  else{
    return "";
  }
  return "timeout"; //timeout - drop the data that had been received
}
