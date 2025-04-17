# 设置变量
$SPIFFS_BIN_PATH = ".\spiffs.bin"  # 相对路径，当前目录下的 spiffs.bin
$DATA_DIR = ".\Data"               # 相对路径，当前目录下的 Data 子目录
$ESP_PORT = "COM4"                 # 请根据实际串口号调整

$SPIFFS_START_ADDRESS = "0x290000" # 更新为分区表中的地址
$SPIFFS_MAX_SIZE = 1441792         # 更新为分区表中的大小，0x160000 = 1441792 字节 (约 1.375MB)

# 生成 SPIFFS 镜像
Write-Host "正在生成 SPIFFS 镜像..."
& mkspiffs -c $DATA_DIR -b 4096 -p 256 -s $SPIFFS_MAX_SIZE $SPIFFS_BIN_PATH
if ($LASTEXITCODE -ne 0) {
    Write-Host "错误: SPIFFS 镜像生成失败！" -ForegroundColor Red
    exit 1
}

# 检查 SPIFFS bin 文件是否创建成功
if (!(Test-Path $SPIFFS_BIN_PATH)) {
    Write-Host "错误: SPIFFS 镜像未生成！" -ForegroundColor Red
    exit 1
} else {
    Write-Host "SPIFFS 镜像生成成功!" -ForegroundColor Green
    Write-Host "镜像路径: $SPIFFS_BIN_PATH"
    Write-Host "镜像大小: $((Get-Item $SPIFFS_BIN_PATH).Length) bytes"
}

# 检查 SPIFFS 镜像大小是否符合预期
$SPIFFS_SIZE = (Get-Item $SPIFFS_BIN_PATH).Length
if ($SPIFFS_SIZE -gt $SPIFFS_MAX_SIZE) {
    Write-Host "错误: 生成的镜像大小超过分区限制（$SPIFFS_MAX_SIZE bytes）！" -ForegroundColor Red
    exit 1
}

# 烧录 SPIFFS bin 文件到 ESP32
Write-Host "正在烧录 SPIFFS 镜像到 ESP32..."
& python -m esptool --port $ESP_PORT write_flash $SPIFFS_START_ADDRESS $SPIFFS_BIN_PATH
if ($LASTEXITCODE -ne 0) {
    Write-Host "错误: 烧录失败！" -ForegroundColor Red
    exit 1
}

Write-Host "操作完成！SPIFFS 镜像已成功烧录。" -ForegroundColor Green