
void drawOtaProgress(unsigned int _progress, unsigned int _total) {
  SendChar('*');
}

void InitOTA(){
  SendMessage("----- Enabling OTA -- Hostname: " + sysName + " -----");
  ArduinoOTA.setHostname((const char *)sysName.c_str());
  ArduinoOTA.onProgress(drawOtaProgress);
  ArduinoOTA.begin();
}

