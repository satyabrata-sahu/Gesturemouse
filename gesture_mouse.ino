#include<Wire.h>
#include<SparkFun_APDS9960.h>
#include<BleMouse.h>

#define G 32
#define R 33
#define k1 13
#define k2 14
#define q1 27
#define q2 26
//#define APDS9960_INT    2  // Needs to be an interrupt pin
BleMouse bleMouse("smouse","Espressif", 65); // 65 show the charging percentage of bluetooth
bool status = true;
// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;
 
void setup() {
 pinMode(G,OUTPUT);
 pinMode(R,OUTPUT);
 pinMode(k1,INPUT);
 pinMode(k2,INPUT);
 pinMode(q1,INPUT);
 pinMode(q2,INPUT);
  // Initialize Serial port
  Serial.begin(9600);
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("APDS-9960 - GestureTest"));
  Serial.println(F("--------------------------------"));
 
  // Initialize interrupt service routine
  attachInterrupt(0, interruptRoutine, FALLING);
 
  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
 
  // Start running the APDS-9960 gesture sensor engine
  if ( apds.enableGestureSensor(true) ) {
    Serial.println(F("Gesture sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }
  bleMouse.begin();
}
 
void loop() {
  
    if (bleMouse.isConnected())
{ 
  if (status == true)
  {
   digitalWrite(G, LOW);
   delay(3000);
   status = false;
   } 
   digitalWrite(G, HIGH);
   
   if(digitalRead(k2)==HIGH && digitalRead(q2)==HIGH && digitalRead(k1)==LOW && digitalRead(q1)==LOW){
     mouseconnected();
   }
    else if(digitalRead(k2)==HIGH && digitalRead(q1)==HIGH && digitalRead(k1)==LOW && digitalRead(q2)==LOW){
    mouseconnected1();
    }
    else if(digitalRead(k1)==HIGH && digitalRead(q2)==HIGH && digitalRead(k2)==LOW && digitalRead(q1)==LOW){
     mouseconnected2();
    }
    else if(digitalRead(k1)==HIGH && digitalRead(q1)==HIGH && digitalRead(k2)==LOW && digitalRead(q2)==LOW){
     mouseconnected3();
    }
}
else
{notconnected();}
}

void notconnected()
 {
  digitalWrite(R,LOW);
  delay(500);
  digitalWrite(R,HIGH);
  delay(500);
digitalWrite(G,HIGH);
status=true;
  }
 void ScrollDelay(){
    delay(10);
  }
void interruptRoutine() {
  isr_flag = 1;
}
 
void mouseconnected1()//declare function according to requirment
{
  if(apds.isGestureAvailable()){
switch ( apds.readGesture() ) {
  case DIR_UP:
  bleMouse.click(MOUSE_FORWARD);
  Serial.println("forward button");
   delay(150);
  break;
  case DIR_DOWN:
  bleMouse.click(MOUSE_BACK);
  Serial.println("back button");
  delay(150);
  break;
  case DIR_LEFT:
  bleMouse.click(MOUSE_MIDDLE);
  Serial.println("Centre Click");
  delay(250);
  break;
  case DIR_RIGHT:
  bleMouse.click(MOUSE_RIGHT); 
  Serial.println("Left Click");
  delay(250);     
  break;
}}
}


void mouseconnected(){
   if(apds.isGestureAvailable()){
switch ( apds.readGesture() ) {
  case DIR_UP:
  bleMouse.move(0, 0, 1);
  Serial.println("Scrolling UP");
  ScrollDelay();
  break;
  case DIR_DOWN:
  bleMouse.move(0, 0, -1);
  Serial.println("Scrolling DOWN");
  ScrollDelay();
  break;
  case DIR_LEFT:
  bleMouse.click(MOUSE_LEFT);
  Serial.println("Centre Click");
  delay(250);
  break;
  case DIR_RIGHT:
  bleMouse.click(MOUSE_RIGHT); 
  Serial.println("Left Click");
  delay(250);     
  break;
  case DIR_NEAR:
  bleMouse.click(MOUSE_BACK);    
  Serial.println("Right Click");
  delay(250);
  break;
}}
}

    
void  mouseconnected2(){
   if(apds.isGestureAvailable()){
switch ( apds.readGesture() ) {
  case DIR_UP:
  bleMouse.move(0, 1);
  Serial.println("arrow Scrolling UP");
  ScrollDelay();
  break;
  case DIR_DOWN:
  bleMouse.move(0, -1);
  Serial.println("arrow Scrolling DOWN");
  ScrollDelay();
  break;
  case DIR_LEFT:
  bleMouse.move(-1,0);
  Serial.println(" arrow move left");
  ScrollDelay();
  break;
  case DIR_RIGHT:
  bleMouse.move(1, 0);
  Serial.println("arrow move right");
  ScrollDelay();  
  break;
}}
}

void  mouseconnected3(){
   if(apds.isGestureAvailable()){
switch ( apds.readGesture() ) {
  case DIR_UP:
  bleMouse.move(0,0,1);
  Serial.println("1Scrolling UP");
  ScrollDelay();
  break;
  case DIR_DOWN:
  bleMouse.move(0,0,-1);
  Serial.println("2Scrolling DOWN");
  ScrollDelay();
  break;
  case DIR_LEFT:
  bleMouse.move(0,0,0,-1);
  Serial.println("Centre Click");
  ScrollDelay();
  break;
  case DIR_RIGHT:
  bleMouse.move(0,0,0,1);
  Serial.println("Left Click");
  ScrollDelay();    
  break;
}}
}

  
