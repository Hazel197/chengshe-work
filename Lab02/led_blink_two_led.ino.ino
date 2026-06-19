// 定义两个LED引脚
const int led1 = 2;
const int led2 = 4;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  // LED2亮，LED4灭
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  delay(500);

  // LED2灭，LED4亮，实现交替闪烁
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  delay(500);
}