/*
  AnalogReadSerial
*/
#define Ain 36

void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
  int sensorValue = analogRead(Ain);
  Serial.println(sensorValue);
  delay(100);  
}
