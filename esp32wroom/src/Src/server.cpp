#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

#include "../Inc/server.hpp" // 使用相对路径引入头文件
#include "../Inc/page.hpp"   // 使用相对路径引入页面处理头文件

#include <ArduinoJson.h>
#include <WiFi.h>

extern WebServer server;
bool globalSOSStatus = false; // 全局变量来存储 SOS 状态

void setSosStatus(bool s) {
  globalSOSStatus = s;
}

// 处理POST请求，更新SOS状态
void handleUpdateSOSStatus() {
  if (server.hasArg("plain")) {
    String body = server.arg("plain");
    
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, body);
    
    if (!error) {
      bool updateRequested = doc["update"];
      
      if (updateRequested) {
        // 更新状态
        globalSOSStatus = !globalSOSStatus; // 切换状态
        Serial.println("SOS状态更新: " + String(globalSOSStatus ? "激活" : "未激活"));
      }
      
      // 返回当前状态
      DynamicJsonDocument responseDoc(1024);
      responseDoc["sosActive"] = globalSOSStatus;
      String response;
      serializeJson(responseDoc, response);
      
      server.send(200, "application/json", response);
    } else {
      server.send(400, "application/json", "{\"status\":\"error\",\"message\":\"Invalid JSON\"}");
    }
  } else {
    server.send(400, "application/json", "{\"status\":\"error\",\"message\":\"No data provided\"}");
  }
}

void setupServer(WebServer &server) {
  server.on("/", handleRoot); // 注册根页面逻辑
  server.on("/get-sos-status", HTTP_POST, handleUpdateSOSStatus);
  server.begin();
  Serial.println("Web服务器启动成功，监听端口8080");
}