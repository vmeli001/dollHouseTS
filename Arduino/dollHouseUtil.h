// dollHouseUtil.h
//
// Declares the utility functions used in the doll house project
// By Vincent Meligne

#include "DollHouseTS.h"
#include <EEPROM.h>
#include <arduino.h>

void blinkLED(int duration, int times);
void blinkDelay(int duration, int frequency);

void readEEPROM();
void writeEEPROM();
void split_10bit();

void colorInterpret(String color);
void sendIR(String where, String color, String action);
