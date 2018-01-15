
void ResetWifiManager(WiFiManager *_wifiManager){
  _wifiManager->resetSettings();
}

int8_t GetWifiQuality() {
  int32_t dbm = WiFi.RSSI();
  if(dbm <= -100) {
      return 0;
  } else if(dbm >= -50) {
      return 100;
  } else {
      return 2 * (dbm + 100);
  }
}


void ConfigModeCallback (WiFiManager *_wifiManager) {
  SendMessage("Entered config mode");
  SendMessage(WiFi.softAPIP());
  SendMessage(_wifiManager->getConfigPortalSSID());
}

bool CheckWifiStatus(){
  int cnt = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    SendChar('.');
    cnt++;
    if(cnt >= 20) return false;
  }
  return true;
}

void InitWifi(){
  WiFi.hostname(sysName);
}

void SetWifiToClient(){
  // Manual Wifi
  WiFi.begin("", "");
}

void SetWifiToAP(WiFiManager *_wifiManager){
  _wifiManager->setSaveConfigCallback(SaveConfigCallback);
  _wifiManager->setAPCallback(ConfigModeCallback);
  _wifiManager->autoConnect();
  InitWifi();
}

void SetIpToStatic(WiFiManager *_wifiManager){
  IPAddress _ip,_gw,_sn;
  
  _ip.fromString(static_ip);
  _gw.fromString(static_gw);
  _sn.fromString(static_sn);

  _wifiManager->setSTAStaticIPConfig(_ip, _gw, _sn);
}

void SetAdditionalParams(WiFiManager *_wifiManager){
  WiFiManagerParameter _mqtt_srvr("server", "mqtt server", mqtt_srvr, 40);
  WiFiManagerParameter _mqtt_port("port", "mqtt port", mqtt_port, 5);

  _wifiManager->addParameter(&_mqtt_srvr);
  _wifiManager->addParameter(&_mqtt_port);

  strcpy(mqtt_srvr, _mqtt_srvr.getValue());
  strcpy(mqtt_port, _mqtt_port.getValue());
}

void InitWifiManager(){
  WiFiManager wifiManager;

  if(dbg) wifiManager.setDebugOutput(true);
  else wifiManager.setDebugOutput(false);
  
  
  //SetAdditionalParams(&wifiManager);
  //wifiManager.setMinimumSignalQuality();
  SetWifiToAP(&wifiManager);
}

