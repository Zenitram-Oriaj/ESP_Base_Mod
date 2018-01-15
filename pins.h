

void UpdateVarsFromPins(){
  dbg = digitalRead(DEBUG_PIN);
  cfgMode = digitalRead(CONFIG_PIN);
}

void InitPins(){
  pinMode(DEBUG_PIN, INPUT);
  pinMode(CONFIG_PIN, INPUT);
  UpdateVarsFromPins();
}


