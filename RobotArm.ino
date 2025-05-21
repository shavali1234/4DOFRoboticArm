#include "arduino_secrets.h"

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN 150
#define SERVOMAX 600
#define FREQUENCY 50

#define button_add 3
#define x_axis A0
#define y_axis A1
#define button_sub 2
#define shoulder_elbow_switch 4



void read_joystick_and_button_values();
void checkbuttonstate(bool m);

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

bool buttonstate=0;
unsigned joystick[]={0,0};

int prev_angles[]={70,50,90,50}; 
bool isshoulder=false;
int count=50;



void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(shoulder_elbow_switch,INPUT);
  pinMode(button_add, INPUT_PULLUP);
  pinMode(button_sub, INPUT);

  digitalWrite(LED_BUILTIN,LOW);

  Serial.begin(9600);
  delay(100);

  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
  delay(100);
  Serial.println("Servo driver initialized.");
  delay(100);

  for (size_t i=0; i<4; i++) {
    pwm.setPWM(i,0,map(prev_angles[i],0,180,SERVOMIN,SERVOMAX));
    delay(100);
  }

}

void loop() {
  read_joystick_and_button_values();
  if (joystick[0]<50 && joystick[1]<500) {
    int value1=map(constrain(--prev_angles[0],0,180),0,180,SERVOMIN,SERVOMAX);
    pwm.setPWM(0,0,value1);
    prev_angles[0]=map(value1,SERVOMIN,SERVOMAX,0,180);
  }
  if (joystick[0]>900 && joystick[1]>500) {
    int value2=map(constrain(++prev_angles[0],0,180),0,180,SERVOMIN,SERVOMAX);
    pwm.setPWM(0,0,value2);
    prev_angles[0]=map(value2,SERVOMIN,SERVOMAX,0,180);
  }

  if (joystick[0]>500 && joystick[1]<100 && isshoulder==true) {
   int value3=map(constrain(--prev_angles[1],0,70),0,180,SERVOMIN,SERVOMAX); 
   pwm.setPWM(1,0,value3);
   prev_angles[1]=map(value3, SERVOMIN, SERVOMAX, 0, 180);
  }
  if (joystick[0]>500 && joystick[1]>1000 && isshoulder==true) {
   int value3=map(constrain(++prev_angles[1],0,70),0,180,SERVOMIN,SERVOMAX); 
   pwm.setPWM(1,0,value3);
   prev_angles[1]=map(value3,SERVOMIN,SERVOMAX,0,180);
  }
  
  if (joystick[0]>500 && joystick[1]<100 && isshoulder==false) {
   int value4=map(constrain(++prev_angles[2],0,180),0,180,SERVOMIN,SERVOMAX); 
   pwm.setPWM(2,0,value4);
   prev_angles[2]=map(value4,SERVOMIN,SERVOMAX,0,180);
  }
  if (joystick[0]>500 && joystick[1]>1000 && isshoulder==false) {
   int value5=map(constrain(--prev_angles[2],0,180),0,180,SERVOMIN,SERVOMAX); 
   pwm.setPWM(2,0,value5);
   prev_angles[2]=map(value5,SERVOMIN,SERVOMAX,0,180);
  }

  prev_angles[3]=constrain(count,50,70);
  pwm.setPWM(3,0 ,map(prev_angles[3],0,180,SERVOMIN,SERVOMAX));
  for(size_t i=0;i<4;i++)
  {
    Serial.print(prev_angles[i]);
    Serial.print(" ");
  }
  Serial.print(isshoulder);
  // Serial.println();
  Serial.print(" ");
  Serial.println(count);
  Serial.println();
  delay(50);
}

void read_joystick_and_button_values()
{
  joystick[1]=analogRead(y_axis);
  joystick[0]=analogRead(x_axis);
  Serial.print(joystick[0]);
  Serial.print(" ");
  Serial.println(joystick[1]);
  int value1=digitalRead(shoulder_elbow_switch);
  int value2=digitalRead(button_add);
  int value3=digitalRead(button_sub);
  if (value1==true) {
    isshoulder=true;
    digitalWrite(LED_BUILTIN, HIGH);
  }else if (value1==false) {
    isshoulder=false;
    digitalWrite(LED_BUILTIN, LOW);
  }
  if (value2==1) {
    count=constrain(count++, 50, 70);
  }else if (value3==1) {
    count=constrain(count--, 50, 70);
  }
}

