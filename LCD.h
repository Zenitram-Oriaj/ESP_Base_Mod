
void ResetLCD(){
  lcd.noBlink();
  lcd.noCursor();
  lcd.home(); 
  lcd.clear();
}

void SetLcdBacklight(bool en){
  if(en) lcd.setBacklight(255);
  else lcd.setBacklight(0);
}

void LcdMessage(String msg, int line, int pos){
  lcd.setCursor(pos, line);
  lcd.print(msg);
}

void InitLCD(){
  Wire.begin(SDA,SCL);
  Wire.beginTransmission(0x27);

  int error = Wire.endTransmission();

  if (error == 0) {
    SendMessage(": LCD found.");
    lcd.begin(16, 2);
  } else {
    SendMessage(": LCD not found.");
  }
}

