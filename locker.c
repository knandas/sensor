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
///////////////////////////// analog keypad3  /////////////////////////////////////////////

//esp32_analogsw3B.ino
const int analogInPin = 36;  
int ref[]={3720,3152,2752,2428,2127,1836,1535,1262,975,694,410,124};

unsigned long lastRead=0;
int key,oldKey;

void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
  key=readSW();
  if(key!=20&&key!=oldKey)
  {
    Serial.print("\t output = ");
    Serial.println(key);
    oldKey=key;
    lastRead=millis();
  }
  if(millis()-lastRead>300)
  {
    oldKey=20;
    lastRead=millis();
  }
  delay(50);
}


byte readSW()
{
  int outputValue=20;
  int sensorValue = analogRead(analogInPin);
  //Serial.println(sensorValue);
  
  if(sensorValue>50)
  {
    for(int i=0;i<=12;i++)
    {
      if((sensorValue>(ref[i]-50))&&(sensorValue<(ref[i]+50)))
      {
       outputValue=i;
      }
    } 
  }
 return outputValue;
}

/////////////////////////////////////////////////////////////////////////////////


//esp32_analogsw4B.ino

#define led1 4
#define led2 2
#define led3 13
#define led4 12
const int analogInPin = 36;  
int ref[]={3720,3152,2752,2428,2127,1836,1535,1262,975,694,410,124};

int key,oldKey;
unsigned long lastRead=0;
unsigned long lastCount=0;
int count=0;
int pass[]={30,30,30,30};

void setup() 
{
  Serial.begin(115200);
  pinMode(led1,OUTPUT);pinMode(led2,OUTPUT);pinMode(led3,OUTPUT);pinMode(led4,OUTPUT);
}

void loop() 
{
  key=readSW();
  if(key!=20&&key!=oldKey)
  {
    Serial.print("key in= "); Serial.println(key);
    oldKey=key;
    lastRead=millis();
    if(count==0)
    {
      pass[0]=key;
      lastCount=millis();
      digitalWrite(led1,HIGH);
      count++;
    }else   if(count==1)
    {
      pass[1]=key;
      lastCount=millis();
      digitalWrite(led2,HIGH);
      count++;
    }else   if(count==2)
    {
      pass[2]=key;
      lastCount=millis();
      digitalWrite(led3,HIGH);
      count++;
    }else   if(count==3)
    {
      pass[3]=key;
      lastCount=millis();
      digitalWrite(led4,HIGH);
      count=0;
      Serial.printf("pass:%d,%d,%d,%d \n",pass[0],pass[1],pass[2],pass[3]);
      blink();
    }
  }

  if(millis()-lastRead>200)
  {
    oldKey=20;
    lastRead=millis();
  }

  if(millis()-lastCount>5000)
  {
    pass[]={30,30,30,30};
    count=0;
    digitalWrite(led1,LOW); digitalWrite(led2,LOW); digitalWrite(led3,LOW); digitalWrite(led4,LOW);
    lastCount=millis();
  }
  delay(50);
}




byte readSW()
{
  int outputValue=20;
  int sensorValue = analogRead(analogInPin);
  //Serial.println(sensorValue);
  
  if(sensorValue>50)
  {
    for(int i=0;i<=12;i++)
    {
      if((sensorValue>(ref[i]-50))&&(sensorValue<(ref[i]+50)))
      {
       outputValue=i;
      }
    } 
  }
 return outputValue;
}

void blink()
{
    delay(100);
    digitalWrite(led1,LOW);digitalWrite(led2,LOW);digitalWrite(led3,LOW);digitalWrite(led4,LOW);
    delay(100);
    digitalWrite(led1,HIGH);digitalWrite(led2,HIGH);digitalWrite(led3,HIGH);digitalWrite(led4,HIGH);
    delay(100);
    digitalWrite(led1,LOW);digitalWrite(led2,LOW);digitalWrite(led3,LOW);digitalWrite(led4,LOW);
    delay(100);
    digitalWrite(led1,HIGH);digitalWrite(led2,HIGH);digitalWrite(led3,HIGH);digitalWrite(led4,HIGH);
    delay(100);
    digitalWrite(led1,LOW);digitalWrite(led2,LOW);digitalWrite(led3,LOW);digitalWrite(led4,LOW);
    delay(100);
    digitalWrite(led1,HIGH);digitalWrite(led2,HIGH);digitalWrite(led3,HIGH);digitalWrite(led4,HIGH);
    delay(100);
    digitalWrite(led1,LOW);digitalWrite(led2,LOW);digitalWrite(led3,LOW);digitalWrite(led4,LOW);
}


















