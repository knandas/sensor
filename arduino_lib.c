arduino lib


///////////////////////////dump code/////////////////////////////////////////////////
int Led1=13;
int Led2=12;
//#define Led1 13
//#define Led2 12
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(Led1, OUTPUT);
  pinMode(Led1, OUTPUT);
}

// the loop function runs over and over again forever
void loop() 
{
  digitalWrite(Led1, HIGH);   
  delay(200);                       
  digitalWrite(Led1, LOW);    
  delay(1000);  

  digitalWrite(Led2, HIGH);   
  delay(100);                       
  digitalWrite(Led2, LOW);    
  delay(1000);   
                      
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////millis blink //////////////////////////////////////

const int Led1=13;
const int Led2=12;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
}

// the loop function runs over and over again forever
void loop() 
{
  blinkLed1();
  blinkLed2();                      
}

void blinkLed1()
{
  static unsigned long Led1Millis = millis();
  if (millis() - Led1Millis>100)
  {
    digitalWrite(Led1, !digitalRead(Led1));
    Led1Millis = millis();
  }
}

void blinkLed2()
{
  static unsigned long Led2Millis = millis();
  if (millis() - Led2Millis>2000)
  {
    digitalWrite(Led2, !digitalRead(Led2));
    Led2Millis = millis();
  }
}

///////////////////////////////////////////////////////////////////////////////////////
////////////millis blink varaible //////////////////////////////

const int Led1=13;
const int Led2=12;
unsigned int time1=100;
unsigned int time2=2000;
static unsigned long Led1Millis = millis();
static unsigned long Led2Millis = millis();

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
}

void loop() 
{
 blinkLed1(time1);
 blinkLed2(time2);
}

void blinkLed1(unsigned int T1)
{
  
  if (millis() - Led1Millis>T1)
  {
    digitalWrite(Led1, !digitalRead(Led1));
    Led1Millis = millis();
  }
}

