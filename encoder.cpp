///////// myEncoder code1  //////////////////////////////////////////////////

#define sw 19 //19  //MISO=19  //25
#define dt 15 //27
#define ck 18 //18 //SCK=18 //33

bool sw_state;
bool last_sw_state;
bool buttonstate;
bool sw_state2;
bool sw_state3;
bool last_sw_state2;
bool buttonstate2;
int change;
unsigned long time1; 
unsigned long time2; 
int rotate=0;
int count=0;

void setup() 
{
  pinMode(sw, INPUT_PULLUP);
  pinMode(dt, INPUT_PULLUP);
  pinMode(ck, INPUT_PULLUP);

  Serial.begin(115200);
  Serial.println("Encoder begin");
  delay(100);
  Serial.print("count:");
  Serial.println(count);
}

void loop() 
{
  rotate=update();

  if(rotate==1)
  {
    Serial.println("sw press");
  }
  
  if(rotate==2)
  { 
    count++;
    Serial.print("count:");
    Serial.println(count);
  } 
  
  if(rotate==3)
  {
    count--; 
    Serial.print("count:");
    Serial.println(count);
  }
}



int update()
{
  change=0;
  
  sw_state=digitalRead(sw);
  if(sw_state!=last_sw_state)
  {
    time1=millis();
  }
  
  if((millis()-time1)>50)
  {
    if(sw_state!=buttonstate)
    {
      buttonstate=sw_state;
      if(buttonstate==HIGH)
      {
        change=1;
        buttonstate=sw_state;
      }
    }
  }
  last_sw_state=sw_state;
  
  
  
  sw_state2=digitalRead(ck);
  if(sw_state2!=last_sw_state2)
  {
    time2=millis();
  }
  
  if((millis()-time2)>1)
  {
    if(sw_state2!=buttonstate2)
    {
      buttonstate2=sw_state2;
      sw_state3=digitalRead(dt);
      if(sw_state2==0&&sw_state3==0) change=3;
      else if(sw_state2==0&&sw_state3==1) change=2;
    }
  }
  last_sw_state2=sw_state2;


  return change;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////// myEncoder_lib.ino ///////////

#include "myEncoder.h"

#define sw 19
#define dt 15
#define ck 18

myEncoder Enc1(dt,ck,sw);

int count=0,oldCount=0;
int rotate=0;
unsigned long delayTime1;

void setup() 
{
  Serial.begin(115200);
  delay(100);
}

void loop() 
{
  rotate=Enc1.update();
  if(rotate==1)
  {
    Serial.println("sw press");
  }
  if(rotate==2) { count++;} 
  if(rotate==3) {count--; }

  if(count!=oldCount)
  {
    Serial.print("count:");
    Serial.println(count);
    oldCount=count;
  }

 if ((millis() - delayTime1) > 500)
 {
  //do something
  delayTime1=millis();
 }
}
 
//////////////////////////////////////////////////////////////////////////////////
///////////////myEncoder.h ////////////////////////////////
/*
 * myEncoder.h
 */
#ifndef MYENCODER_H
#define MYENCODER_H
#include <Arduino.h>

class myEncoder
{
  public:
   myEncoder(byte dt, byte ck,byte sw);
   int update();
  private:
   byte _sw;
   byte _dt;
   byte _ck;
   bool _sw_state;
   bool _last_sw_state;
   bool _buttonstate;
   bool _sw_state2;
   bool _sw_state3;
   bool _last_sw_state2;
   bool _buttonstate2;
   int _change;
   unsigned long _time; 
   unsigned long _time2; 
};

#endif

////////////////////////////////////////////////////////////////////////////
//////////////////////   myEncoder.cpp   ////////////////////////

/*
 * myEncoder.cpp
 */

#include "myEncoder.h"

myEncoder::myEncoder(byte dt,byte ck,byte sw)
{
  pinMode(sw, INPUT_PULLUP);
  pinMode(dt, INPUT_PULLUP);
  pinMode(ck, INPUT_PULLUP);
  _sw = sw;
  _dt = dt;
  _ck = ck;
}

int myEncoder::update()
{
  _change=0;
  
  _sw_state=digitalRead(_sw);
  if(_sw_state!=_last_sw_state)
  {
    _time=millis();
  }
  
  if((millis()-_time)>50)
  {
    if(_sw_state!=_buttonstate)
    {
      _buttonstate=_sw_state;
      if(_buttonstate==HIGH)
      {
        _change=1;
        _buttonstate=_sw_state;
      }
    }
  }
  _last_sw_state=_sw_state;
  
  _sw_state2=digitalRead(_ck);
  if(_sw_state2!=_last_sw_state2)
  {
    _time2=millis();
  }
  
  if((millis()-_time2)>1)
  {
    if(_sw_state2!=_buttonstate2)
    {
      _buttonstate2=_sw_state2;
      _sw_state3=digitalRead(_dt);
      if(_sw_state2==0&&_sw_state3==0) _change=3;
      else if(_sw_state2==0&&_sw_state3==1) _change=2;
      
    }
  }
  _last_sw_state2=_sw_state2;


  return _change;
}
/////////////////////////////////////////////////////////
///////////one direction ////////////////////////////////

// setting PWM properties
const int freq = 100;
const int resolution = 8;

int R1 = 4;
int R2 = 2;
int speed=200;

void setup()
{
  Serial.begin(115200);
  pinMode(R1,OUTPUT);
  pinMode(R2,OUTPUT);
  ledcSetup(0, freq, resolution); //(ledcChannel, freq, resolution)
  ledcAttachPin(R1, 0); //(pin, channel)  
}
 
void loop()
{
    digitalWrite(R2, LOW);
    ledcWrite(0, speed);
    delay(5000);
}


////////////////////////////////////////////////////////////////
/////////////// CW <-> CCW ///////////////////////
// setting PWM properties
const int freq = 100;
const int resolution = 8;

int R1 = 4;
int R2 = 2;
#define PWM_R1 0
#define PWM_R2 1

int speed=200;


void setup()
{
  Serial.begin(115200);
  pinMode(R1,OUTPUT);
  pinMode(R2,OUTPUT);
  
  ledcSetup(PWM_R1, freq, resolution); //(ledChannel, freq, resolution)
  ledcSetup(PWM_R2, freq, resolution); //(ledChannel, freq, resolution)
  
  ledcAttachPin(R1, PWM_R1);
  ledcAttachPin(R2, PWM_R2);
  
}
 
void loop()
{
    ledcWrite(PWM_R2, 0);
    ledcWrite(PWM_R1, speed);
    Serial.println("CW");
    delay(5000);
  
    ledcWrite(PWM_R1, 0);
    ledcWrite(PWM_R2, speed);
    Serial.println("CCW");
    delay(5000);  
}


///////////////////////////////////////////////////////////////
///////// Method1 counts in specific time.ino ///////////

#include "myEncoder.h"

#define sw 19
#define dt 15
#define ck 18
#define dt2 27
#define ck2 33
const int freq = 100;
const int resolution = 8;
int R1 = 4;
int R2 = 2;
#define PWM_R1 0
#define PWM_R2 1

myEncoder Enc1(dt,ck,sw);

int speed=200;
int rotate=0,rotate2=0,count=0;
unsigned long delayTime1;
bool swState=0,lastSwState=0,mode=0,dir=0;

void  pulse()
{
  if(digitalRead(dt2)==1){count++;} else {count--;}
}

void setup() 
{
  Serial.begin(115200);
  delay(100);
  pinMode(R1,OUTPUT);
  pinMode(R2,OUTPUT);
  ledcSetup(PWM_R1, freq, resolution);
  ledcSetup(PWM_R2, freq, resolution);
  ledcAttachPin(R1, PWM_R1);
  ledcAttachPin(R2, PWM_R2);
  
  pinMode(ck2,INPUT_PULLUP);
  pinMode(dt2,INPUT_PULLUP);
  attachInterrupt(ck2, pulse, FALLING);
}



void loop() 
{
  rotate=Enc1.update();
  if(rotate==1)
  {
    Serial.println("sw press");
    mode=!mode;
    if(mode==0)
    {
      ledcWrite(PWM_R1, 0);
      ledcWrite(PWM_R2, 0);
    }else
    {
      drive();
    }
  }
  if(rotate==2) 
  {
    speed=speed+10;
    if(speed>255)speed=255;
    displayData();
    if(mode==1)
    {
      drive();
    }
  } 
  if(rotate==3) 
  {
    speed=speed-10; 
    if(speed<-225)speed=-225;
    displayData();
    if(mode==1)
    {
      drive();
    }
  }

 if ((millis() - delayTime1) > 1000)
 {

  displayData();
  delayTime1=millis();
  count=0;
 }
}
 
void drive()
{
  if(speed>=0)
  {
    ledcWrite(PWM_R1, speed);
    ledcWrite(PWM_R2, 0);
  }else
  {
    ledcWrite(PWM_R1, 0);
    ledcWrite(PWM_R2, speed*-1);
  }
}

void displayData()
{
 
  Serial.print("set:");
  Serial.print(speed);

  Serial.print(" count:");
  Serial.print(count);

  if(mode==0)
  Serial.println(" Off");
  else
  Serial.println(" On");
}

//////////////////////////////////////////////////////////////////////////////
