//Code used to operate the chipKIT Uno32 with a speaker

//Globals of which pins are attached to the chipKIT board
int RS = 4;
int RW = 30;
int E = 29;
int d0 = 41;
int d1 = 40;
int d2 = 39;
int d3 = 38;
int d4 = 13;
int d5 = 12;
int d6 = 37;
int d7 = 36;
int bitPinArray[] = {d0, d1, d2, d3, d4, d5, d6, d7};
int button = 11;
int speaker = 10;
int increment; //counter to know what frequency we are on

//arrays for the various commands
int functionSetArray[] = {0, 0, 0, 1, 1, 1, 0, 0};
int displayControlArray[] = {0, 0, 1, 1, 0, 0, 0, 0};
int clearDisplayArray[] = {1, 0, 0, 0, 0, 0, 0, 0};
int cursorHomeArray[] = {1, 1, 0, 0, 0, 0, 0, 0};

//arrays for the various characters
int charSpace[] = {0, 0, 0, 0, 0, 1, 0, 0};
int charZero[] = {0, 0, 0, 0, 1, 1, 0, 0};
int charTwo[] = {0, 1, 0, 0, 1, 1, 0, 0};
int charFive[] = {1, 0, 1, 0, 1, 1, 0, 0};
int charOne[] = {1, 0, 0, 0, 1, 1, 0, 0};
int charH[] = {0, 0, 0, 1, 0, 0, 1, 0};
int charZ[] = {0, 1, 0, 1, 1, 1, 1, 0};
int charR[] = {0, 1, 0, 0, 1, 0, 1, 0};
int charE[] = {1, 0, 1, 0, 0, 0, 1, 0};
int charA[] = {1, 0, 0, 0, 0, 0, 1, 0};
int charD[] = {0, 0, 1, 0, 0, 0, 1, 0};
int charY[] = {1, 0, 0, 1, 1, 0, 1, 0};

void setup(){
  increment = 0;
  pinMode(speaker, OUTPUT);
  digitalWrite(speaker, LOW);
  pinMode(button, INPUT);
  pinMode(RS, OUTPUT);
  pinMode(RW, OUTPUT);
  pinMode(E, OUTPUT);
  for(int i=0; i>8; i++){
    pinMode(bitPinArray[i], OUTPUT);
  }
  
  delay(20);
  //commanding function set
  sendCommand(functionSetArray);
  
  delay(1);
  //commanding display control
  sendCommand(displayControlArray);

  
  //Clearing the display and showing the "ready"
  delay(2);
  //commanding clear display
  sendCommand(clearDisplayArray);
  
  //commanding to get the cursor in the home position
  sendCommand(cursorHomeArray);
  
  for(int i=0; i<5; i++){
    //writing some blanks
    sendData(charSpace);
  }
  
  //writing the R onto the screen - R
  sendData(charR);
  
  //writing the second E onto the screen - E
  sendData(charE);
  
  //writing the A onto the screen - A
  sendData(charA);
  
  //writing the D onto the screen - D
  sendData(charD);
  
  //writing the Y onto the screen - Y
  sendData(charY);
}//END of Setup
 
