// 1 corresponds to no object, 0 corresponds to seeing an object

int leftReciever = 13;
int leftLED = 10;
int rightReciever = 3;
int rightLED = 2;

void setup() {
  tone(4, 3000, 1000);
  delay(1000);

  pinMode(leftReciever, INPUT);   // Left reciever
  pinMode(leftLED, OUTPUT);   // Left IR LED
  pinMode(rightReciever, INPUT);    // Right reciever
  pinMode(rightLED, OUTPUT);   // Right IR LED
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int irLeft = irDetect(leftLED, leftReciever, 38000);
  int irRight = irDetect(rightLED, rightReciever, 38000);
  digitalWrite(8, !irLeft);
  digitalWrite(7, !irRight);
  Serial.print(irLeft);
  Serial.print(" ");
  Serial.println(irRight);
  delay(100);
}

int irDetect(int irLedPin, int irRecieverPin, long frequency){
  tone(irLedPin, frequency, 8);   // IRLED 38 kHz for at least 1 ms
  delay(1);
  int ir = digitalRead(irRecieverPin);  
  delay(1);     // Wait before recheck
  return ir;    // Returns 1 no detect, o detect
}
