#include <WiFi.h>
#include <WebServer.h>

// 配置WiFi信息
const char* ssid = "abc";
const char* password = "qwer1234a";

// 触摸引脚T0(GPIO4)
#define TOUCH_PIN T0
#define LED_PIN 2
// 触摸阈值，数值越小越灵敏
const int TOUCH_THRESHOLD =400;

WebServer server(80);
bool isAlarm = false; // 报警标志位

// 网页主页
void handleRoot() {
  String html = R"HTML(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <title>安防触摸报警系统</title>
    <style>
        body{text-align:center;margin-top:100px;font-size:24px;}
        .normal{background:#fff;color:#000;}
        .alarm{background:#ff3333;color:#fff;}
        button{padding:10px 30px;font-size:20px;margin-top:30px;cursor:pointer;}
    </style>
</head>
<body class="STATUS">
    <h2 id="tip">系统正常，未检测到入侵</h2>
    <button onclick="resetAlarm()">一键解除报警</button>
    <script>
        // 轮询实时获取安防状态
        function refreshStatus(){
            fetch("/getAlarm")
            .then(res=>res.text())
            .then(data=>{
                let body = document.querySelector("body");
                let tip = document.getElementById("tip");
                if(data=="1"){
                    body.className="alarm";
                    tip.innerText="⚠️ 检测到触摸入侵！安防报警触发！";
                }else{
                    body.className="normal";
                    tip.innerText="系统正常，未检测到入侵";
                }
            })
        }
        // 定时500ms刷新一次状态
        setInterval(refreshStatus,500);
        // 复位报警
        function resetAlarm(){
            fetch("/reset");
        }
    </script>
</body>
</html>
)HTML";
  server.send(200,"text/html",html);
}

// 获取当前报警状态接口
void handleGetAlarm(){
  server.send(200,"text/plain",isAlarm?"1":"0");
}

// 复位报警接口
void handleResetAlarm(){
  isAlarm = false;
  digitalWrite(LED_PIN, LOW);
  server.send(200,"text/plain","OK");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // WiFi连接
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi连接成功 内网IP："+WiFi.localIP().toString());

  // 绑定网页路由
  server.on("/",handleRoot);
  server.on("/getAlarm",handleGetAlarm);
  server.on("/reset",handleResetAlarm);
  server.begin();
}

void loop() {
  server.handleClient();

  // 触摸触发锁定报警
  int touchVal = touchRead(TOUCH_PIN);
  if(touchVal < TOUCH_THRESHOLD){
    isAlarm = true;
  }

  // 报警状态下LED高频闪烁
  if(isAlarm){
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
}