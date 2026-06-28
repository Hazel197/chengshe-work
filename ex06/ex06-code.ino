#define LEDA_PIN 18
#define LEDB_PIN 19

void setup() {
  Serial.begin(115200);
  pinMode(LEDA_PIN, OUTPUT);
  pinMode(LEDB_PIN, OUTPUT);
}

void loop() {
  // A灯渐亮、B灯渐暗
  for(int i = 0; i <= 255; i++){
    analogWrite(LEDA_PIN, i);
    analogWrite(LEDB_PIN, 255 - i);
    delay(10);
  }
  // A灯渐暗、B灯渐亮
  for(int i = 255; i >= 0; i--){
    analogWrite(LEDA_PIN, i);
    analogWrite(LEDB_PIN, 255 - i);
    delay(10);
  }
}