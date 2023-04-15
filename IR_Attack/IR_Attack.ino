#include <Servo.h>

Servo servoLeft;
Servo servoRight;

byte irLeftOld;
byte irRightOld;
int counter;

int leftReciever = 10;
int leftLED = 9;
int rightReciever = 3;
int rightLED = 2;
int leftServo = 12;
int rightServo = 11;
int dir = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("***Reset***");
  tone(4, 3000, 1000);
  delay(1000);
  pinMode(leftLED, OUTPUT); // Left LED
  pinMode(rightLED, OUTPUT); // Right LED
  pinMode(leftReciever, INPUT);  // Right IR
  pinMode(rightReciever, INPUT);  // Left IR
  servoLeft.attach(leftServo);
  servoRight.attach(rightServo);
  
  irLeftOld = 0;
  irRightOld = 1;
  counter = 0;
}

void loop() {
  int irLeft = irDetect(leftLED, leftReciever, 38000);
  int irRight = irDetect(rightLED, rightReciever, 38000);

  if(irLeft != irRight){
    if ((irLeft != irLeftOld) && (irRight != irRightOld)){
      counter ++;
      irLeftOld = irLeft;
      irRightOld = irRight;
      if(counter == 4){
        irLeft = 0;
        irRight = 0;
        counter = 0;
      }
    } else{
      counter = 0;
    }
  }
  if(irLeft == 0 || irRight == 0){
    drive(500, 1);
  } else if (irLeft == 0 && irRight == 1){
    turn(250, 0);
    drive(250, 1);
    dir = 0;
  } else if(irLeft == 1 && irRight == 0){
    turn(250, 1);
    drive(250, 1);
    dir = 1;
  } else {
    turn(250, dir);
  }

}

void turn(int time, bool dir){
    if (dir==1){
      servoLeft.writeMicroseconds(1700);
      servoRight.writeMicroseconds(1700);
      delay(time/2);
      servoLeft.writeMicroseconds(1600);
      servoRight.writeMicroseconds(1600);
      delay(time/2);
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1500);
    } else{
      servoLeft.writeMicroseconds(1300);
      servoRight.writeMicroseconds(1300);
      delay(time/2);
      servoLeft.writeMicroseconds(1400);
      servoRight.writeMicroseconds(1400);
      delay(time/2);
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1500);      
    }
}

void drive(int time, bool dir){
    if (dir==1){
      servoLeft.writeMicroseconds(1700);
      servoRight.writeMicroseconds(1300);
      delay(time);
    } else{
      servoLeft.writeMicroseconds(1300);
      servoRight.writeMicroseconds(1700);
      delay(time);     
    }
}

int irDetect(int irLedPin, int irRecieverPin, long frequency){
  tone(irLedPin, frequency, 8);   // IRLED 38 kHz for at least 1 ms
  delay(1);
  int ir = digitalRead(irRecieverPin);  
  delay(1);     // Wait before recheck
  return ir;    // Returns 1 no detect, 0 detect
}
