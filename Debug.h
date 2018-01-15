

void InitDebug(){
  Serial.begin(115200);
  Serial.println();
}

void SendMessage(String str){
  if(dbg) Serial.println(str);
}

void SendMessage(IPAddress ip){
  if(dbg) Serial.println(ip);
}

void SendChar(char val){
  if(dbg) Serial.print(val);
}

