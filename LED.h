void InitLEDs(){
  pinMode(LEDRED, OUTPUT);
  pinMode(LEDGRN, OUTPUT);
}

void SetLED(int led, bool state){
  if(state) digitalWrite(led,HIGH);
  else digitalWrite(led,LOW);
}

