// IR Sensors
int sensor1 = 32;  // Left most sensor
int sensor2 = 33;
int sensor3 = 25;
int sensor4 = 26;  // Right most sensor
int sensor[4] = {0, 0, 0, 0}; 
// Initial Values of Sensors
int motorInput1 = 18;   //L1
int motorInput2 = 19;   //L2
int motorInput3 = 13;   //R1
int motorInput4 = 27;   //R2

int left_motor_speed=200;
int right_motor_speed=200; 
int sw=39;
// Output Pins for Led
int ledPin1 = 2;


const int freq = 5000;
const int ledChannel_0 = 0;
const int ledChannel_1 = 1;
const int ledChannel_2 = 2;
const int ledChannel_3 = 3;
const int resolution = 8;

void setup()
{
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sw, INPUT_PULLUP);

  pinMode(motorInput1, OUTPUT);
  pinMode(motorInput2, OUTPUT);
  pinMode(motorInput3, OUTPUT);
  pinMode(motorInput4, OUTPUT);

  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1, LOW);

  ledcSetup(ledChannel_0, freq, resolution);
  ledcSetup(ledChannel_1, freq, resolution);
  ledcSetup(ledChannel_2, freq, resolution);
  ledcSetup(ledChannel_3, freq, resolution);
  ledcAttachPin(motorInput1, ledChannel_0);
  ledcAttachPin(motorInput2, ledChannel_1);
  ledcAttachPin(motorInput3, ledChannel_2);
  ledcAttachPin(motorInput4, ledChannel_3);

  Serial.begin(115200);                    
  delay(500);
  while(digitalRead(sw)==1);
  Serial.println("Started !!");
  delay(500);
}



void loop()
{
  sensor[0] = !digitalRead(sensor1);
  sensor[3] = !digitalRead(sensor4);
  
  if(sensor[0]==1)
  {
    left_motor_speed=0;    
  }else
  {
    left_motor_speed=220;
  }

  if(sensor[3]==1)
  {
    right_motor_speed=0;
  }else
  {
    right_motor_speed=220;
  } 
  forwardPWM();
}
  
void forwardPWM()
{
  ledcWrite(ledChannel_0, 0); 
  ledcWrite(ledChannel_1, left_motor_speed); 
  ledcWrite(ledChannel_2, 0); 
  ledcWrite(ledChannel_3, right_motor_speed); 
}

