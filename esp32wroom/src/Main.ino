#include "./Inc/network.hpp"  // 相对路径引入网络管理头文件
#include "./Inc/server.hpp"   // 相对路径引入服务器管理头文件
#include "./Inc/page.hpp"     // 相对路径引入页面处理头文件
#include "./Inc/usart.hpp"

#include <SPIFFS.h>
#include <WebServer.h>

WebServer server(8080); // 全局定义Web服务器对象

void view_esp_partition(void) {
    Serial.println("ESP32分区信息:");
    esp_partition_iterator_t it = esp_partition_find(ESP_PARTITION_TYPE_ANY, ESP_PARTITION_SUBTYPE_ANY, NULL);
    while (it) {
        const esp_partition_t *part = esp_partition_get(it);
        Serial.printf("类型: %d, 子类型: %d, 地址: 0x%x, 大小: 0x%x, 标签: %s\n",
                 part->type, part->subtype, part->address, part->size, part->label);
        it = esp_partition_next(it);
    }
    esp_partition_iterator_release(it);
}

void setup() {
    // 初始化串口
    initSerial(115200);
    
    // 设置串口中断
    Serial.onReceive(serialEvent);
    
    view_esp_partition();
    
    // 挂载SPIFFS
    if (!SPIFFS.begin(false)) {
        Serial.println("SPIFFS挂载失败！");
        return;
    }
    Serial.println("SPIFFS挂载成功！");

    // 初始化WiFi和服务器
    setupWiFi();                 
    setupServer(server);         
}

void loop() {
    // 处理客户端请求
    server.handleClient();
    
    // 处理串口命令
    processSerialCommand();
    
    delay(10); 
}