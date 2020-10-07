# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# compile C with /home/gerrit/.espressif/tools/tools/xtensa-esp32-elf/esp-2020r2-8.2.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc
C_FLAGS = -mlongcalls -Wno-frame-address  

C_DEFINES = -DHAVE_CONFIG_H -DMBEDTLS_CONFIG_FILE=\"mbedtls/esp_config.h\" -DUNITY_INCLUDE_CONFIG_H -DWITH_POSIX

C_INCLUDES = -I/home/gerrit/git/esp-idf/components/xtensa/include -I/home/gerrit/git/esp-idf/components/xtensa/esp32/include -I/home/gerrit/Documents/Spider/spiderrobot/experimental/GxEPD2HelloWorldFreeRTOS/config -I/home/gerrit/git/esp-idf/components/newlib/platform_include -I/home/gerrit/git/esp-idf/components/freertos/include -I/home/gerrit/git/esp-idf/components/freertos/xtensa/include -I/home/gerrit/git/esp-idf/components/heap/include -I/home/gerrit/git/esp-idf/components/log/include -I/home/gerrit/git/esp-idf/components/lwip/include/apps -I/home/gerrit/git/esp-idf/components/lwip/include/apps/sntp -I/home/gerrit/git/esp-idf/components/lwip/lwip/src/include -I/home/gerrit/git/esp-idf/components/lwip/port/esp32/include -I/home/gerrit/git/esp-idf/components/lwip/port/esp32/include/arch -I/home/gerrit/git/esp-idf/components/soc/src/esp32/. -I/home/gerrit/git/esp-idf/components/soc/src/esp32/include -I/home/gerrit/git/esp-idf/components/soc/include -I/home/gerrit/git/esp-idf/components/esp_rom/include -I/home/gerrit/git/esp-idf/components/esp_common/include -I/home/gerrit/git/esp-idf/components/esp_system/include -I/home/gerrit/git/esp-idf/components/esp32/include -I/home/gerrit/git/esp-idf/components/driver/include -I/home/gerrit/git/esp-idf/components/driver/esp32/include -I/home/gerrit/git/esp-idf/components/esp_ringbuf/include -I/home/gerrit/git/esp-idf/components/efuse/include -I/home/gerrit/git/esp-idf/components/efuse/esp32/include -I/home/gerrit/git/esp-idf/components/espcoredump/include -I/home/gerrit/git/esp-idf/components/esp_timer/include -I/home/gerrit/git/esp-idf/components/esp_ipc/include -I/home/gerrit/git/esp-idf/components/soc/soc/esp32/. -I/home/gerrit/git/esp-idf/components/soc/soc/esp32/include -I/home/gerrit/git/esp-idf/components/soc/soc/esp32/../include -I/home/gerrit/git/esp-idf/components/vfs/include -I/home/gerrit/git/esp-idf/components/esp_wifi/include -I/home/gerrit/git/esp-idf/components/esp_wifi/esp32/include -I/home/gerrit/git/esp-idf/components/esp_event/include -I/home/gerrit/git/esp-idf/components/esp_netif/include -I/home/gerrit/git/esp-idf/components/esp_eth/include -I/home/gerrit/git/esp-idf/components/tcpip_adapter/include -I/home/gerrit/git/esp-idf/components/app_trace/include -I/home/gerrit/git/esp-idf/components/mbedtls/port/include -I/home/gerrit/git/esp-idf/components/mbedtls/mbedtls/include -I/home/gerrit/git/esp-idf/components/mbedtls/esp_crt_bundle/include -I/home/gerrit/git/esp-idf/components/bootloader_support/include -I/home/gerrit/git/esp-idf/components/app_update/include -I/home/gerrit/git/esp-idf/components/spi_flash/include -I/home/gerrit/git/esp-idf/components/nvs_flash/include -I/home/gerrit/git/esp-idf/components/pthread/include -I/home/gerrit/git/esp-idf/components/wpa_supplicant/include -I/home/gerrit/git/esp-idf/components/wpa_supplicant/port/include -I/home/gerrit/git/esp-idf/components/wpa_supplicant/include/esp_supplicant -I/home/gerrit/git/esp-idf/components/perfmon/include -I/home/gerrit/git/esp-idf/components/asio/asio/asio/include -I/home/gerrit/git/esp-idf/components/asio/port/include -I/home/gerrit/git/esp-idf/components/cbor/port/include -I/home/gerrit/git/esp-idf/components/coap/port/include -I/home/gerrit/git/esp-idf/components/coap/port/include/coap -I/home/gerrit/git/esp-idf/components/coap/libcoap/include -I/home/gerrit/git/esp-idf/components/coap/libcoap/include/coap2 -I/home/gerrit/git/esp-idf/components/console -I/home/gerrit/git/esp-idf/components/nghttp/port/include -I/home/gerrit/git/esp-idf/components/nghttp/nghttp2/lib/includes -I/home/gerrit/git/esp-idf/components/esp-tls -I/home/gerrit/git/esp-idf/components/esp_adc_cal/include -I/home/gerrit/git/esp-idf/components/esp_gdbstub/include -I/home/gerrit/git/esp-idf/components/esp_hid/include -I/home/gerrit/git/esp-idf/components/tcp_transport/include -I/home/gerrit/git/esp-idf/components/esp_http_client/include -I/home/gerrit/git/esp-idf/components/esp_http_server/include -I/home/gerrit/git/esp-idf/components/esp_https_ota/include -I/home/gerrit/git/esp-idf/components/protobuf-c/protobuf-c -I/home/gerrit/git/esp-idf/components/protocomm/include/common -I/home/gerrit/git/esp-idf/components/protocomm/include/security -I/home/gerrit/git/esp-idf/components/protocomm/include/transports -I/home/gerrit/git/esp-idf/components/mdns/include -I/home/gerrit/git/esp-idf/components/esp_local_ctrl/include -I/home/gerrit/git/esp-idf/components/sdmmc/include -I/home/gerrit/git/esp-idf/components/esp_serial_slave_link/include -I/home/gerrit/git/esp-idf/components/esp_websocket_client/include -I/home/gerrit/git/esp-idf/components/expat/expat/expat/lib -I/home/gerrit/git/esp-idf/components/expat/port/include -I/home/gerrit/git/esp-idf/components/wear_levelling/include -I/home/gerrit/git/esp-idf/components/fatfs/diskio -I/home/gerrit/git/esp-idf/components/fatfs/vfs -I/home/gerrit/git/esp-idf/components/fatfs/src -I/home/gerrit/git/esp-idf/components/freemodbus/common/include -I/home/gerrit/git/esp-idf/components/idf_test/include -I/home/gerrit/git/esp-idf/components/idf_test/include/esp32 -I/home/gerrit/git/esp-idf/components/jsmn/include -I/home/gerrit/git/esp-idf/components/json/cJSON -I/home/gerrit/git/esp-idf/components/libsodium/libsodium/src/libsodium/include -I/home/gerrit/git/esp-idf/components/libsodium/port_include -I/home/gerrit/git/esp-idf/components/mqtt/esp-mqtt/include -I/home/gerrit/git/esp-idf/components/openssl/include -I/home/gerrit/git/esp-idf/components/spiffs/include -I/home/gerrit/git/esp-idf/components/ulp/include -I/home/gerrit/git/esp-idf/components/unity/include -I/home/gerrit/git/esp-idf/components/unity/unity/src -I/home/gerrit/git/esp-idf/components/wifi_provisioning/include 

