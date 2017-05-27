// dollHouseUtil.cpp
//
// Declares the utility functions used in the doll house project
// By Vincent Meligne
#include "DollHouseTS.h"
#include "dollHouseTS_gv.h"
#include "dollHouseUtil.h"
#include <EEPROM.h>
#include <arduino.h>

void blinkLED(int duration, int times){
  for( int i=0; i<times; i++){
    digitalWrite(LEDpin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(duration);               // wait for a second
    digitalWrite(LEDpin, LOW);    // turn the LED off by making the voltage LOW
    delay(duration);
  }
}

void sendIR(String where, String color, String action){
// Sends the location and color code via IR.
  
  colorInterpret(color);
  String toSend="*";
  toSend += "W: ";
  toSend += where;
  toSend += "R: ";
  toSend += String(colorI[0]);
  toSend += "G: ";
  toSend += String(colorI[1]);
  toSend += "B: ";
  toSend += String(colorI[2]);
  toSend += "A: ";
  toSend += action;

  for (int i = 0; i < toSend.length(); i++){
    My_Sender.send(RC5,toSend.charAt(i), 12); 
    delay(5);
  }
  My_Sender.send(RC5,13, 12);  //send a RETURN
  delay(100);
  toSend="";
}

void colorInterpret(String color){
  for (int i=0; i < NUMCOLOR; i++){
    if (color == COLOR[i]){
      //blinkLED(100,10);
      for (int j=0; j<3; j++){
        colorI[j] = colorDef[i][j];
      }
    }
  }
}

void blinkDelay(int duration, int frequency){
  unsigned long currentMillis = millis();
  int interval = duration / frequency;
  
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    // set the LED with the ledState of the variable:
    digitalWrite(LEDpin, ledState);
  }
}

void readEEPROM(){
  for (int address = (100 ); address < 110 ; address++){
    int value = EEPROM.read(address);
    Serial.print(address);
    Serial.print("\t");
    Serial.print(value, DEC);
    Serial.println();
  }
}

void writeEEPROM(){
  for (int address = 100; address < 110; address++){
    EEPROM.write(address,10 + address);
  }
  //delay(100);
}

void split_10bit(int value){
  int lBit = value & 0xff;
  int hBit = (value & 0xff00) >>8;
} 
