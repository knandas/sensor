/*
 * ESP32 ledc Servo Example1
*/
#define TIMER_WIDTH 16
#define servoPin1 25 //servo PWM pin 25
#define servo1 1   //timer ch1  (0-15)
#define freq 50 

unsigned int COUNT_LOW=1638;
unsigned int COUNT_HIGH=7864;

void setup() 
{
  ledcSetup(servo1, freq, TIMER_WIDTH); // channel 1, 50 Hz, 16-bit width
  ledcAttachPin(servoPin1, servo1);   // GPIO 25 assigned to channel 1
  Serial.begin(115200);
}

void loop() 
{
  for (int i=COUNT_LOW ; i < COUNT_HIGH ; i=i+10)
  {
    ledcWrite(servo1, i);       // sweep servo 1
    Serial.printf("i=%d \n",i);
    delay(20);
  }

  for (int i=COUNT_HIGH ; i > COUNT_LOW  ; i=i-10)
  {
    ledcWrite(servo1, i);       // sweep servo 1
    Serial.printf("i=%d \n",i);
    delay(20);
  }
}



/*
* %B    - binary (d = 0b1000001)
 * %b    - binary (d = 1000001)  
 * %c    - character (s = H)
 * %d/%i - integer (d = 65)\
 * %f    - float (f = 123.45)
 * %3f   - float (f = 123.346) three decimal places specified by %3.
 * %o    - boolean on/off (d = On)
 * %s    - char* string (s = Hello)
 * %X    - hexidecimal (d = 0x41)
 * %x    - hexidecimal (d = 41)
 * %%    - escaped percent ("%")
 */


///////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

/*
 * ESP32 ledc Servo Example3 serialeven
*/
#define TIMER_WIDTH 16
#define servoPin1 25 //servo PWM pin 25
#define servo1 1   //timer ch1  (0-15)
#define freq 50 
#define Ain 36
int VR;
int pos,count;
unsigned int COUNT_LOW=1638;
unsigned int COUNT_HIGH=7864;

void setup() 
{
  ledcSetup(servo1, freq, TIMER_WIDTH); // channel 1, 50 Hz, 16-bit width
  ledcAttachPin(servoPin1, servo1);   // GPIO 25 assigned to channel 1
  Serial.begin(115200);
}

