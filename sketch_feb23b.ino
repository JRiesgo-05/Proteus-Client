#define SAMPLES 300 
int pin_LEDblue = 11;
int pin_LEDgreen = 10;
int pin_LEDyellow = 9;
int pin_LEDred = 8;
int pin_switch = 2;
int pin_timer = 3;
int relay1 = 6;
int relay2 = 7;
// variables to hold the new and old switch states
boolean oldSwitchState = LOW;
boolean newSwitchState = LOW;
boolean oldSwitchState_timer = LOW;
boolean newSwitchState_timer = LOW;
byte state = 0;
const int sensorIn_1 = A0;
const int sensorIn_2 = A1;
int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
int mode =0;
long int timer = 0;
int count=0;
unsigned long startMillis;
unsigned long currentMillis;
float threshold_1 = 0;
float threshold_2 = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(pin_switch, INPUT);
  pinMode(pin_timer, INPUT);
  pinMode(relay1, OUTPUT);         digitalWrite(relay1, LOW);
  pinMode(relay2, OUTPUT);         digitalWrite(relay1, LOW);
  pinMode (sensorIn_1, INPUT);
  pinMode(pin_LEDgreen, OUTPUT);    digitalWrite(pin_LEDgreen, HIGH);
  pinMode(pin_LEDyellow, OUTPUT);   digitalWrite(pin_LEDyellow, HIGH);
  pinMode(pin_LEDred, OUTPUT);      digitalWrite(pin_LEDred, HIGH);
  pinMode(pin_LEDblue, OUTPUT);      digitalWrite(pin_LEDblue, HIGH);
  delay(200);
  pinMode(pin_LEDgreen, OUTPUT);    digitalWrite(pin_LEDgreen, LOW);
  pinMode(pin_LEDyellow, OUTPUT);   digitalWrite(pin_LEDyellow, LOW);
  pinMode(pin_LEDred, OUTPUT);      digitalWrite(pin_LEDred, LOW);
  pinMode(pin_LEDblue, OUTPUT);      digitalWrite(pin_LEDblue, LOW);
  delay(200);
  pinMode(pin_LEDgreen, OUTPUT);    digitalWrite(pin_LEDgreen, HIGH);
  pinMode(pin_LEDyellow, OUTPUT);   digitalWrite(pin_LEDyellow, HIGH);
  pinMode(pin_LEDred, OUTPUT);      digitalWrite(pin_LEDred, HIGH);
  pinMode(pin_LEDblue, OUTPUT);      digitalWrite(pin_LEDblue, HIGH); 
  delay(200);
  pinMode(pin_LEDgreen, OUTPUT);    digitalWrite(pin_LEDgreen, LOW);
  pinMode(pin_LEDyellow, OUTPUT);   digitalWrite(pin_LEDyellow, LOW);
  pinMode(pin_LEDred, OUTPUT);      digitalWrite(pin_LEDred, LOW);
  pinMode(pin_LEDblue, OUTPUT);      digitalWrite(pin_LEDblue, LOW);
  delay(5000);
  threshold_1 = (sensor_read(sensorIn_1,5000))*.5; //.5 is the 50% of the current threshold %
  Serial.println(threshold_1);
  threshold_2 = (sensor_read(sensorIn_2,5000))*.5; //.5 is the 50% of the current threshold %
  Serial.println(threshold_2);
}

float sensor_read(int sensor_number, int sampling)
{
  float result;
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  double Voltage = 0;
  double VRMS = 0;
  double AmpsRMS = 0;
   uint32_t start_time = millis();
   while((millis()-start_time) < sampling) //sample for 1 Sec
   {
       readValue = analogRead(sensor_number);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           //record the maximum sensor value/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           //record the minimum sensor value/
           minValue = readValue;
       }
   }

   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
 VRMS = (result) *0.707;  //root 2 is 0.707
 AmpsRMS = (VRMS * 1000)/mVperAmp;
 AmpsRMS = AmpsRMS/2;
   return AmpsRMS;
 }