void blinkLed2(unsigned int T2)
{
  
  if ((millis() - Led2Millis>T2))
  {
    digitalWrite(Led2, !digitalRead(Led2));
    Led2Millis = millis();
  }
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////myBlink4.ino////////////////////////////////////////
/*
 * myblink4
 */
#include "myBlink.h"

int Led1=13;
int Led2=12;
unsigned int time1=100;
unsigned int time2=2000;
unsigned long Led1Millis=millis();
unsigned long Led2Millis=millis();


void setup() 
{
 pinMode(Led1, OUTPUT);
 pinMode(Led2, OUTPUT);
}

void loop() 
{
 blinkLed1(time1);
 blinkLed2(time2);
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////myBlink4.h////////////////////////////////////////


//myBlink4.h
#ifndef MYBLINK_H
#define MYBLINK_H
#include <Arduino.h>


void blinkLed1(unsigned int T1);
void blinkLed2(unsigned int T2);

#endif


//////////////////////////////////////////////////////////////////////////////////
//////////////////myBlink4.cpp////////////////////////////////////////



#include "myBlink.h"

extern int Led1;
extern int Led2;
extern unsigned long Led1Millis;
extern unsigned long Led2Millis;

void blinkLed1(unsigned int T1)
{
  if (millis() - Led1Millis>T1)
  {
    digitalWrite(Led1, !digitalRead(Led1));
    Led1Millis = millis();
  }
}

void blinkLed2(unsigned int T2)
{
  if ((millis() - Led2Millis>T2))
  {
    digitalWrite(Led2, !digitalRead(Led2));
    Led2Millis = millis();
  }
}

///////////////////////////////////////////////////////////////////////////
///////////////////esp32_myBlink2.ino ////////////////////////////////////

/*blink millis*/
#include "myBlink.h"

myBlink led1(4);
myBlink led2(2);
myBlink led3(13);

unsigned int time1=100;
unsigned int time2=2000;
unsigned int time3=500;


void setup() 
{                
 
}

void loop() 
{
 led1.blinkLed(time1);
 led2.blinkLed(time2);
 led3.blinkLed(time3);
}

///////////////////////////////////////////////////////////////////////////
/////////////////// myBlink.h ////////////////////////////////////

//esp32_myBlink2
//myBlink.h

#ifndef MYBLINK_H
#define MYBLINK_H
#include <Arduino.h>

class myBlink
{
  public:
   myBlink(byte pin);
   void blinkLed(unsigned int Time);
  private:
   byte _pin;
   unsigned int _Time;
   unsigned int _LedMillis;
};

#endif 

///////////////////////////////////////////////////////////////////////////
/////////////////// myBlink.cpp ////////////////////////////////////


#include "myBlink.h"

//extern int led1;
//extern int led2;
//extern unsigned long Led1Millis;
//extern unsigned long Led2Millis;

myBlink::myBlink(byte pin)
{
   pinMode(pin, OUTPUT); 
   _pin=pin;
   _LedMillis=millis();

}

void myBlink::blinkLed(unsigned int Time)
{
  if(millis()-_LedMillis>Time)
  {
    digitalWrite(_pin, !digitalRead(_pin));
    _LedMillis=millis();
  }
}

////////////////////////////////////////////////////////////////////////
/////////////////esp32_myBlink4.ino ////////////////////////////////////
/*blink millis*/
#include "myBlink.h"

myBlink led1(4);
myBlink led2(2);

unsigned int time1=100;
unsigned int time2=4000;


void setup() 
{                
 
}

void loop() 
{
 led1.blinkLed(time1);
 led2.blinkLed(50,4000);
}

////////////////////////////////////////////////////////////////////////
/////////////////myBlink.h ////////////////////////////////////

//esp32_myBlink2

#ifndef MYBLINK_H
#define MYBLINK_H
#include <Arduino.h>

class myBlink
{
  public:
   myBlink(byte pin);
   void blinkLed(unsigned int Time);
   void blinkLed(unsigned int Time,unsigned int Time2);
  private:
   byte _pin;
   unsigned int _Time;
   unsigned int _Time2;
   unsigned int _LedMillis;
};

#endif 

/////////////////////////////////////////////////////////////////////////////
/////////////////myBlink.cpp ////////////////////////////////////

#include "myBlink.h"

myBlink::myBlink(byte pin)
{
   pinMode(pin, OUTPUT); 
   _pin=pin;
   _LedMillis=millis();

}

void myBlink::blinkLed(unsigned int Time)
{
  if(millis()-_LedMillis>Time)
  {
    digitalWrite(_pin, !digitalRead(_pin));
    _LedMillis=millis();
  }
}

void myBlink::blinkLed(unsigned int Time,unsigned int Time2)
{
  if(digitalRead(_pin)==HIGH)
  {
   if(millis()-_LedMillis>Time)
   {
    digitalWrite(_pin, LOW);
    _LedMillis=millis();
   }
  } 
  else
  {
       if(millis()-_LedMillis>Time2)
   {
    digitalWrite(_pin, HIGH);
    _LedMillis=millis();
   }
  }
}

///////////////////////////////////////////////////////////////////////////////

https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

//////////////////////////////////////////////////////////////////////////////////////////////
///////////////// wirescan.ino ////////////////////////////////////////////////

#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin();
}

void loop() {
  byte error, address;
  int nDevices = 0;

  delay(5000);

  Serial.println("Scanning for I2C devices ...");
  for(address = 0x01; address < 0x7f; address++){
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0){
      Serial.printf("I2C device found at address 0x%02X\n", address);
      nDevices++;
    } else if(error != 2){
      Serial.printf("Error %d at address 0x%02X\n", error, address);
    }
  }
  if (nDevices == 0){
    Serial.println("No I2C devices found");
  }
}




////////////////////////////////////////////////////////////////////////////////////////
////////////myAt24C32.ino ////////////////////////////////////////////////////

#include <Wire.h>
#define EEPROM_address 0x50  //0x57

int address=70;
byte Value=99;
byte readOut;

void setup() 
{
  Wire.begin();
  Serial.begin(115200);
  Wire.beginTransmission(EEPROM_address);
  Wire.write(address>>8);
  Wire.write(address&0x00FF);
  Wire.write(Value);
  Wire.endTransmission();
  delay(10);
}

void loop() 
{
  
  Wire.beginTransmission(EEPROM_address);
  Wire.write(address>>8);
  Wire.write(address&0x00FF);
  Wire.endTransmission();
  
  Wire.requestFrom(EEPROM_address, 1);
  readOut = Wire.read();
  Serial.println(readOut);
  delay(2000);
}

////////////////////////////////////////////////////////////////////////////
////////////myAt24C32_2.ino ////////////////////////////////////////////////////

#include <Wire.h>
#define EEPROM_address 0x50  //0x57

int address=00;
int pageSize=30;
byte Value=0;
byte readOut;

