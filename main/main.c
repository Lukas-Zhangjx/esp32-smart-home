#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "wifi_sta.h"
#include "http_server.h"

static const char *TAG = "main";

/**
 * @brief  主任务：WiFi 连接完成后启动 HTTP 服务器，进入主循环
 *
 * @param pvParameters  FreeRTOS 任务参数（未使用）
 */
static void main_task(void *pvParameters)
{
    ESP_LOGI(TAG, "main_task started");

    /* 启动 HTTP 服务器，对外提供页面与 API */
    if (http_server_start() != ESP_OK) {
        ESP_LOGE(TAG, "http server failed to start, task exit");
        vTaskDelete(NULL);
        return;
    }

    while (1) {
        /* TODO: 周期性任务，如传感器采集、状态上报等 */
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/**
 * @brief  ESP-IDF 入口：初始化 NVS，连接 WiFi，创建主任务
 */
void app_main(void)
{
    /* 初始化 NVS，WiFi 凭据存储依赖此组件 */
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    /* 阻塞直到 WiFi 连接成功或超过最大重试次数 */
    wifi_station_startup();

    /* WiFi 就绪后创建主任务 */
    xTaskCreate(main_task, "main_task", 4096, NULL, 5, NULL);
}
