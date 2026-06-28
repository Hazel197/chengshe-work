#include <WiFi.h>
#include <WebServer.h>

#define LED_PIN 2

const char* ssid = "abc";
const char* password = "qwer1234a";

WebServer server(80);
int brightness = 0;

void handleRoot() {
  // oninput：拖动过程实时发送请求，实现平滑调光
  String html = R"HTML(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>LED亮度调节</title>
</head>
<body>
<h2>LED亮度调节</h2>
<input type="range" min="0" max="255" value="0" id="slider">
<span id="val">0</span>
<script>
let slider = document.getElementById("slider");
let val = document.getElementById("val");
// 拖动过程实时触发
slider.oninput = function(){
  val.innerText = this.value;
  fetch("/set?b="+this.value);
}
</script>
</body>
</html>
)HTML";
  server.send(200, "text/html", html);
}

void handleSetBright() {
  brightness = server.arg("b").toInt();
  analogWrite(LED_PIN, brightness);
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  analogWrite(LED_PIN, brightness);

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi成功 IP: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.on("/set", handleSetBright);
  server.begin();
}

void loop() {
  server.handleClient();
}