void setup() 
{
  Wire.begin();
  Serial.begin(115200);
  Wire.beginTransmission(EEPROM_address);
  Wire.write(address>>8);
  Wire.write(address&0x00FF);
  for(int i=0;i<pageSize;i++)
  {
   Wire.write(Value);
   Value++;
  } 
  Wire.endTransmission();
  delay(10);
}

void loop() 
{
  address=0;
  Serial.println("");
  Serial.println("dump data:");
  Wire.beginTransmission(EEPROM_address);
  Wire.write(address>>8);
  Wire.write(address&0x00FF);
  Wire.endTransmission();

  Wire.requestFrom(EEPROM_address, pageSize);
  for(int i=0;i<pageSize;i++)
  {
   readOut = Wire.read();
   if(i%16==0&&i!=0)  Serial.println("");
   Serial.print(readOut);  
   Serial.print("\t");
   
  }
  delay(10000);
}


////////////////////////////////////////////////////////////////////////
////////////myAt24C32_3.ino //////////////////////////////////////////////////

#include "myAT24C32.h"
#define EEPROM_address 0x50
uint16_t pageSize=30;
uint8_t readOut;
uint8_t Value=0;

myAT24C32 mem(EEPROM_address);

void setup() 
{
  Serial.begin(115200);
  Serial.println("");
  //Serial.println("start mem clear");
  //mem.clear(0xFE);
  //Serial.println("");
  //Serial.println("mem cleared!");
  
  for(uint16_t i=0;i<pageSize;i++)
  {
   mem.write(i,Value);
   Value++;
  }
}

void loop() 
{
  Serial.println("");
  Serial.println("dump data:");
  for(uint16_t i=0;i<pageSize;i++)
  {
   readOut= mem.read(i);
   if(i%16==0&&i!=0)  Serial.println("");
   Serial.print(readOut);  
   Serial.print("\t");
  }
  delay(10000);
}

////////////////////////////////////////////////////////////////////////
////////////myAT24C32.h //////////////////////////////////////////////////


/* 
 * File:   myAT24C32.h
 * Author: nandhasri.k@gmail.com
 */

#ifndef myAT24C32_H
#define myAT24C32_H

#include <Arduino.h>
class myAT24C32 
{
 public:
  myAT24C32(uint8_t i2c_address);
  uint8_t read(uint16_t  address);
  void write(uint16_t address, uint8_t value);
  void clear(uint8_t value);
 private:
  uint16_t  _address;
  uint8_t _value;
  uint8_t _i2c_address;

};
#endif

////////////////////////////////////////////////////////////////////////
////////////myRTC.ino //////////////////////////////////////////////////

#include "myDS1307.h"
myDS1307 myRTC;
byte OldSec=0;
bool h12,PM_time;
void setup()
{
  Serial.begin(115200);
  //setRTC();
}
void loop() 
{
  byte Sec = myRTC.getSecond(); 
  byte Min = myRTC.getMinute(); 
  byte Hr = myRTC.getHour(h12,PM_time); 
  byte DW = myRTC.getDoW(); 
  byte Date = myRTC.getDate(); 
  byte Mo = myRTC.getMonth();
  byte Yr = myRTC.getYear();
  if(OldSec!=Sec)
  {
   Serial.print((String)Date+"/"+(String)Mo+"/"+(String)Yr+"\t"+(String)Hr+":");
   if(Min<10) Serial.print("0");
   Serial.print((String)Min+":");
   if(Sec<10) Serial.print("0");
   Serial.println(Sec);
   OldSec=Sec; 
  }
}
void setRTC ()
{
   myRTC.setClockMode(0); 
   myRTC.setSecond(00); 
   myRTC.setMinute(51); 
   myRTC.setHour(19);
   myRTC.setDoW(1); 
   myRTC.setDate(27); 
   myRTC.setMonth(3); 
   myRTC.setYear(23);
}

//////////////////////////////////////////////////////////////////////////
////////////myDS1307.h //////////////////////////////////////////////////

#ifndef MYDS1307_h
#define MYDS1307_h
#include <Arduino.h>
class myDS1307 
{
  public:
   myDS1307();  
   
