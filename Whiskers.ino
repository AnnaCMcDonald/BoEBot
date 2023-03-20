void setup() {
  // put your setup code here, to run once:
tone(4, 3000, 1000);
delay(1000);
pinMode(8, OUTPUT);
pinMode(2, OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int wLeft = digitalRead(5);
  int wRight = digitalRead(7);
  Serial.print(digitalRead(5));
  Serial.println(digitalRead(7));
  if(wLeft == 0){
    digitalWrite(8, HIGH);
  } else {
    digitalWrite(8, LOW);
  }

  if(wRight == 0)
  {
    digitalWrite(2, HIGH);
  } else {
    digitalWrite(2, LOW);
  }

}
