#ifndef USART_HPP
#define USART_HPP

#include <Arduino.h>

// 声明缓冲区大小常量
#define SERIAL_BUFFER_SIZE 64

// 声明全局变量
extern char serialBuffer[SERIAL_BUFFER_SIZE];
extern bool commandReady;

// 串口中断函数声明
void IRAM_ATTR serialEvent();

// 处理串口命令的函数声明
void processSerialCommand();

// 初始化串口的函数声明
void initSerial(unsigned long baudRate = 115200);

#endif // USART_HPP