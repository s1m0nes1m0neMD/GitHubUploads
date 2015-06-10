#define echoPin 8 // Echo Pin
#define trigPin 9 // Trigger Pin
#define stopfar 13 // Stop Farlar
#define gerivitesfar 12 // gerivites Farlar
#define onfarlar 2 // ön farlar

int duration, distance; // Duration used to calculate distance
#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); //TX, RX respetively
String readdata;

void setup() {
 BT.begin(9600);
 Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(stopfar, OUTPUT); // frene basıldığı zaman yanacak Stop Farlar
 pinMode(gerivitesfar, OUTPUT); // geriye basıldığı zaman yanacak gerivites Farlar
 pinMode(onfarlar, OUTPUT); // ileri gaza basınca ön farlar yansın
}
//-----------------------------------------------------------------------// 
void loop() {
digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
 if ( distance< 30) {BT.print(distance);
   BT.print("çok yakın: ");digitalWrite(4, LOW);delay (50);BT.print(distance);
   BT.println("cm"); readdata = "stop"; delay (50);
   }
if ( 30 < distance, distance < 40) { //engel freni
 BT.print("çok yakın: ");digitalWrite(4, HIGH);delay (50);BT.print(distance);
   BT.println("cm"); readdata = "stop"; delay (50);
   }
if (distance> 40) {
 BT.print(distance); BT.println("cm");digitalWrite(stopfar, LOW);readdata="";
  delay(50); }
 
  while (BT.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable
  char c = BT.read(); //Conduct a serial read
  readdata += c; //build the string- "forward", "reverse", "left" and "right"
  } 
  if (readdata.length() > 0) {
    Serial.println(readdata);
    
  if(readdata == "farlaryansin")
  {
  digitalWrite(onfarlar, HIGH);digitalWrite(stopfar, LOW);
     delay(50); 
    }
  else  if(readdata == "farlarsonsun")
    {
  digitalWrite(onfarlar, LOW);digitalWrite(stopfar, LOW);
     delay(50); 
    }
 else  if(readdata == "forward")
  {
   digitalWrite(4, LOW);
   digitalWrite(6, HIGH);
   digitalWrite(stopfar, LOW);digitalWrite(gerivitesfar, LOW);
   delay(50); ;
  }

  else  if(readdata == "reverse")
  {
   digitalWrite(4, HIGH);
   digitalWrite(6, LOW);digitalWrite(stopfar, LOW);digitalWrite(gerivitesfar, HIGH);
    delay(50);
  }

  else  if (readdata == "right")
  {
    digitalWrite (3,LOW);
    digitalWrite (5,HIGH);digitalWrite(stopfar, LOW);digitalWrite(gerivitesfar, LOW);
    delay (50);
   }

 else  if ( readdata == "left")
 {
   digitalWrite (3, HIGH);
   digitalWrite (5, LOW);digitalWrite(stopfar, LOW);digitalWrite(gerivitesfar, LOW);
   delay (50);
 }

 else  if (readdata == "stop")
 {
   digitalWrite (3, LOW);
   digitalWrite (4, LOW);
   digitalWrite (5, LOW);
   digitalWrite (6, LOW); digitalWrite(stopfar, HIGH);digitalWrite(gerivitesfar, LOW);
   delay (50);
 }
 else
readdata="";}
} //Reset the variable