void loop(){
  if(digitalRead(button)==HIGH){
    
    delay(2);
    //commanding to get the cursor in the home position
    sendCommand(cursorHomeArray);
    
//////////////////////////////////////////*
//    Displaying and playing 200 Hz      //
/////////////////////////////////////////*/
    if(increment == 0){//display and play 200
      for(int i=0; i<5; i++){
        //writing some blanks
        sendData(charSpace);
      }
      
      //writing the 2 onto the screen - 2
      sendData(charTwo);
      
      //writing the second 0 onto the screen - 0
      sendData(charZero);
      
      //writing the third character onto the screen - 0
      sendData(charZero);
      
      //writing the space character onto the screen - _
      sendData(charSpace);
      
      //writing the fourth character onto the screen - H
      sendData(charH);
      
      //writing the 5th character onto the screen - z
      sendData(charZ);
      
      increment = 1;
      while(digitalRead(button)==HIGH){
       playFreq(200, 200);
      }
      
      delay(1);
      //commanding clear display
    sendCommand(clearDisplayArray);
    }//END of 200 Hz
 
//////////////////////////////////////////*
//    Displaying and playing 500 Hz      //
/////////////////////////////////////////*/ 
    else if(increment == 1){//display and play 500
      delay(2);
      for(int i=0; i<5; i++){
        //writing some blanks
        sendData(charSpace);
      }
      
      //writing the 5 onto the screen - 5
      sendData(charFive);
      
      //writing the second 0 onto the screen - 0
      sendData(charZero);
      
      //writing the third character onto the screen - 0
      sendData(charZero);
      
      //writing the space character onto the screen - _
      sendData(charSpace);
      
      //writing the fourth character onto the screen - H
      sendData(charH);
      
      //writing the 5th character onto the screen - z
      sendData(charZ);
      
      increment = 2;
      while(digitalRead(button)==HIGH){
       playFreq(500, 200);
      }
      
      delay(1);
      //commanding clear display
      sendCommand(clearDisplayArray);
    }//END of 500 Hz
    
//////////////////////////////////////////*
//    Displaying and playing 1000 Hz     //
/////////////////////////////////////////*/
    else if(increment == 2){//display and play 1000
      for(int i=0; i<4; i++){
        //writing some blanks
        sendData(charSpace);
      }
      
      //writing the 1 onto the screen - 1
      sendData(charOne);
      
      //writing the first 0 onto the screen - 0
      sendData(charZero);
      
      //writing the second 0 onto the screen - 0
      sendData(charZero);
      
      //writing the third character onto the screen - 0
      sendData(charZero);
      
      //writing the space character onto the screen - _
      sendData(charSpace);
      
      //writing the fourth character onto the screen - H
      sendData(charH);
      
      //writing the 5th character onto the screen - z
      sendData(charZ);
      
      increment = 0;
      while(digitalRead(button)==HIGH){
        playFreq(1000, 200);
      }
      
      delay(1);
      //commanding clear display
      sendCommand(clearDisplayArray);
    }//END of 1000 Hz
    
  }//END of if the button is pressed
}//END of loop 


//////////////////////////////////////////////
//                                          //
//          User Defined Functions          //
//                                          //
//////////////////////////////////////////////


void playFreq(double freqHz, int durationMs)
{
    //Calculate the period in microseconds
    int periodMicro = int((1/freqHz)*1000000);
    int halfPeriod = periodMicro/2;
     
    //store start time
    int startTime = millis();
     
    //(millis() - startTime) is elapsed play time
    while ((millis() - startTime) < durationMs)    
    {
        digitalWrite(speaker, HIGH);
        delayMicroseconds(halfPeriod);
        digitalWrite(speaker, LOW);
        delayMicroseconds(halfPeriod);
    }
}//END of playing the frequency on the speaker

void sendCommand(int command[]){
  digitalWrite(RS, LOW);      //drive low for an instruction (command) transfer
  digitalWrite(RW, LOW);      //drive low for writing to the device
  digitalWrite(E, HIGH);      //bring high so that it can be driven low afterwards
  for(int i = 0; i<8; i++){
    digitalWrite(bitPinArray[i], command[i]);  //send the array of data
  }
  digitalWrite(E, LOW);       //send a low signal on the enable so it knows to process the device
}//END of sending a command signal

void sendData(int dataSet[]){
  delay(2);
  digitalWrite(RS, HIGH);      //drive high for an data (character) transfer
  digitalWrite(RW, LOW);      //drive low for writing to the device
  digitalWrite(E, HIGH);      //bring high so that it can be driven low afterwards
  for(int i=0; i<8; i++){
    digitalWrite(bitPinArray[i], dataSet[i]);  //send the array of data
  }
  digitalWrite(E, LOW);      //send a low signal on the enable so it knows to process the device
}//END of sending a set of data
