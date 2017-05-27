// dollHouseTS_gv.cpp
//
// Header file for the dollHouse global Variables
// By Vincent Meligne

#include <Adafruit_NeoPixel.h>
#include "DollHouseTS.h"
#include <IRLib.h>;
#include "TouchScreen.h"

// NEOpixel
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_BRG + NEO_KHZ800);

int ledState = LOW;
unsigned long previousMillis = 0;

// IR 
IRsend My_Sender;
String messReceived = "";
String toSend="";

// Touchscreen
// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

struct config_TS
{
  int MINX;
  int MAXX;
  int MINY;
  int MAXY;
}
configurationTS;

// ******************* Color **********************
//floats to hold colour arrays
float colourArray[] = {0,0,0};
float whiteArray[] = {0,0,0};
float blackArray[] = {0,0,0};
int colorDef[11][3] = {{255,0,0},{255,25,0},{255,63,0},{255,156,0},{0,8,0},{0,255,0},{0,0,255},{0,255,213},{37,0,255},{255,0,72},{255,255,255}};
int colorI[3] = {0,0,0};

String WHERE[] = {"ALL","000","001","002","003","004","005","006","007"};
String COLOR[11] = {"RED","ORANGE","YELLOW","YELLOW1","GREEN","GREEN1","INDIGO","BLUE","PURPLE","MAGENTA","WHITE"};
String ACTION[] = {"ON","OFF","WHEEL","RAINBOW","PLUS","MINUS"};

struct whiteBal
{
  int red;
  int green;
  int blue;
}
whiteBalance;

struct blackBal
{
  int red;
  int green;
  int blue;
}
blackBalance;

int  buttonState = 0;
boolean balanceSet = false;
int avgRead;

String where = "";
String action = "";
String color = "";
