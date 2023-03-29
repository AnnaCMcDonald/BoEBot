#include <Servo.h>

Servo servoLeft;
Servo servoRight;

byte wLeftOld;
byte wRightOld;
int counter;

void setup() {
  tone(4, 3000, 1000);
  delay(1000);
  pinMode(8, OUTPUT); // Left LED
  pinMode(2, OUTPUT); // Right LED
  pinMode(7, INPUT);  // Right whisker
  pinMode(5, INPUT);  // Left whisker
  servoLeft.attach(11);
  servoRight.attach(12);
  
  wLeftOld = 0;
  wRightOld = 1;
  counter = 0;
}

void loop() {
  byte wLeft = digitalRead(5);
  byte wRight = digitalRead(7);

  if(wLeft != wRight){
    if ((wLeft != wLeftOld) && (wRight != wRightOld)){
      counter ++;
      wLeftOld = wLeft;
      wRightOld = wRight;
      if(counter == 4){
        wLeft = 0;
        wRight = 0;
        counter = 0;
      }
    } else{
      counter = 0;
    }
  }
  if(wLeft == 0 && wRight == 0){
    digitalWrite(8, HIGH);
    digitalWrite(2, HIGH);
    drive(1000, 0);
    turn(400, 0);
  } else if (wLeft == 0 && wRight == 1){
    digitalWrite(2, LOW);
    digitalWrite(8, HIGH);
    drive(1000, 0);
    turn(400, 1);
  } else if(wLeft == 1 && wRight == 0){
    digitalWrite(8, LOW);
    digitalWrite(2, HIGH);
    drive(1000, 0);
    turn(400, 0);
  } else{
    digitalWrite(8, LOW);
    digitalWrite(2, LOW);
    drive(20, 1);
  }

  if(wRight == 0)
  {
    digitalWrite(2, HIGH);
  } else {
    digitalWrite(2, LOW);
  }

}

void turn(int time, bool dir){
    if (dir==1){
      servoLeft.writeMicroseconds(1700);
      servoRight.writeMicroseconds(1700);
      delay(time);
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1500);
    } else{
      servoLeft.writeMicroseconds(1300);
      servoRight.writeMicroseconds(1300);
      delay(time);
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1500);      
    }
}

void drive(int time, bool dir){
    if (dir==1){
      servoLeft.writeMicroseconds(1700);
      servoRight.writeMicroseconds(1300);
      delay(time);
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1500);
    } else{
      servoLeft.writeMicroseconds(1300);
      servoRight.writeMicroseconds(1700);
      delay(time);
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1500);      
    }
}