int led_loop(int state)
{
  switch (state)
  {
    case 0:
    digitalWrite(pin_LEDgreen, LOW);    
    digitalWrite(pin_LEDyellow, LOW);
    digitalWrite(pin_LEDred, LOW);
    digitalWrite(pin_LEDblue, LOW);
    break;
    case 1:
    digitalWrite(pin_LEDgreen, LOW);
    digitalWrite(pin_LEDyellow, LOW);
    digitalWrite(pin_LEDred, LOW);
    digitalWrite(pin_LEDblue, HIGH);
    break;
    case 2:
    digitalWrite(pin_LEDgreen, LOW);    
    digitalWrite(pin_LEDyellow, LOW);
    digitalWrite(pin_LEDred, HIGH);
    digitalWrite(pin_LEDblue, LOW);
    break;
    case 3:
    digitalWrite(pin_LEDgreen, LOW);    
    digitalWrite(pin_LEDyellow, LOW);
    digitalWrite(pin_LEDred, HIGH);
    digitalWrite(pin_LEDblue, HIGH);
    break;
    case 4:
    digitalWrite(pin_LEDgreen, LOW);    
    digitalWrite(pin_LEDyellow, HIGH);
    digitalWrite(pin_LEDred, LOW);
    digitalWrite(pin_LEDblue, LOW);
    break;
    case 5:
    digitalWrite(pin_LEDgreen, LOW);    
    digitalWrite(pin_LEDyellow, HIGH);
    digitalWrite(pin_LEDred, LOW);
    digitalWrite(pin_LEDblue, HIGH);
    break;    
    case 6:
    digitalWrite(pin_LEDgreen, LOW);    
    digitalWrite(pin_LEDyellow, HIGH);
    digitalWrite(pin_LEDred, HIGH);
    digitalWrite(pin_LEDblue, LOW);
    break; 
    case 7:
    digitalWrite(pin_LEDgreen, LOW);    
    digitalWrite(pin_LEDyellow, HIGH);
    digitalWrite(pin_LEDred, HIGH);
    digitalWrite(pin_LEDblue, HIGH);
    break; 
    case 8:
    digitalWrite(pin_LEDgreen, HIGH);    
    digitalWrite(pin_LEDyellow, LOW);
    digitalWrite(pin_LEDred, LOW);
    digitalWrite(pin_LEDblue, LOW);
    break;         
    case 9:
    digitalWrite(pin_LEDgreen, HIGH);    
    digitalWrite(pin_LEDyellow, LOW);
    digitalWrite(pin_LEDred, LOW);
    digitalWrite(pin_LEDblue, HIGH);
    break;   
    case 10:
    digitalWrite(pin_LEDgreen, HIGH);    
    digitalWrite(pin_LEDyellow, LOW);
    digitalWrite(pin_LEDred, HIGH);
    digitalWrite(pin_LEDblue, LOW);
    break;  
    case 11:
    digitalWrite(pin_LEDgreen, HIGH);    
    digitalWrite(pin_LEDyellow, LOW);
    digitalWrite(pin_LEDred, HIGH);
    digitalWrite(pin_LEDblue, HIGH);
    break;    
    case 12:
    digitalWrite(pin_LEDgreen, HIGH);    
    digitalWrite(pin_LEDyellow, HIGH);
    digitalWrite(pin_LEDred, LOW);
    digitalWrite(pin_LEDblue, LOW);
    break;  
    case 13:
    digitalWrite(pin_LEDgreen, HIGH);    
    digitalWrite(pin_LEDyellow, HIGH);
    digitalWrite(pin_LEDred, LOW);
    digitalWrite(pin_LEDblue, HIGH);
    break;  
    case 14:
    digitalWrite(pin_LEDgreen, HIGH);    
    digitalWrite(pin_LEDyellow, HIGH);
    digitalWrite(pin_LEDred, HIGH);
    digitalWrite(pin_LEDblue, LOW);
    break;
    case 15:
    digitalWrite(pin_LEDgreen, HIGH);    
    digitalWrite(pin_LEDyellow, HIGH);
    digitalWrite(pin_LEDred, HIGH);
    digitalWrite(pin_LEDblue, HIGH);
    break;                     
  }
}

long int timer_set()
{
  bool loop_var = true;
  int state = 0;
  long int timer = 0;
  while(loop_var)
  {
      newSwitchState = digitalRead(pin_switch);
      if(newSwitchState != oldSwitchState)
      {
      if(newSwitchState == HIGH)
      {
      break;
      }
      else
      {
        oldSwitchState = newSwitchState;
      }
      }
    newSwitchState_timer = digitalRead(pin_timer);
    if(newSwitchState_timer != oldSwitchState_timer)
      {
      if(newSwitchState_timer == HIGH)
      {
        state++;
        Serial.println("STATE: ");
        Serial.print(state);
        if(state>15)
        {
          state = 0;
          timer = led_loop(state);
        }
        else
        {
          timer = led_loop(state);
        }
      }
      else
      {

      }
      oldSwitchState_timer = newSwitchState_timer;
      }
  }
if(state >15)
{
  state = 0;
}
//timer = 1800000*state;
timer = 2000*state; //User change this to timer = 1800000*state; when increment is 30 mins.
Serial.println("THE TIMER IS");
Serial.println(timer);
return timer;
}


