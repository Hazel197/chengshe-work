#define LED_PIN 2
const int TOUCH_PIN = T0;
const int TOUCH_THRESHOLD = 400;

bool lastTouch = false;
unsigned long lastTouchTime = 0;
const unsigned long debounce = 50;

int speedLevel = 1;
int stepArr[3] = {1,4,8};

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int touchVal = touchRead(TOUCH_PIN);
  bool nowTouch = touchVal < TOUCH_THRESHOLD;
  unsigned long now = millis();
  
  if(nowTouch && !lastTouch && (now - lastTouchTime > debounce)){
    lastTouchTime = now;
    speedLevel += 1;
    if(speedLevel > 3) speedLevel = 1;
    Serial.print("当前呼吸档位：");
    Serial.println(speedLevel);
  }
  lastTouch = nowTouch;

  int step = stepArr[speedLevel - 1];
  // 呼吸灯渐亮
  for(int i = 0; i <= 255; i += step){
    analogWrite(LED_PIN, i);
    delay(8);
  }
  // 呼吸灯渐暗
  for(int i = 255; i >= 0; i -= step){
    analogWrite(LED_PIN, i);
    delay(8);
  }
}