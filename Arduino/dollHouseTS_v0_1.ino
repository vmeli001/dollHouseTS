/*
Doll_House_Touchscreen
 
 This sketch is to be used as a remote to control the lights on the doll house. 
 The lights can be turned ON and OFF from the color as well as the color of the lights for each room.
 A color wheel is attached at the bottom of the remote, once calibrated
 an LDR sensor reads the color in front of it which can be sent to 
 the doll house via infrared.
 
 The circuit:
 * INPUTS
 - The four pins of the touchscreen are attached as input to
 A0, A1, A2, A3
 - The LDR is connected in series with a 10 kOhm resistor to ground
 the LDR output (between 10 k and LDR) is connected to A4 on the 
 arduino. Gnd----R(10k)--|--LDR---5V
 |
 A4
 * OUTPUTS
 - D3 is used with the IR transmitter (330 Ohm in series).
 - D6 (1 k Ohm in series) is connected to the data line of the
 WS2811 LED controller.
 - D13 is connected to the status LED.
 
 Created 01/24/2017
 By Vincent Meligne
 */
#include <stdint.h>
#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>
#include <IRLib.h>;
#include "EepromAnything.h"
#include "TouchScreen.h"
#include "DollHouseTS.h"
#include "dollHouseUtil.h"
#include "dollHouseTS_gv.h"
#include "dollHouseTouchScreen.h"
#include "dollHouseColor.h"

#ifdef __AVR__
#include <avr/power.h>
#endif

void setup(void) {
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  pinMode(buttonPin, INPUT);
  pinMode(LEDpin, OUTPUT);
  
  pixels.begin();
  pixels.show(); // Initialize all pixels to 'off'

  Serial.begin(9600);
 
  blinkLED(100,3);
  //checkBalance();
  //calibration();
  Serial.begin(9600);
}

void loop(void) {
  // a point object holds x y and z coordinates
  TSPoint p = ts.getPoint();
  p.x = map(p.x, TS_MINX, TS_MAXX, 0,TS_X);
  p.y = map(p.y, TS_MINY, TS_MAXY, 0,TS_Y);
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > ts.pressureThreshhold) {
    touchLoc(p);
    
  }
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  /*if (action == "WHEEL") {
    checkColor();
    action="";
    //sendColor();
  } 
  */
  
  delay(150);
}


