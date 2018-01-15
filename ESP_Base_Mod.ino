///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Include Files

#include <FS.h>                   // this needs to be first
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>          // ESP8266 Core WiFi Library (you most likely already have this in your sketch)
#include <time.h>
#include <simpleDSTadjust.h>
#include <DNSServer.h>            // Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     // Local WebServer used to serve the configuration portal
#include <ESP8266mDNS.h>
#include <WiFiManager.h>          // https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include <ArduinoJson.h> 

#include "Parameters.h"
#include "pins.h"
#include "Debug.h"
#include "FileSystem.h"
#include "Wifi.h"
#include "Upgrader.h"

#ifdef LCD
#include "LCD.h"
#endif

#ifdef LED2COLOR
#include "LED.h"
#endif



void ResetESP(){
  ESP.reset();
}

void setup() {
  InitPins();
  InitDebug();
  
  SendMessage("----- Startup of ESP -----");
  BuildHostName();
  
  InitFS();

  #ifdef LCD
  InitLCD();
  LcdMessage("Initializing...",0,0);
  #endif

  #ifdef LED
  
  InitLEDs();
  delay(100);
  SetLED(LEDRED,true);
  delay(2000);
  SetLED(LEDGRN,true);
  delay(2000);
  SetLED(LEDRED,false);
  delay(2000);
  SetLED(LEDGRN,false);
  
  #endif
  
  InitWifiManager();

  if(CheckWifiStatus()){
    InitOTA();
  }
}

void loop() {

}
