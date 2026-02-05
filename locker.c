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


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// analog keypad2  /////////////////////////////////////////////


const int analogInPin = 36;  
int ref[]={3720,3152,2752,2428,2127,1836,1535,1262,975,694,410,124};
int sensorValue = 0;  // value read from the pot
int outputValue = 0;  // 

void setup() 
{ 
  Serial.begin(115200);
}

void loop() 
{
  sensorValue = analogRead(analogInPin);
  if(sensorValue>50)
  {
    for(int i=0;i<=12;i++)
    {
      outputValue=20;
      if((sensorValue>(ref[i]-50))&&(sensorValue<(ref[i]+50)))
      {
       outputValue=i;
        Serial.print("sensor = ");
        Serial.print(sensorValue);
        Serial.print("\t output = ");
        Serial.println(outputValue);
      }
    } 
  }
  delay(100);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