   //read
   byte getSecond(); 
   byte getMinute(); 
   byte getHour(bool& h12, bool& PM_time); 
   byte getDoW(); 
   byte getDate(); 
   byte getMonth();
   byte getYear();
   
  
   //write
   void setSecond(byte Second); 
   void setMinute(byte Minute); 
   void setHour(byte Hour);
   void setDoW(byte DoW); 
   void setDate(byte Date); 
   void setMonth(byte Month); 
   void setYear(byte Year);
   void setClockMode(bool h12); 

  private:
    byte decToBcd(byte val); 
    byte bcdToDec(byte val); 
    byte readControlByte(bool which); 
      // Read selected control byte:(0)reads 0x0e,(1)reads 0x0f
    void writeControlByte(byte control, bool which); 
     // which == false -> 0x0e, true->0x0f.
};
#endif


//////////////////////////////////////////////////////////////////////////
////////////myDS1307.cpp //////////////////////////////////////////////////

/*
 * nandhasri.k@gmail.com myDS1307.cpp
 */
#include "myDS1307.h"
#include <Arduino.h>
#include <Wire.h>
#define DS1307_ADDRESS 0x68   // DS1307

myDS1307::myDS1307()
{
  Wire.begin();
}

byte myDS1307::getSecond() 
{
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0x00);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 1);
  return bcdToDec(Wire.read());
}

byte myDS1307::getMinute() 
{
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0x01);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 1);
  return bcdToDec(Wire.read());
}

byte myDS1307::getHour(bool& h12, bool& PM_time) 
{
  byte temp_buffer;
  byte hour;
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0x02);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 1);
  temp_buffer = Wire.read();
  h12 = temp_buffer & 0b01000000;
  if (h12) {
    PM_time = temp_buffer & 0b00100000;
    hour = bcdToDec(temp_buffer & 0b00011111);
  } else {
    hour = bcdToDec(temp_buffer & 0b00111111);
  }
  return hour;
}

byte myDS1307::getDoW() 
{
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0x03);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 1);
  return bcdToDec(Wire.read());
}

byte myDS1307::getDate() 
{
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0x04);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 1);
  return bcdToDec(Wire.read());
}

byte myDS1307::getMonth() 
{
  byte temp_buffer;
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0x05);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 1);
  temp_buffer = Wire.read();
  return (bcdToDec(temp_buffer & 0b00011111)) ;
}

byte myDS1307::getYear() 
{
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0x06);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 1);
  return bcdToDec(Wire.read());
}

void myDS1307::setSecond(byte Second) 
{
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0x00);
  Wire.write(decToBcd(Second));  
  Wire.endTransmission();
  byte temp_buffer = readControlByte(1);//ClearOSF 
  writeControlByte((temp_buffer & 0b01111111), 1);
}

void myDS1307::setMinute(byte Minute) 
{
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0x01);
  Wire.write(decToBcd(Minute));  
  Wire.endTransmission();
}


void myDS1307::setHour(byte Hour) 
{
  // The hour must be in 24h format.
  bool h12;
  byte temp_hour;
  // Start by figuring out what the 12/24 mode is
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0x02);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 1);
  h12 = (Wire.read() & 0b01000000);
  // if h12 is true, it's 12h mode; false is 24h.
  if (h12) 
  {
    // 12 hour
    bool am_pm = (Hour > 11);
    temp_hour = Hour;
    if (temp_hour > 11) 
    {
      temp_hour = temp_hour - 12;
    }
    if (temp_hour == 0) {
      temp_hour = 12;
    }
    temp_hour = decToBcd(temp_hour) | (am_pm << 5) | 0b01000000;
  } 
  else 
  {
    // 24 hour
    temp_hour = decToBcd(Hour) & 0b10111111;
  }

  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0x02);
  Wire.write(temp_hour);
  Wire.endTransmission();
}

void myDS1307::setDoW(byte DoW) 
{
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0x03);
  Wire.write(decToBcd(DoW)); 
  Wire.endTransmission();
}

void myDS1307::setDate(byte Date) 
{
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0x04);
  Wire.write(decToBcd(Date));  
  Wire.endTransmission();
}

void myDS1307::setMonth(byte Month) 
{
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0x05);
  Wire.write(decToBcd(Month)); 
  Wire.endTransmission();
}

void myDS1307::setYear(byte Year) 
{
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0x06);
  Wire.write(decToBcd(Year));  
  Wire.endTransmission();
}