void loop() 
{
  VR=analogRead(Ain);
  pos=map(VR,0,4095,0,180);
  count=map(VR,0,4095,COUNT_LOW,COUNT_HIGH);
  ledcWrite(servo1, count);       // sweep servo 1
  Serial.printf("position=%d count=%d \n",pos,count);
  delay(20);  
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

/*
 * ESP32 ledc Servo Example3 serialevent + moveServo function
*/
#define TIMER_WIDTH 16
#define servoPin1 25 //servo PWM pin 25
#define servo1 1   //timer ch1  (0-15)
#define freq 50 
#define Ain 36
int VR;
int deg1,setcount1;
unsigned int COUNT_LOW=1638;
unsigned int COUNT_HIGH=7864;
String inputString = "";

void serialEvent() 
{
 while (Serial.available()) 
  {
    char inChar = Serial.read();
    if(isDigit(inChar))
    {
     inputString += (char)inChar;
    }
    if (inChar == '\n') 
    {
     deg1=inputString.toInt();
     setcount1=map(deg1,0,180,COUNT_LOW,COUNT_HIGH);
     Serial.printf("set pos1: %d \n",deg1);
     inputString = "";
    }
  } 
  ledcWrite(servo1,setcount1);    // move servo 1
}

void setup() 
{
  ledcSetup(servo1, freq, TIMER_WIDTH); // channel 1, 50 Hz, 16-bit width
  ledcAttachPin(servoPin1, servo1);   // GPIO 25 assigned to channel 1
  Serial.begin(115200);
  inputString.reserve(10);
  Serial.println("Start");
}

void loop() 
{
  delay(20);  
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * ESP32 ledc Servo Example3 serialevent + moveServo function
*/
#define TIMER_WIDTH 16
#define servoPin1 25 //servo PWM pin 25
#define servo1 1   //timer ch1  (0-15)
#define freq 50 

unsigned int COUNT_LOW=1638;
unsigned int COUNT_HIGH=7864;
int servoDelay1 = 200;
unsigned long lastMicros1=0;
int deg1,setcount1=COUNT_LOW,count1=COUNT_LOW+1;
String inputString = "";

void serialEvent() 
{
 while (Serial.available()) 
  {
    char inChar = Serial.read();
    if(isDigit(inChar))
    {
     inputString += (char)inChar;
    }
    if (inChar == '\n') 
    {
     deg1=inputString.toInt();
     setcount1=map(deg1,0,180,COUNT_LOW,COUNT_HIGH);
     Serial.printf("set pos1: %d \n",deg1);
     inputString = "";
    }
  } 
}

void setup() 
{
  ledcSetup(servo1, freq, TIMER_WIDTH); // channel 1, 50 Hz, 16-bit width
  ledcAttachPin(servoPin1, servo1);   // GPIO 25 assigned to channel 1
  Serial.begin(115200);
  inputString.reserve(10);
  Serial.println("Start");
}

void loop() 
{
  moveServo();
}

void moveServo()
{
  if(micros()-lastMicros1>=servoDelay1)
  {
    if(count1>setcount1&&count1>=COUNT_LOW)
    {
      count1--;
      ledcWrite(servo1, count1);
      lastMicros1=micros();
    }

    if(count1<setcount1&&count1<=COUNT_HIGH)
    {
      count1++;
      ledcWrite(servo1, count1);
      lastMicros1=micros();
    }
  }  
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * ESP32 ledc Servo Example5 serialevent + myServo lib
*/

#include "myServo.h"

#define servoPin1 25 //servo PWM pin 25
#define ch1 1   //timer ch1  (0-15)
unsigned int COUNT_LOW=1638;
unsigned int COUNT_HIGH=7864;
int maxDeg=180;
int deg1=90;

myServo servoA(ch1,servoPin1,COUNT_LOW,COUNT_HIGH,maxDeg);

String inputString = "";
bool stringComplete = false; 

void serialEvent() 
{
 while (Serial.available()) 
  {
    char inChar = Serial.read();
    if(isDigit(inChar))
    {
     inputString += (char)inChar;
    }
    if (inChar == '\n') 
    {
      stringComplete = true;
    }
  } 
}

void setup() 
{
  Serial.begin(115200);
  inputString.reserve(10);
  Serial.println("Start");
}

void loop() 
{
  if (stringComplete==true) 
  {
    deg1=inputString.toInt();
    Serial.printf("set pos1: %d \n",deg1);
    inputString = "";
    stringComplete = false;
  }
  servoA.moveServo(deg1);  //0-180;
}




////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// myServo.h //////////////////////////////////////////////
/*
 myServo.h by k^_^ nandhasri.k@gmail.com
*/

#ifndef MYSERVO_H
#define MYSERVO_H
#include <Arduino.h>

class myServo
{
  public:
   myServo(byte ch, byte pin,int COUNT_LOW,int COUNT_HIGH,int maxDeg);
   myServo(byte ch, byte pin);
   void moveServo(int setcount);
   void setServo(int time);
  private:
   byte _ch;
   byte _pin;
   int _setcount;
   int _COUNT_LOW;
   int _COUNT_HIGH;
   unsigned long _lastMicros=0;
   int _deg;
   int _maxDeg;
   int _count;
   int _servoDelay;
};

#endif

///////////////////////////////////////////////////////////////////////////////////
/////////////////////////  myServo.cpp  ////////////////////////////////////////
/*
 myServo.h by k^_^ nandhasri.k@gmail.com
*/

#include "myServo.h"

myServo::myServo(byte ch, byte pin,int COUNT_LOW,int COUNT_HIGH,int maxDeg)
{
  _ch=ch;
  _pin=pin;
  _COUNT_LOW=COUNT_LOW;
  _COUNT_HIGH=COUNT_HIGH;
  _maxDeg=maxDeg;
  _servoDelay=200;
  _setcount=_COUNT_HIGH-(_COUNT_LOW/2);
  _count=(_COUNT_HIGH-(_COUNT_LOW/2))+1;
  ledcSetup(_ch, 50, 16); // channel , 50 Hz, 16-bit width
  ledcAttachPin(_pin, _ch);  
}

myServo::myServo(byte ch, byte pin)
{
  _ch=ch;
  _pin=pin;
  _COUNT_LOW=1638;
  _COUNT_HIGH=7864;
  _servoDelay=200;
  _maxDeg=180;
  _setcount=_COUNT_HIGH-(_COUNT_LOW/2);
  _count=(_COUNT_HIGH-(_COUNT_LOW/2))+1;
  ledcSetup(_ch, 50, 16); // channel , 50 Hz, 16-bit width
  ledcAttachPin(_pin, _ch);  
}

void myServo::setServo(int time)
{
  _servoDelay=time;
}

void myServo::moveServo(int _deg)
{
  _setcount=map(_deg,0,_maxDeg,_COUNT_LOW,_COUNT_HIGH);
  if(micros()-_lastMicros>=_servoDelay)
  {
    if(_count>_setcount&&_count>=_COUNT_LOW)
    {
      _count--;
      ledcWrite(_ch, _count);
      _lastMicros=micros();
    }

    if(_count<_setcount&&_count<=_COUNT_HIGH)
    {
      _count++;
      ledcWrite(_ch, _count);
      _lastMicros=micros();
    }
  }  
}

//////////////////////////////////////////////////////////////////////////////////////




