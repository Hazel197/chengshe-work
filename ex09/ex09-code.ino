#include <WiFi.h>
#include <WebServer.h>

// WiFi配置
const char* ssid = "abc";
const char* password = "qwer1234a";

WebServer server(80);

// 主页：仪表盘HTML页面，AJAX轮询上报采集触摸数据
void handleRoot() {
  String html = R"HTML(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="UTF-8">
<title>ESP32触摸检测实时仪表盘</title>
<style>
body{text-align:center;margin-top:40px;font-size:22px;}
#gauge{width:400px;height:220px;margin:20px auto;position:relative;}
#valueText{font-size:32px;color:#ff4400;font-weight:bold;}
</style>
</head>
<body>
<h2>ESP32 触摸检测实时仪表盘</h2>
<div id="gauge">
<svg width="400" height="220">
<path d="M 40 200 A 160 160 0 0 1 360 200" fill="none" stroke="#eee" stroke-width="20"/>
<path id="arc" d="M 40 200 A 160 160 0 0 1 40 200" fill="none" stroke="#0099ff" stroke-width="20"/>
<line id="pointer" x1="200" y1="200" x2="200" y2="60" stroke="#f33" stroke-width="4"/>
<text x="20" y="215" text-anchor="middle">0</text>
<text x="380" y="215" text-anchor="middle">1200</text>
</svg>
</div>
<p>当前触摸数值：<span id="valueText">0</span></p>
<script>
// AJAX定时拉取传感器采集数据（数据上报）
function updateData(){
  fetch("/getTouch")
  .then(res=>res.text())
  .then(val=>{
    let num = parseInt(val);
    document.getElementById("valueText").innerText = num;
    // 触摸量程修正为0~1200
    let angle = 180 - (num / 1200 * 180);
    let rad = angle * Math.PI / 180;
    let x = 200 + 140 * Math.cos(rad);
    let y = 200 - 140 * Math.sin(rad);
    document.getElementById("pointer").setAttribute("x2", x);
    document.getElementById("pointer").setAttribute("y2", y);
  })
}
// 200ms轮询一次，实时上报刷新
setInterval(updateData, 200);
</script>
</body>
</html>
)HTML";
  server.send(200, "text/html", html);
}

// 数据上报接口：实时采集触摸模拟量并返回给网页
void handleGetTouch() {
  int touchVal = touchRead(T0);
  server.send(200, "text/plain", String(touchVal));
}

void setup() {
  Serial.begin(115200);
  // WiFi连接
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi连接成功 内网IP：" + WiFi.localIP().toString());

  // 路由绑定：网页页面 + 传感器数据上报接口
  server.on("/", handleRoot);
  server.on("/getTouch", handleGetTouch);
  server.begin();
}

void loop() {
  server.handleClient();
}
