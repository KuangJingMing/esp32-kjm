#include "../Inc/usart.hpp"
#include "../Inc/server.hpp"
#include <Arduino.h>
#include <string.h>

// 定义全局变量
char serialBuffer[SERIAL_BUFFER_SIZE];
int bufferIndex = 0;
bool commandReady = false;

// 初始化串口函数
void initSerial(unsigned long baudRate) {
    Serial.begin(baudRate);
    Serial.println("串口初始化完成");
}

// 串口中断回调函数实现
void IRAM_ATTR serialEvent() {
    while (Serial.available()) {
        char inChar = (char)Serial.read();
        
        // 如果收到换行或回车，表示命令结束
        if (inChar == '\n' || inChar == '\r') {
            if (bufferIndex > 0) {
                serialBuffer[bufferIndex] = '\0';  // 添加字符串结束符
                commandReady = true;
                bufferIndex = 0;
            }
        } else {
            // 添加字符到缓冲区，防止溢出
            if (bufferIndex < SERIAL_BUFFER_SIZE - 1) {
                serialBuffer[bufferIndex++] = inChar;
            }
        }
    }
}

// 处理串口命令的函数实现
void processSerialCommand() {
    if (commandReady) {
        if (strcmp(serialBuffer, "START_SOS") == 0) {
            Serial.println("收到开始SOS指令");
            setSosStatus(true);
        } 
        else if (strcmp(serialBuffer, "STOP_SOS") == 0) {
            Serial.println("收到停止SOS指令");
            setSosStatus(false);
        }
        else if (strcmp(serialBuffer, "GET_IP") == 0) {
            Serial.print('<');
            Serial.print(WiFi.localIP());
            Serial.println('>');
        }
        commandReady = false;
    }
}