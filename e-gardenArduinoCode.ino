#define valve 13
#define heat 21
#define light 22

int moisture1;
int moisture2;
int moisture3;

void setup() {
  Serial.begin(9600);
  pinMode(heat, OUTPUT); digitalWrite(heat, HIGH);
  pinMode(valve, OUTPUT); digitalWrite(valve, HIGH);
  pinMode(light, OUTPUT); digitalWrite(light, HIGH);
}

void loop() {
  moisture1=analogRead(A0);
  moisture2=analogRead(A1);
  moisture3=analogRead(A2);
}

void serialEvent(){
  String dataString="";
  while(Serial.available()>0){
    dataString=Serial.readStringUntil(';');
    if(dataString.startsWith("get")) getData();
    else if(dataString.startsWith("heatON")) digitalWrite(heat,LOW);
    else if(dataString.startsWith("heatOFF")) digitalWrite(heat,HIGH);
    else if(dataString.startsWith("lightON")) digitalWrite(light,LOW);
    else if(dataString.startsWith("lightOFF")) digitalWrite(light,HIGH);
    else if(dataString.startsWith("valve:")){
      dataString = dataString.substring(dataString.indexOf(":")+1,dataString.length());
      digitalWrite(valve,LOW);
      delay(dataString.toInt());
      digitalWrite(valve,HIGH);
    }
    else Serial.write("WRONG COMAND!\nFUCKER!!!\n");
  }
}

void getData(){
 // delay(50);
  Serial.write("m1:");Serial.print(moisture1);Serial.write("\n");
  Serial.write("m2:");Serial.print(moisture2);Serial.write("\n");
  Serial.write("m3:");Serial.print(moisture3);Serial.write("\n");
}
