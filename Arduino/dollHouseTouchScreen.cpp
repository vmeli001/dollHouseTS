// dollHouseTouchScreen.cpp
//
// Touchscreen routines for the doll house project
// By Vincent Meligne

#include "TouchScreen.h"
#include "DollHouseTS.h"
#include "dollHouseTS_gv.h"
#include "dollHouseUtil.h"
#include "dollHouseColor.h"
#include <EEPROM.h>
#include <arduino.h>

void touchLoc(TSPoint p){
  if ((p.y > 30)&&(p.x>30)){
    // Rooms in the house
    if (p.y <105){
      if (p.x<130){
        blinkLED(100,3);
        where = "005";
      }
      else if ((p.x<230)&&(p.x>130)){
        blinkLED(100,3);
        where = "006";
      }
      else if ((p.x<330)&&(p.x>230)){
        blinkLED(100,3);
        where = "007";
      }      
    }
    else if((p.y>105)&&(p.y<175)){
      if (p.x<105){
        blinkLED(100,3);
        where = "004";
      }
      else if ((p.x<216)&&(p.x>105)){
        blinkLED(100,3);
        where = "003";
      }
      else if ((p.x<330)&&(p.x>216)){
        blinkLED(100,3);
        where = "002";
      }      
    }
    else if((p.y>175)&&(p.y<240)){
      if (p.x<180){
        blinkLED(100,3);
        where = "000";
      }
      else if ((p.x<300)&&(p.x>180)){
        blinkLED(100,3);
        where = "001";
      }
    }
    // Buttons 
    if ((p.x<460)&&(p.x>360)){
      if (p.y<70){
        action="OFF";
        blinkLED(100,1);
        sendIR(where,color,action);        
      }

      else if ((p.y<115)&&(p.y>75)){
        action="ON";
        blinkLED(100,1);
        sendIR(where,color,action);
      }
      else if ((p.y<160)&&(p.y>120)){
        action="ALL";
        blinkLED(100,1);
        sendIR(where,color,action);
      }
      else if ((p.y<205)&&(p.y>165)){
        action="RAINBOW";
        blinkLED(100,1);
        sendIR(where,color,action);       
      }
      else if (p.y>225){
        if ((p.x<380)&&(p.x>355)){
          action="PLUS";
          blinkLED(100,1);
          sendIR(where,color,action);
        }
        else if ((p.x<407)&&(p.x>382)){
          action="MINUS";
          blinkLED(100,1);
          sendIR(where,color,action);
        }
        else if ((p.x<450)&&(p.x>410)){
          checkBalance();
          action="WHEEL";
          checkColor();
          blinkLED(100,1);
          sendIR(where,color,action);
        }
      }
    }

    // Colors  
    else if((p.y>230)&&(p.y<272)){
      if (p.x<65){
        blinkLED(100,5);
        color = "RED";        
      }
      else if ((p.x<90)&&(p.x>65)){
        blinkLED(100,5);
        color = "ORANGE";
      }
      else if ((p.x<115)&&(p.x>90)){
        blinkLED(100,5);
        color = "YELLOW";
      }
      else if ((p.x<140)&&(p.x>115)){
        blinkLED(100,5);
        color = "YELLOW1";
      }
      else if ((p.x<165)&&(p.x>140)){
        blinkLED(100,5);
        color = "GREEN";
      }
      else if ((p.x<190)&&(p.x>165)){
        blinkLED(100,5);
        color = "GREEN1";
      }
      else if ((p.x<215)&&(p.x>190)){
        blinkLED(100,5);
        color = "INDIGO";
      }
      else if ((p.x<240)&&(p.x>215)){
        blinkLED(100,5);
        color = "BLUE";
      }
      else if ((p.x<265)&&(p.x>240)){
        blinkLED(100,5);
        color = "PURPLE";
      }
      else if ((p.x<290)&&(p.x>265)){
        blinkLED(100,5);
        color = "MAGENTA";
      }
      else if ((p.x<315)&&(p.x>290)){
        blinkLED(100,5);
        color = "WHITE";
      }
    }
  }
}

void calibration(){
  /*
  configurationTS.MINX=80;
   configurationTS.MAXX=955;
   configurationTS.MINY=135;
   configurationTS.MAXY=865;
   */
  //EEPROM_readAnything(100,configurationTS);
  //EEPROM_writeAnything(100, configurationTS);
  //  EEPROM_readAnything(100,configurationTS);
  /*
  Serial.print(configurationTS.MINX);
   Serial.print("\t");
   Serial.print(configurationTS.MAXX);
   Serial.print("\t");
   Serial.print(configurationTS.MINY);
   Serial.print("\t");
   Serial.print(configurationTS.MAXY);
   
   //Serial.print(value, DEC);
   Serial.println();
   */
  //writeEEPROM();
  //readEEPROM();
}
