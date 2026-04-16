/**
 * @file    http_server.h
 * @brief   HTTP 服务器模块公共接口
 *
 * 基于 ESP-IDF esp_http_server 组件实现。
 * 提供以下功能：
 *   - 提供 index.html 静态页面（GET /）
 *   - 传感器数据 JSON 接口（GET /api/sensors）
 *   - 继电器控制 JSON 接口（POST /api/relay）
 *
 * 依赖：
 *   - esp_http_server
 *   - sensor 模块（桩，待实现）
 *   - relay  模块（桩，待实现）
 */

#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "esp_err.h"

/**
 * @brief  启动 HTTP 服务器，注册所有 URI 处理器
 *
 * 应在 WiFi 连接成功（获得 IP）后调用。
 *
 * @return ESP_OK      启动成功
 * @return ESP_FAIL    启动失败
 */
esp_err_t http_server_start(void);

/**
 * @brief  停止 HTTP 服务器并释放资源
 */
void http_server_stop(void);

#endif /* HTTP_SERVER_H */
