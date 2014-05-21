void setup() {
  Serial.begin(9600);
}

void loop() {}

void serialEvent() {
  String dataString="";
  if(Serial.available() > 0)
    dataString=Serial.readStringUntil(';');
  if(dataString.startsWith("pinMode")){
    dataString=dataString.substring(dataString.indexOf("(")+1,dataString.length());
    int pin=dataString.toInt();
    dataString=dataString.substring(dataString.indexOf(",")+1,dataString.indexOf(")"));
    if(dataString=="INPUT" || dataString=="0") pinMode(pin,INPUT);
    else if(dataString=="OUTPUT" || dataString=="1") pinMode(pin,OUTPUT);
    else if(dataString=="INPUT_PULLPU" || dataString=="2") pinMode(pin,INPUT_PULLUP);
    else Serial.write("wrong mode\n");
  }
  else if(dataString.startsWith("digitalWrite")){
    dataString=dataString.substring(dataString.indexOf("(")+1,dataString.indexOf(")"));
    int pin=dataString.toInt();
    dataString=dataString.substring(dataString.indexOf(",")+1,dataString.indexOf(")"));
    if(dataString=="HIGH" || dataString=="1") digitalWrite(pin,HIGH);
    else if(dataString=="LOW" || dataString=="0") digitalWrite(pin,LOW);
    else Serial.write("wrong mode\n");
  }
  else if(dataString.startsWith("digitalRead")){
    dataString=dataString.substring(dataString.indexOf("(")+1,dataString.indexOf(")"));
    int pin=dataString.toInt();
    Serial.println(digitalRead(pin));
  }
  else if(dataString.startsWith("analogRead")){
    if(dataString.indexOf('A')<0){
      dataString=dataString.substring(dataString.indexOf("(")+1,dataString.indexOf(")"));
      int pin=dataString.toInt();
      Serial.println(analogRead(pin));
    }
    else{
      dataString=dataString.substring(dataString.indexOf("A")+1,dataString.indexOf(")"));
      int pin=dataString.toInt()+54;
      Serial.println(analogRead(pin));
    }
  }
  else if(dataString.startsWith("analogWrite")){
    dataString=dataString.substring(dataString.indexOf("(")+1,dataString.length());
    int pin=dataString.toInt();
    dataString=dataString.substring(dataString.indexOf(",")+1,dataString.indexOf(")"));
    int value=dataString.toInt();
    analogWrite(pin,value);
  }
  else Serial.write("wrong input\n");
}
