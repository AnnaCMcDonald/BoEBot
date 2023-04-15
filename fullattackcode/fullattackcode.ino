#include <Servo.h>

Servo servoLeft;
Servo servoRight;

byte irLeftOld;
byte irRightOld;
int counter;
bool dir = 1;

// Constants
int leftReciever = 10;
int leftLED = 9;
int rightReciever = 3;
int rightLED = 2;
int leftServo = 12;
int rightServo = 11;


void setup() {
  // Initialize
  Serial.begin(9600);
  Serial.println("***Reset***");
  tone(4, 3000, 1000);
  delay(1000);

  pinMode(leftLED, OUTPUT);       // Left LED
  pinMode(rightLED, OUTPUT);      // Right LED
  pinMode(leftReciever, INPUT);   // Right IR
  pinMode(rightReciever, INPUT);  // Left IR
  servoLeft.attach(leftServo);    // Left servo
  servoRight.attach(rightServo);  // Right servo
  
  irLeftOld = 0;
  irRightOld = 1;
  counter = 0;
}

void loop() {
  stayIn();
  irTrack();


  // This was old code from the whiskers navigation
  // The intent is no get out of a corner
  
  // if(irLeft != irRight){
  //   if ((irLeft != irLeftOld) && (irRight != irRightOld)){
  //     counter ++;
  //     irLeftOld = irLeft;
  //     irRightOld = irRight;
  //     if(counter == 4){
  //       irLeft = 0;
  //       irRight = 0;
  //       counter = 0;
  //     }
  //   } else{
  //     counter = 0;
  //   }
  // }

}



// Functions

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
    } else if (dir==0){
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

void irTrack(){
  int irLeft = irDetect(leftLED, leftReciever, 38000);
  int irRight = irDetect(rightLED, rightReciever, 38000);
  Serial.print("irr/l");
  Serial.print(irRight);
  Serial.println(irLeft);

  if(irLeft == 0 || irRight == 0){
    drive(10, 1);
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
Serial.println(dir);
}

int irDetect(int irLedPin, int irRecieverPin, long frequency){
  tone(irLedPin, frequency, 8);   // IRLED 38 kHz for at least 1 ms
  delay(1);
  int ir = digitalRead(irRecieverPin);  
  delay(1);     // Wait before recheck
  return ir;    // Returns 1 no detect, o detect
}

void stayIn(){
  DDRD |= B11110000;                         // Set direction of Arduino pins D4-D7 as OUTPUT
  PORTD |= B11110000;                        // Set level of Arduino pins D4-D7 to HIGH
  delayMicroseconds(230);                    // Short delay to allow capacitor charge in QTI module
  DDRD &= B00001111;                         // Set direction of pins D4-D7 as INPUT
  PORTD &= B00001111;                        // Set level of pins D4-D7 to LOW
  delayMicroseconds(230);                    // Short delay
  int pins = PIND;                           // Get values of pins D0-D7
  pins >>= 4;                                // Drop off first four bits of the port; keep only pins D4-D7
  
  Serial.println(pins, BIN);                  // Display result of D4-D7 pins in Serial Monitor
  
  // Determine how to steer based on state of the four QTI sensors
  int vL, vR;
  switch(pins)                                // Compare pins to known line following states
  {
    case B1000:                               // Line on left side
    case B1100:                        
    case B1110:
    Serial.print("1");
    servoLeft.writeMicroseconds(1300);
    servoRight.writeMicroseconds(1700);
    delay(1000);
    servoRight.writeMicroseconds(1700);
    servoLeft.writeMicroseconds(1700);
    delay(900);
    servoLeft.writeMicroseconds(1500);
    servoRight.writeMicroseconds(1500); 
      break;

    case B1111:                               // Line directly in front
    Serial.print("2");
    servoLeft.writeMicroseconds(1300);
    servoRight.writeMicroseconds(1700);
    delay(1000);
    servoRight.writeMicroseconds(1700);
    servoLeft.writeMicroseconds(1700);
    delay(1000);
    servoLeft.writeMicroseconds(1500);
    servoRight.writeMicroseconds(1500);
      break;   

    case B0111:                               // Line on right side
    case B0011:                        
    case B0001:
    Serial.print("3");
    servoLeft.writeMicroseconds(1300);
    servoRight.writeMicroseconds(1700);   
    delay(1000);
    servoRight.writeMicroseconds(1300);
    servoLeft.writeMicroseconds(1300);
    delay(900);
    servoLeft.writeMicroseconds(1500);
    servoRight.writeMicroseconds(1500);                    
      break;
  }
}
