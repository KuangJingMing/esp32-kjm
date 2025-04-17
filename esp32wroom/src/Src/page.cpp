#include "../Inc/page.hpp" // 使用相对路径引入头文件

extern WebServer server;

// 从SPIFFS中读取文件内容并转换为字符串
String readFile(fs::FS &fs, const char *path) {
    File file = fs.open(path, "r");
    if (!file || file.isDirectory()) {
        Serial.println("- failed to open file for reading");
        return String();
    }
    String fileContent;
    while (file.available()) {
        char c = char(file.read());
        fileContent += c;
    }
    file.close();
    return fileContent;
}

// 根页面处理逻辑
void handleRoot() {
  String html = readFile(SPIFFS, "/index.html"); 
  if (html.length() > 0) {
    server.send(200, "text/html", html);
  } else {
    server.send(404, "text/plain", "can not open html file");
  }
}