///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Defines

#define HOSTNAME "ESP-OTA-"
#define DEBUG_PIN 14
#define CONFIG_PIN 13

#define EST_OFFSET -5
#define CST_OFFSET -6
#define MST_OFFSET -7
#define PST_OFFSET -8

#define DST 1

#define LCD 1
#define LED2COLOR 1

#define NTP_SERVERS "us.pool.ntp.org", "time.nist.gov", "pool.ntp.org"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constants

#ifdef LCD

#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

const int I2C_DISPLAY_ADDRESS = 0x27;

LiquidCrystal_PCF8574 lcd(I2C_DISPLAY_ADDRESS);
#endif

#ifdef LED2COLOR

#define LEDRED 12
#define LEDGRN 16

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Variables

struct dstRule StartRule = {"PDT", Second, Sun, Mar, 2, 3600}; // Eastern Daylight time = UTC/GMT -7 hours
struct dstRule EndRule = {"PST", First, Sun, Nov, 1, 0};       // Eastern Standard time = UTC/GMT -8 hour

bool dbg = true;

bool cfgMode = false;
bool shouldSaveConfig = false;

char mqtt_srvr[40]= "Unknown Server";
char mqtt_port[6] = "22876";

//default custom static IP
char static_ip[16] = "10.0.1.99";
char static_gw[16] = "10.0.1.1";
char static_sn[16] = "255.255.255.0";

String sysName;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Prototypes

void configModeCallback (WiFiManager *_wiFiManager);
int8_t GetWifiQuality();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utility Methods

void BuildHostName(){
  sysName += HOSTNAME;
  sysName += String(ESP.getChipId(), HEX);
}

