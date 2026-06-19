\# 实验三：ESP32 PWM呼吸灯实验

\## 一、实验目的

1\. 熟悉ESP32开发板在Arduino IDE中的配置、程序上传流程。

2\. 理解PWM脉冲宽度调制原理，掌握LEDC硬件PWM驱动LED渐变的使用方法。

3\. 学会使用串口监视器调试程序，观察程序运行输出信息。

4\. 通过修改延时参数，掌握PWM亮度变化速率的调节方式。



\## 二、实验环境

\- 硬件：ESP32开发板、USB数据线

\- 软件：Arduino IDE

\- 开发板型号：ESP32 Dev Module

\- 串口波特率：115200



\## 三、实验原理

本实验利用ESP32内置的LEDC硬件PWM模块，通过调节PWM占空比来改变LED两端平均电压，从而实现亮度平滑变化。

1\. 配置PWM频率为5000Hz，8位分辨率，亮度调节范围0\~255；

2\. 程序先让亮度从0递增到255，实现LED由暗慢慢变亮；

3\. 再让亮度从255递减到0，实现LED由亮慢慢变暗；

4\. 单次呼吸循环结束后，通过串口打印提示信息，方便调试观察。



\## 四、实验操作步骤

1\. 打开Arduino IDE，依次选择：工具 → 开发板 → ESP32 Arduino → ESP32 Dev Module；

2\. 工具 → 端口，选择ESP32设备对应的COM端口；

3\. 粘贴呼吸灯实验代码，点击上传按钮；

4\. 若上传失败，按住开发板`BOOT`按键后再次点击上传；

5\. 上传成功后观察板载LED的呼吸渐变效果；

6\. 打开串口监视器，波特率设置为115200，查看循环打印信息；

7\. 修改代码中`delay(10)`的数值，重新上传观察呼吸快慢变化：

&#x20;  - 数值变大：呼吸速度变慢；

&#x20;  - 数值变小：呼吸速度变快。



\## 五、实验代码

```cpp

// 定义LED引脚

const int ledPin = 2;



// 设置PWM属性

const int freq = 5000;        // 频率 5000Hz

const int resolution = 8;    // 分辨率 8位（0-255）



void setup() {

\&#x20; Serial.begin(115200);

\&#x20; // 将引脚、频率、分辨率绑定PWM通道

\&#x20; ledcAttach(ledPin, freq, resolution);

}



void loop() {

\&#x20; // 逐渐变亮

\&#x20; for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){

\&#x20;   ledcWrite(ledPin, dutyCycle);

\&#x20;   delay(10);

\&#x20; }



\&#x20; // 逐渐变暗

\&#x20; for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){

\&#x20;   ledcWrite(ledPin, dutyCycle);

\&#x20;   delay(10);

\&#x20; }



\&#x20; Serial.println("Breathing cycle completed");

}


