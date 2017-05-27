// dollHouseTS_gv.h
//
// Header file for the dollHouse global Variables
// By Vincent Meligne

#include <Adafruit_NeoPixel.h>
#include "DollHouseTS.h"
#include <IRLib.h>;
#include "TouchScreen.h"

// NEOpixel
extern Adafruit_NeoPixel pixels;

extern int ledState;                         // ledState used to set the LED
extern unsigned long previousMillis;         // will store last time LED was updated

// IR
extern IRsend My_Sender;
extern String messReceived;
extern String toSend;

// Touchscreen
extern TouchScreen ts;

extern struct config_TS
{
  int MINX;
  int MAXX;
  int MINY;
  int MAXY;
}
configurationTS;

// ******************* Color **********************
//floats to hold colour arrays

extern float colourArray[];
extern float whiteArray[];
extern float blackArray[];
extern int colorDef[3][3];
extern int colorI[3];

extern String WHERE[];
extern String COLOR[];
extern String ACTION[];

extern struct whiteBal
{
  int red;
  int green;
  int blue;
}
whiteBalance;

extern struct blackBal
{
  int red;
  int green;
  int blue;
}
blackBalance;

extern int  buttonState;
extern boolean balanceSet;
extern int avgRead;

extern String where;
extern String action;
extern String color;