void timer_process(long timer)
{
   int official_time = timer;
   long unsigned int var = 0;
   int state = 0;
   uint32_t start_time = millis();
   while((millis()-start_time) < official_time) //sample for 1 Sec
   {
    var ++; 
    if(var==20000)//For animation led of the timer change the 20000
    {
      state++;
      var=0;
      if(state>5)
      {
        state = 0;  
      }
      led_animation(state);
    }
   }  
}

void led_animation(int state)
{
  switch (state)
  {
    case 0:
    digitalWrite(pin_LEDgreen, LOW);    
    digitalWrite(pin_LEDyellow, LOW);
    digitalWrite(pin_LEDred, LOW);
    digitalWrite(pin_LEDblue, LOW);
    break;
    case 1:
    digitalWrite(pin_LEDgreen, HIGH);
    digitalWrite(pin_LEDyellow, LOW);
    digitalWrite(pin_LEDred, LOW);
    digitalWrite(pin_LEDblue, LOW);
    break;
    case 2:
    digitalWrite(pin_LEDgreen, LOW);    
    digitalWrite(pin_LEDyellow, HIGH);
    digitalWrite(pin_LEDred, LOW);
    digitalWrite(pin_LEDblue, LOW);
    break;
    case 3:
    digitalWrite(pin_LEDgreen, LOW);    
    digitalWrite(pin_LEDyellow, LOW);
    digitalWrite(pin_LEDred, HIGH);
    digitalWrite(pin_LEDblue, LOW);
    break;
    case 4:
    digitalWrite(pin_LEDgreen, LOW);    
    digitalWrite(pin_LEDyellow, LOW);
    digitalWrite(pin_LEDred, LOW);
    digitalWrite(pin_LEDblue, HIGH);
    break;  
}
}


void loop()
{

  int sensor1;
  int sensor2;
  float Amps_RMS;
  float reading1;
  float reading2;
  for (int x = 0; x < 5000; x++){
  delay(1);
  newSwitchState = digitalRead(pin_switch);
  if(newSwitchState != oldSwitchState)
  {
    break;
  }
  }

  if ( newSwitchState != oldSwitchState )
  {
    if ( newSwitchState == HIGH )
    {
      Serial.println("CLICK CLICK");      
      state++;
      if (state > 4) {
        state = 0;
      }
      digitalWrite(pin_LEDgreen, LOW);
      digitalWrite(pin_LEDyellow, LOW);
      digitalWrite(pin_LEDred, LOW);
      digitalWrite(relay1, LOW);
      digitalWrite(relay2, LOW);
      mode = 0;
      if (state == 1) {
      digitalWrite(pin_LEDgreen, HIGH);
      digitalWrite(relay1, LOW);
      digitalWrite(relay2, LOW);
      mode=1;
      }
      if (state == 2) {
        digitalWrite(pin_LEDyellow, HIGH);
      mode=2;
      }
      if (state == 3) {
        digitalWrite(pin_LEDred, HIGH);
      mode=3;
      }
      if (state == 4) {
      digitalWrite(pin_LEDred, HIGH);
      digitalWrite(pin_LEDgreen, HIGH);
      digitalWrite(pin_LEDyellow, HIGH);
      mode=4;
      }
    }
    else 
    {
      
    }
    oldSwitchState = newSwitchState;
  }

switch(mode)
{
 case 1:
 reading1 = sensor_read(sensorIn_1,1000);
 Serial.println("MODE 1");
 Serial.print(reading1,3);
 Serial.println(" Amps RMS of Sensor 1");
 reading2 = sensor_read(sensorIn_2,1000);
 if(reading1<=threshold_1)
  {
  digitalWrite(relay2,HIGH);
  }
 delay(10);
 if(reading2<=threshold_2)
 {
  digitalWrite(relay1,HIGH);
 }
 Serial.print(reading2,3);
 Serial.println(" Amps RMS of Sensor 2");
 break;
 case 2:
 reading2 = sensor_read(sensorIn_2,1000);
 Serial.println("MODE 2");
 Serial.print(reading2,3);
 Serial.println(" Amps RMS of Sensor 2");
  if(reading2<=threshold_2)
  {
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
  }
 break;
 case 3:
 Serial.println("MODE 3");
 timer = timer_set();
 break;
 case 4:
 Serial.println("MODE 4");
 float timer_display = timer/3600000;
 Serial.println("Timer hr: ");
 Serial.print(timer_display);
 timer_process(timer);
 Serial.println("TIMER IS DONE");
 digitalWrite(pin_LEDblue, LOW);
 digitalWrite(relay1,HIGH);
 digitalWrite(relay2,HIGH);
 mode=0;
 break;
 default:
 Serial.println("MODE 0");
}
}
