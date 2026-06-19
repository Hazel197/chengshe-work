/*
===== 基础LED闪烁原版代码（保留存档）
const int ledPin = 2;
void setup(){
  pinMode(ledPin,OUTPUT);
}
void loop(){
  digitalWrite(ledPin,HIGH);
  delay(500);
  digitalWrite(ledPin,LOW);
  delay(500);
}
=====
*/

// 进阶实验：SOS摩尔斯求救信号灯（本次运行代码）
const int ledPin = 2;
void setup() {
  pinMode(ledPin, OUTPUT);
}
void loop() {
  // S短闪3次
  for(int i = 0; i < 3; i++){
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
  }
  delay(500);
  // O长闪3次
  for(int i = 0; i < 3; i++){
    digitalWrite(ledPin, HIGH);
    delay(600);
    digitalWrite(ledPin, LOW);
    delay(200);
  }
  delay(500);
  // S短闪3次
  for(int i = 0; i < 3; i++){
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
  }
  delay(2000);
}