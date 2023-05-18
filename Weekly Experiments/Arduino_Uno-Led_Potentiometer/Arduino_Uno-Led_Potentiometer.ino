// #include <Servo.h>
// Servo testServo;

// int potentiometer = 0;
// int pulse;

// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(9600);
//   testServo.attach(9);
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   Serial.println(analogRead(A0));
//   pulse = analogRead(potentiometer);
//   pulse = map(pulse, 0, 1023, 0, 180);
//   testServo.write(pulse);
//   delay(20);
  
//   if (analogRead(A0) <= 512){
//     digitalWrite(13, HIGH);
//     digitalWrite(7, LOW);
//   } else{
//     digitalWrite(13, LOW);
//     digitalWrite(7, HIGH);
//   }
// }


#include<Servo.h>
int lightval;
int LDRpin=A0;
int tm=100;
int servopin=13;
int rotationAngle;

Servo myservo;

void setup() {
  Serial.begin(9600);
  pinMode(LDRpin,INPUT);
  myservo.attach(servopin);
  pinMode(servopin,OUTPUT);
}

void loop() {
  lightval=analogRead(LDRpin);
  Serial.println(lightval);
  delay(tm);
  
  rotationAngle = lightval/5;
  myservo.write(rotationAngle);
  Serial.print("Current Angle:");
  Serial.print(rotationAngle);
  Serial.println();
}