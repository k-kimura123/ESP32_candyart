#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"
#include "esp_http_client.h"

#define MAX_APs 20
#define AP_SSID "ESP32network"
#define AP_PASSWORD "12345678"
#define AP_MAX_CONN 4
#define AP_CHANNEL 0
#define STA_SSID "Kohsuke Kimura's iPhone"
#define STA_PASSWORD "password"

static esp_err_t event_handler(void *ctx, system_event_t *event){
	return ESP_OK;
}
void wifiInit(){
	ESP_ERROR_CHECK(nvs_flash_init());
	tcpip_adapter_init();
	tcpip_adapter_ip_info_t ipInfo;
	
	ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));

	wifi_init_config_t wifi_config = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&wifi_config));
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
	
	wifi_config_t sta_config = {
		.sta = {
			.ssid = STA_SSID,
			.password = STA_PASSWORD},
	};

	wifi_config_t ap_config = {
		.ap = {
			.ssid = AP_SSID,
			.password = AP_PASSWORD,
			.max_connection = AP_MAX_CONN,
			.channel = AP_CHANNEL,
			.ssid_hidden = 0,
		},
	};
	ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP,&ap_config));
	

	ESP_ERROR_CHECK(esp_wifi_start());
	//ESP_ERROR_CHECK(esp_wifi_connect());
	tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &ipInfo);
	printf("My IP: " IPSTR "\n",IP2STR(&ipInfo.ip));
}

static char *getAuthModeName(wifi_auth_mode_t auth_mode){
	char *names[] = {"OPEN","WEP","WPA PSK","WPA2 PSK","WPA WPA2 PSK", "MAX"};
	return names[auth_mode];
}

void scanWifi(void *params){
	while (true){
		wifi_scan_config_t scan_config = {
			.ssid = 0,
			.bssid = 0,
			.channel = 0,
			.show_hidden = true
		};
		ESP_ERROR_CHECK(esp_wifi_scan_start(&scan_config, true));
		wifi_ap_record_t wifi_records[MAX_APs];
		uint16_t maxRecords = MAX_APs;
		ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&maxRecords,wifi_records));

		printf("Found %d access points: \n",maxRecords);
		printf("\n");
		printf("                SSID             | Channel  |  RSSI |   Auth Mode  \n");
		printf("-------------------------------------------------------------------\n");
		for (int i = 0; i < maxRecords; i++)
			printf("%32s | %7d | %4d | %12s\n", (char *)wifi_records[i].ssid,wifi_records[i].primary,wifi_records[i].rssi,getAuthModeName(wifi_records[i].authmode)); 
		printf("-------------------------------------------------------------------\n");
	}
}
void app_main(void) {
	printf("is this working\n");
	//ESP_ERROR_CHECK(nvs_flash_init());
	//tcpip_adapter_init();
	//ESP_ERROR_CHECK(esp_event_loop_create_default());
	//ESP_ERROR_CHECK(example_connect());
	wifiInit();
	//xTaskCreate(scanWifi, "scan wifi", 1024 * 8, NULL, 2, NULL);
}