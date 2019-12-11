
#include <SoftwareSerial.h>
#include "DFRobotDFPlayerMini.h"

#define BUTTON_PIN A0 //Pin A0
boolean playing = false;
unsigned long previousMillis = 0; 

  
//Customize----------------------------------------------------------------------------------------------------------------------------
const long pause = 900000; // Pause between technopause in ms(15 min = 600000)
const int number = 1; // Number of songs (up to 65534)
//End Customize------------------------------------------------------------------------------------------------------------------------

SoftwareSerial softSerial(10, 11); // RX, TX
DFRobotDFPlayerMini mp3;

//#####################################################
void setup() {
  delay(500);
  softSerial.begin(9600);
  Serial.begin(115200); // start serial connection to print out debug messages and data
  
  //Print license
  Serial.println("--------------------------------------------------------------------------------------------------");
  Serial.println("Technopause for the Computer-Science Student Union of the Univertity of Tuebingen");
  Serial.println("Copyright (C) 2019  Jules Kreuer / not-a-feature");
  Serial.println();
  Serial.println("This program is free software: you can redistribute it and/or modify");
  Serial.println("it under the terms of the GNU General Public License as published by");
  Serial.println("the Free Software Foundation, either version 3 of the License, or");
  Serial.println("(at your option) any later version.");
  Serial.println();
  Serial.println("This program is distributed in the hope that it will be useful,");
  Serial.println("but WITHOUT ANY WARRANTY; without even the implied warranty of");
  Serial.println("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.");
  //Serial.println("See https://github.com/not-a-feature/technopause/blob/master/LICENSE for more. details.");
  Serial.println("--------------------------------------------------------------------------------------------------");

  randomSeed(analogRead(A2));
  
  if (!mp3.begin(softSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  mp3.volume(15);
}

void loop() {
  buttonStatus();
  unsigned long currentMillis = millis()+pause;
  
  if(playing && (currentMillis - previousMillis >= pause)) {
    previousMillis = currentMillis;
    playing = false;
    int randNum = random(1,number+1);
    mp3.playMp3Folder(randNum);
    Serial.println("technopause ---- Playing: " + String(randNum));
  }
}


void buttonStatus() {
  int buttonValue;
  buttonValue = analogRead(BUTTON_PIN);
  buttonValue = map(buttonValue, 0, 1024, 0, 2);
  if (buttonValue == 1) {
    playing = true;
  }
  else {
    playing = false;
  }
  delay(10);
}