void myDS1307::setClockMode(bool h12) 
{
  // sets the mode to 12-hour (true) or 24-hour (false).
  byte temp_buffer;
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0x02);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 1);
  temp_buffer = Wire.read();
  // Set the flag to the requested value:
  if (h12) {
    temp_buffer = temp_buffer | 0b01000000;
  } else {
    temp_buffer = temp_buffer & 0b10111111;
  }
  // Write the byte
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0x02);
  Wire.write(temp_buffer);
  Wire.endTransmission();
}



byte myDS1307::decToBcd(byte val) 
{
// Convert normal decimal numbers to binary coded decimal
  return ( (val/10*16) + (val%10) );
}

byte myDS1307::bcdToDec(byte val) 
{
// Convert binary coded decimal to normal decimal numbers
  return ( (val/16*10) + (val%16) );
}

byte myDS1307::readControlByte(bool which) 
{
  // Read selected control byte
  // first byte (0) is 0x0e, second (1) is 0x0f
  Wire.beginTransmission(DS1307_ADDRESS);
  if (which) {
    // second control byte
    Wire.write(0x0f);
  } else {
    // first control byte
    Wire.write(0x0e);
  }
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 1);
  return Wire.read();  
}

void myDS1307::writeControlByte(byte control, bool which) 
{
  // Write the selected control byte.
  // which=false -> 0x0e, true->0x0f.
  Wire.beginTransmission(DS1307_ADDRESS);
  if (which) {
    Wire.write(0x0f);
  } else {
    Wire.write(0x0e);
  }
  Wire.write(control);
  Wire.endTransmission();
}


//////////////////////////////////////////////////////////////////////////
////////////myDataloggerDS1307.cpp ////////////////////////////////////////////

#include "myDS1307.h"
#include "myAT24C32.h"
#define EEPROM_address 0x50

myDS1307 myRTC;
myAT24C32 mem(EEPROM_address);

byte Sec,Min,Hr,DW,Date,Mo,Yr;
byte OldSec=0;
bool century = false;
bool h12,PM_time;
const int buttonPin = 32; 
int buttonState;             
int lastButtonState = LOW; 
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50; 
int ledState = LOW; 
const int ledPin = 13;
int reading;
unsigned int address=0;

void setup()
{
  Serial.begin(115200);
  Serial.println("");
  Serial.println("DataLogger Start");
 // Serial.println("rtc config");
 // setRTC();
 // Serial.println("set rtc completed");
 
// Serial.println("start mem clear");
// mem.clear(0xFF);
// Serial.println("");
// Serial.println("mem cleared!");

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);
  delay(1000);
}

void loop() 
{
  debouceRead();
  if(ledState)
  {
    scanWrite();
    dumpData();
    //delay(50);
    ledState=LOW;
  }
}

void dumpData()
{
  unsigned int add2=0;
  byte temp;
  Serial.println("");
  Serial.print("dump data:");
  do
  {
   temp=mem.read(add2);
   if(temp==0x7A)Serial.println("");
   else
   {
    if(temp==0xFF) break;
    Serial.print(temp);
    Serial.print(" ");
   }
   add2++;
  }while(temp!=0xFF); 
}

void scanWrite()
{
  while(mem.read(address)!=0xFF)
  {
   address++;
  }
  getRTC();
  mem.write(address,0x7A); address++;
  mem.write(address,Date); address++;
  mem.write(address,Mo); address++;
  mem.write(address,Yr); address++;
  mem.write(address,Hr); address++;
  mem.write(address,Min); address++;
  mem.write(address,Sec); address++;  
}

void debouceRead()
{
  reading = digitalRead(buttonPin);
  if (reading != lastButtonState) 
  {
   lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) 
  {
    if (reading != buttonState) 
    {
      buttonState = reading;
      if (buttonState == HIGH) 
      {
        ledState = HIGH;
      }
    }
  }
  digitalWrite(ledPin, ledState);
  lastButtonState = reading;
}

void getRTC() 
{
   Sec = myRTC.getSecond(); 
   Min = myRTC.getMinute(); 
   Hr = myRTC.getHour(h12,PM_time); 
   DW = myRTC.getDoW(); 
   Date = myRTC.getDate(); 
   Mo = myRTC.getMonth();
   Yr = myRTC.getYear();
} 

void setRTC ()
{
   myRTC.setClockMode(0); 
   myRTC.setSecond(00); 
   myRTC.setMinute(27); 
   myRTC.setHour(21);
   myRTC.setDoW(7); 
   myRTC.setDate(3); 
   myRTC.setMonth(4); 
   myRTC.setYear(22);
}







   



