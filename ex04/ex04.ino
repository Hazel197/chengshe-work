const int LED_PIN = 2;
const int TOUCH_PIN = T0;   // T0对应GPIO4
const int TOUCH_THRESHOLD = 400;  // 触摸阈值，可根据串口数值微调

bool ledState = false;
bool lastTouch = false;
unsigned long lastTouchTime = 0;
const unsigned long debounce = 50; // 触摸防抖50ms，防止误触发

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  int touchVal = touchRead(TOUCH_PIN);
  bool nowTouch = (touchVal < TOUCH_THRESHOLD);
  unsigned long now = millis();

  // 检测触摸按下瞬间，翻转LED状态
  if(nowTouch == true && lastTouch == false && (now - lastTouchTime) > debounce){
    lastTouchTime = now;
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }

  lastTouch = nowTouch;
  delay(10);
}