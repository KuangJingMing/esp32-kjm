#ifndef SERVER_H
#define SERVER_H

#include <WebServer.h>

// 声明服务器初始化函数
void setupServer(WebServer &server);
void sendUpdateRequest(bool needsUpdate);
void setSosStatus(bool s);

#endif