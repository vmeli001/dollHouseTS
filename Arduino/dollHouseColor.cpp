// dollHouseColor.cpp
//
// dollHouse color functions
// By Vincent Meligne

#include <arduino.h>
#include <EEPROM.h>
#include "EepromAnything.h"
#include "DollHouseTS.h"
#include "dollHouseTS_gv.h"
#include "dollHouseColor.h"

void updateLigths(String where, String color){
  if (color == "RAINBOW"){
    //rainbow();
  }
  else if (color == "WHEEL"){
    checkColor();
    sendColor(where);
  }
  else {
    

  }
}


void checkBalance(){
  // Check if the balance has been set, if not, set it
  // Update whiteBalance and blackBalance if the data is
  // available on the EEPROM.

  EEPROM_readAnything(110,whiteBalance);
  EEPROM_readAnything(120,blackBalance);

  // If the first and last values in the balance struct are 255 then set the balance.
  if (whiteBalance.red == 255 || blackBalance.blue == 255){
    setBalance();
  }
  /*
  if(balanceSet == false){
   setBalance();
   }
   */
}

void setBalance(){
  //set white balance
  //Serial.println("Check Balance (WHITE) in 5s:");
  delay(5000);                              //delay for five seconds, this gives us time to get a white sample in front of our sensor
  //scan the white sample.
  //go through each light, get a reading, set the base reading for each colour red, green, and blue to the white array
  for(int i = 0;i<=2;i++){
    pixels.setPixelColor(0, pixels.Color(colorDef[i][0],colorDef[i][1],colorDef[i][2]));
    pixels.show();
    //digitalWrite(ledArray[i],HIGH);
    delay(100);
    getReading(5);          //number is the number of scans to take for average, this whole function is redundant, one reading works just as well.
    whiteArray[i] = avgRead;
    pixels.setPixelColor(0, pixels.Color(0,0,0));
    pixels.show();
    //digitalWrite(ledArray[i],LOW);
    delay(100);
    Serial.println(whiteArray[i]);
  }
  whiteBalance.red=whiteArray[0];
  whiteBalance.green=whiteArray[1];
  whiteBalance.blue=whiteArray[2]; 
  EEPROM_writeAnything(110, whiteBalance);

  //done scanning white, now it will pulse blue to tell you that it is time for the black (or grey) sample.
  //set black balance
  //Serial.println("Check Balance (BLACK) in 5s:");
  delay(5000);              //wait for five seconds so we can position our black sample 
  //go ahead and scan, sets the colour values for red, green, and blue when exposed to black
  for(int i = 0;i<=2;i++){
    pixels.setPixelColor(0, pixels.Color(colorDef[i][0],colorDef[i][1],colorDef[i][2]));
    pixels.show();
    //digitalWrite(ledArray[i],HIGH);
    delay(100);
    getReading(5);
    blackArray[i] = avgRead;

    //blackArray[i] = analogRead(2);
    pixels.setPixelColor(0, pixels.Color(0,0,0));
    pixels.show();
    //digitalWrite(ledArray[i],LOW);
    delay(100);
  }
  blackBalance.red=blackArray[0];
  blackBalance.green=blackArray[1];
  blackBalance.blue=blackArray[2]; 
  EEPROM_writeAnything(120, blackBalance);
  
  //set boolean value so we know that balance is set
  balanceSet = true;
  //Serial.println("DONE:");
  //delay another 5 seconds to allow the human to catch up to what is going on
  delay(5000);
}

void checkColor(){
  //Serial.println("Check Colour :");
  for(int i = 0;i<=2;i++){
    pixels.setPixelColor(0, pixels.Color(colorDef[i][0],colorDef[i][1],colorDef[i][2]));
    pixels.show();
    //digitalWrite(ledArray[i],HIGH);  //turn or the LED, red, green or blue depending which iteration
    delay(100);                      //delay to allow CdS to stabalize, they are slow
    getReading(5);                  //take a reading however many times
    colourArray[i] = avgRead;        //set the current colour in the array to the average reading
    float greyDiff = whiteArray[i] - blackArray[i];                    //the highest possible return minus the lowest returns the area for values in between
    colourArray[i] = constrain((colourArray[i] - blackArray[i])/(greyDiff)*255,0,255); //the reading returned minus the lowest value divided by the possible range multiplied by 255 will give us a value roughly between 0-255 representing the value for the current reflectivity(for the colour it is exposed to) of what is being scanned
    pixels.setPixelColor(0, pixels.Color(0,0,0));
    pixels.show();
    //digitalWrite(ledArray[i],LOW);   //turn off the current LED
    delay(100);
  }
  for (int n=0;n<=2;n++){
    colorI[n]=colourArray[n];
  }
}

void getReading(int times){
  int reading;
  int tally=0;
  //take the reading however many times was requested and add them up
  for(int i = 0;i < times;i++){
    reading = analogRead(4);
    tally = reading + tally;
    delay(10);
  }
  //calculate the average and set it
  avgRead = (tally)/times;
}


void sendColor(String where){
// Sends the location and color code via IR.
  String toSend = "W: ";
  toSend += where;
  toSend += "R: ";
  toSend += String(int(colourArray[0]));
  toSend += "G: ";
  toSend += String(int(colourArray[1]));
  toSend += "B: ";
  toSend += String(int(colourArray[2]));

  for (int i = 0; i < toSend.length(); i++){
    My_Sender.send(RC5,toSend.charAt(i), 12); 
    delay(20);
  }
  My_Sender.send(RC5,13, 12);  //send a RETURN
  delay(1000);
}

