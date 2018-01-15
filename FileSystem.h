
void ResetFS(){
  SPIFFS.format();
}

void SaveConfigCallback () {
  shouldSaveConfig = true;
}

void SaveConfig(){
  SendMessage("----- Save Config File -----");
  
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  
  json["mqtt_srvr"] = mqtt_srvr;
  json["mqtt_port"] = mqtt_port;
  json["ip"] = WiFi.localIP().toString();
  json["gateway"] = WiFi.gatewayIP().toString();
  json["subnet"] = WiFi.subnetMask().toString();

  File file = SPIFFS.open("/config.json", "w");
  if (!file) {
    SendMessage("----- File Not Found -----");
    return;
  }

  if(dbg) json.prettyPrintTo(Serial);
  
  json.printTo(file);
  file.close();
}

void LoadConfig(){
  SendMessage("----- Load Config File -----");
  if(SPIFFS.exists("/config.json")){
    File file = SPIFFS.open("/config.json","r");
    if(file){
      size_t size = file.size();
      std::unique_ptr<char[]> buf(new char[size]);
      file.readBytes(buf.get(), size);
      
      DynamicJsonBuffer jsonBuffer;
      JsonObject& json = jsonBuffer.parseObject(buf.get());
      
      if(dbg) json.printTo(Serial);
      
      if (json.success()) {
        strcpy(mqtt_srvr, json["mqtt_srvr"]);
        strcpy(mqtt_port, json["mqtt_port"]);
        strcpy(static_ip, json["ip"]);
        strcpy(static_gw, json["gateway"]);
        strcpy(static_sn, json["subnet"]);
      }
    } else {
      SendMessage("----- Fail To Load File -----");
    }
  } else {
    SendMessage("----- File Not Found -----");
  }
}

void InitFS(){
  SendMessage("----- Mounting FS... -----");
  if (SPIFFS.begin()) LoadConfig();
}

