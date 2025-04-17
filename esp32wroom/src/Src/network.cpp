#include "../Inc/network.hpp" // 使用相对路径引入头文件
#include <WiFi.h>

const char *ssid = "xiaomi";          // STA模式下的SSID（要连接的WiFi名称）
const char *password = "12345678"; // STA模式下的密码

void setupWiFi() {
  // 设置为STA模式（连接到现有的WiFi网络）
  WiFi.mode(WIFI_STA);
  
  // 连接到指定的WiFi网络
  WiFi.begin(ssid, password);

  Serial.println("正在连接到WiFi网络...");
  Serial.print("WiFi名称 (SSID): ");
  Serial.println(ssid);
  Serial.print("WiFi密码: ");
  Serial.println(password);

  // 等待连接成功
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // 连接成功后打印IP地址
  Serial.println("");
  Serial.println("WiFi连接成功！");
  Serial.print("ESP32 IP地址: ");
  Serial.println(WiFi.localIP()); // 显示ESP32在局域网中的IP地址
}