#include <Servo.h>

Servo servoLeft;
Servo servoRight;

void setup() {
  tone(4, 3000, 1000);  // Play start-up tone
  delay(1000);          // Finish after 1 second

  servoLeft.attach(11);
  servoRight.attach(12);

  drive(2000, 1);
  turn90(0);
  drive(2000, 0);
  pivot90(0);
  drive(2000, 1);
  turn90(0);
  drive(2000, 0);
  pivot90(0);

}

void loop() {
  // put your main code here, to run repeatedly:

}

void pivot90(bool dir){
  if(dir == 0){
  servoRight.writeMicroseconds(1300);
  delay(940);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  }else{
  servoRight.writeMicroseconds(1700);
  delay(940);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  }

}

void turn90(bool dir){
  if(dir==0){
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
  delay(515);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  }else{
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
  delay(515);
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