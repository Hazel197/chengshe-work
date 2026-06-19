const int ledPin = 2;
unsigned long previousTime = 0;
const unsigned long interval = 500; // 500ms翻转一次，周期1s，频率1Hz
bool ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long currentTime = millis();
  // 判断是否达到翻转时间
  if (currentTime - previousTime >= interval) {
    previousTime = currentTime;
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
}
