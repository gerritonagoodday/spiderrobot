# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gerrit/Documents/Spider/spiderrobot/experimental/GxEPD2HelloWorldFreeRTOS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gerrit/Documents/Spider/spiderrobot/experimental/GxEPD2HelloWorldFreeRTOS

# Include any dependencies generated for this target.
include CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/flags.make

project_elf_src.c:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/gerrit/Documents/Spider/spiderrobot/experimental/GxEPD2HelloWorldFreeRTOS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating project_elf_src.c"
	/usr/bin/cmake -E touch /home/gerrit/Documents/Spider/spiderrobot/experimental/GxEPD2HelloWorldFreeRTOS/project_elf_src.c

CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/project_elf_src.c.obj: CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/flags.make
CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/project_elf_src.c.obj: project_elf_src.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gerrit/Documents/Spider/spiderrobot/experimental/GxEPD2HelloWorldFreeRTOS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/project_elf_src.c.obj"
	/home/gerrit/.espressif/tools/tools/xtensa-esp32-elf/esp-2020r2-8.2.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/project_elf_src.c.obj   -c /home/gerrit/Documents/Spider/spiderrobot/experimental/GxEPD2HelloWorldFreeRTOS/project_elf_src.c

CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/project_elf_src.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/project_elf_src.c.i"
	/home/gerrit/.espressif/tools/tools/xtensa-esp32-elf/esp-2020r2-8.2.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gerrit/Documents/Spider/spiderrobot/experimental/GxEPD2HelloWorldFreeRTOS/project_elf_src.c > CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/project_elf_src.c.i

CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/project_elf_src.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/project_elf_src.c.s"
	/home/gerrit/.espressif/tools/tools/xtensa-esp32-elf/esp-2020r2-8.2.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gerrit/Documents/Spider/spiderrobot/experimental/GxEPD2HelloWorldFreeRTOS/project_elf_src.c -o CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/project_elf_src.c.s

# Object files for target GxEPD2HelloWorldFreeRTOS.elf
GxEPD2HelloWorldFreeRTOS_elf_OBJECTS = \
"CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/project_elf_src.c.obj"

# External object files for target GxEPD2HelloWorldFreeRTOS.elf
GxEPD2HelloWorldFreeRTOS_elf_EXTERNAL_OBJECTS =

GxEPD2HelloWorldFreeRTOS.elf: CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/project_elf_src.c.obj
GxEPD2HelloWorldFreeRTOS.elf: CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/build.make
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/xtensa/libxtensa.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/mbedtls/libmbedtls.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/efuse/libefuse.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/bootloader_support/libbootloader_support.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/app_update/libapp_update.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_ipc/libesp_ipc.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/spi_flash/libspi_flash.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/nvs_flash/libnvs_flash.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/pthread/libpthread.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_system/libesp_system.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_rom/libesp_rom.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/soc/libsoc.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/vfs/libvfs.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_eth/libesp_eth.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/tcpip_adapter/libtcpip_adapter.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_netif/libesp_netif.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_event/libesp_event.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/wpa_supplicant/libwpa_supplicant.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_wifi/libesp_wifi.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/lwip/liblwip.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/log/liblog.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/heap/libheap.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_ringbuf/libesp_ringbuf.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/driver/libdriver.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/espcoredump/libespcoredump.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/perfmon/libperfmon.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp32/libesp32.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_common/libesp_common.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_timer/libesp_timer.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/freertos/libfreertos.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/newlib/libnewlib.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/cxx/libcxx.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/app_trace/libapp_trace.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/asio/libasio.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/cbor/libcbor.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/coap/libcoap.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/console/libconsole.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/nghttp/libnghttp.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp-tls/libesp-tls.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_adc_cal/libesp_adc_cal.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_gdbstub/libesp_gdbstub.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_hid/libesp_hid.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/tcp_transport/libtcp_transport.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_http_client/libesp_http_client.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_http_server/libesp_http_server.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_https_ota/libesp_https_ota.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/protobuf-c/libprotobuf-c.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/protocomm/libprotocomm.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/mdns/libmdns.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_local_ctrl/libesp_local_ctrl.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/sdmmc/libsdmmc.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_serial_slave_link/libesp_serial_slave_link.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_websocket_client/libesp_websocket_client.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/expat/libexpat.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/wear_levelling/libwear_levelling.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/fatfs/libfatfs.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/freemodbus/libfreemodbus.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/jsmn/libjsmn.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/json/libjson.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/libsodium/liblibsodium.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/mqtt/libmqtt.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/openssl/libopenssl.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/spiffs/libspiffs.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/ulp/libulp.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/unity/libunity.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/wifi_provisioning/libwifi_provisioning.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/sdmmc/libsdmmc.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/wear_levelling/libwear_levelling.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/protocomm/libprotocomm.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/protobuf-c/libprotobuf-c.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/mdns/libmdns.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/console/libconsole.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/json/libjson.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/xtensa/libxtensa.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/mbedtls/libmbedtls.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/efuse/libefuse.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/bootloader_support/libbootloader_support.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/app_update/libapp_update.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_ipc/libesp_ipc.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/spi_flash/libspi_flash.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/nvs_flash/libnvs_flash.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/pthread/libpthread.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_system/libesp_system.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_rom/libesp_rom.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/soc/libsoc.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/vfs/libvfs.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_eth/libesp_eth.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/tcpip_adapter/libtcpip_adapter.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_netif/libesp_netif.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_event/libesp_event.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/wpa_supplicant/libwpa_supplicant.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_wifi/libesp_wifi.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/lwip/liblwip.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/log/liblog.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/heap/libheap.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_ringbuf/libesp_ringbuf.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/driver/libdriver.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/espcoredump/libespcoredump.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/perfmon/libperfmon.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp32/libesp32.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_common/libesp_common.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_timer/libesp_timer.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/freertos/libfreertos.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/newlib/libnewlib.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/cxx/libcxx.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/app_trace/libapp_trace.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/nghttp/libnghttp.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp-tls/libesp-tls.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/tcp_transport/libtcp_transport.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_http_client/libesp_http_client.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_http_server/libesp_http_server.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/ulp/libulp.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/mbedtls/mbedtls/library/libmbedtls.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/mbedtls/mbedtls/library/libmbedcrypto.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/mbedtls/mbedtls/library/libmbedx509.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/soc/soc/esp32/libsoc_esp32.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libcoexist.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libcore.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libespnow.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libmesh.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libnet80211.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libpp.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/librtc.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libsmartconfig.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libphy.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/xtensa/libxtensa.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/mbedtls/libmbedtls.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/efuse/libefuse.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/bootloader_support/libbootloader_support.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/app_update/libapp_update.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_ipc/libesp_ipc.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/spi_flash/libspi_flash.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/nvs_flash/libnvs_flash.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/pthread/libpthread.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_system/libesp_system.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_rom/libesp_rom.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/soc/libsoc.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/vfs/libvfs.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_eth/libesp_eth.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/tcpip_adapter/libtcpip_adapter.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_netif/libesp_netif.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_event/libesp_event.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/wpa_supplicant/libwpa_supplicant.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_wifi/libesp_wifi.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/lwip/liblwip.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/log/liblog.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/heap/libheap.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_ringbuf/libesp_ringbuf.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/driver/libdriver.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/espcoredump/libespcoredump.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/perfmon/libperfmon.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp32/libesp32.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_common/libesp_common.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_timer/libesp_timer.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/freertos/libfreertos.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/newlib/libnewlib.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/cxx/libcxx.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/app_trace/libapp_trace.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/nghttp/libnghttp.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp-tls/libesp-tls.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/tcp_transport/libtcp_transport.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_http_client/libesp_http_client.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_http_server/libesp_http_server.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/ulp/libulp.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/mbedtls/mbedtls/library/libmbedtls.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/mbedtls/mbedtls/library/libmbedcrypto.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/mbedtls/mbedtls/library/libmbedx509.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/soc/soc/esp32/libsoc_esp32.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libcoexist.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libcore.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libespnow.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libmesh.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libnet80211.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libpp.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/librtc.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libsmartconfig.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libphy.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/xtensa/libxtensa.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/mbedtls/libmbedtls.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/efuse/libefuse.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/bootloader_support/libbootloader_support.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/app_update/libapp_update.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_ipc/libesp_ipc.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/spi_flash/libspi_flash.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/nvs_flash/libnvs_flash.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/pthread/libpthread.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_system/libesp_system.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_rom/libesp_rom.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/soc/libsoc.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/vfs/libvfs.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_eth/libesp_eth.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/tcpip_adapter/libtcpip_adapter.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_netif/libesp_netif.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_event/libesp_event.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/wpa_supplicant/libwpa_supplicant.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_wifi/libesp_wifi.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/lwip/liblwip.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/log/liblog.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/heap/libheap.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_ringbuf/libesp_ringbuf.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/driver/libdriver.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/espcoredump/libespcoredump.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/perfmon/libperfmon.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp32/libesp32.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_common/libesp_common.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_timer/libesp_timer.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/freertos/libfreertos.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/newlib/libnewlib.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/cxx/libcxx.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/app_trace/libapp_trace.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/nghttp/libnghttp.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp-tls/libesp-tls.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/tcp_transport/libtcp_transport.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_http_client/libesp_http_client.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_http_server/libesp_http_server.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/ulp/libulp.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/mbedtls/mbedtls/library/libmbedtls.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/mbedtls/mbedtls/library/libmbedcrypto.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/mbedtls/mbedtls/library/libmbedx509.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/soc/soc/esp32/libsoc_esp32.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libcoexist.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libcore.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libespnow.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libmesh.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libnet80211.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libpp.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/librtc.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libsmartconfig.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libphy.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/xtensa/libxtensa.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/mbedtls/libmbedtls.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/efuse/libefuse.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/bootloader_support/libbootloader_support.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/app_update/libapp_update.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_ipc/libesp_ipc.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/spi_flash/libspi_flash.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/nvs_flash/libnvs_flash.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/pthread/libpthread.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_system/libesp_system.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_rom/libesp_rom.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/soc/libsoc.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/vfs/libvfs.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_eth/libesp_eth.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/tcpip_adapter/libtcpip_adapter.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_netif/libesp_netif.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_event/libesp_event.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/wpa_supplicant/libwpa_supplicant.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_wifi/libesp_wifi.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/lwip/liblwip.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/log/liblog.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/heap/libheap.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_ringbuf/libesp_ringbuf.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/driver/libdriver.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/espcoredump/libespcoredump.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/perfmon/libperfmon.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp32/libesp32.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_common/libesp_common.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_timer/libesp_timer.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/freertos/libfreertos.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/newlib/libnewlib.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/cxx/libcxx.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/app_trace/libapp_trace.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/nghttp/libnghttp.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp-tls/libesp-tls.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/tcp_transport/libtcp_transport.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_http_client/libesp_http_client.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp_http_server/libesp_http_server.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/ulp/libulp.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/mbedtls/mbedtls/library/libmbedtls.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/mbedtls/mbedtls/library/libmbedcrypto.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/mbedtls/mbedtls/library/libmbedx509.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/soc/soc/esp32/libsoc_esp32.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libcoexist.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libcore.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libespnow.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libmesh.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libnet80211.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libpp.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/librtc.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libsmartconfig.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_wifi/lib/esp32/libphy.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/xtensa/esp32/libhal.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/newlib/libnewlib.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/pthread/libpthread.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/app_trace/libapp_trace.a
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/app_trace/libapp_trace.a
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_rom/esp32/ld/esp32.rom.newlib-time.ld
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_rom/esp32/ld/esp32.rom.api.ld
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_rom/esp32/ld/esp32.rom.ld
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_rom/esp32/ld/esp32.rom.libgcc.ld
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_rom/esp32/ld/esp32.rom.newlib-data.ld
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_rom/esp32/ld/esp32.rom.syscalls.ld
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp_rom/esp32/ld/esp32.rom.newlib-funcs.ld
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp32/esp32_out.ld
GxEPD2HelloWorldFreeRTOS.elf: esp-idf/esp32/ld/esp32.project.ld
GxEPD2HelloWorldFreeRTOS.elf: /home/gerrit/git/esp-idf/components/esp32/ld/esp32.peripherals.ld
GxEPD2HelloWorldFreeRTOS.elf: CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gerrit/Documents/Spider/spiderrobot/experimental/GxEPD2HelloWorldFreeRTOS/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable GxEPD2HelloWorldFreeRTOS.elf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/build: GxEPD2HelloWorldFreeRTOS.elf

.PHONY : CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/build

CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/clean

CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/depend: project_elf_src.c
	cd /home/gerrit/Documents/Spider/spiderrobot/experimental/GxEPD2HelloWorldFreeRTOS && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gerrit/Documents/Spider/spiderrobot/experimental/GxEPD2HelloWorldFreeRTOS /home/gerrit/Documents/Spider/spiderrobot/experimental/GxEPD2HelloWorldFreeRTOS /home/gerrit/Documents/Spider/spiderrobot/experimental/GxEPD2HelloWorldFreeRTOS /home/gerrit/Documents/Spider/spiderrobot/experimental/GxEPD2HelloWorldFreeRTOS /home/gerrit/Documents/Spider/spiderrobot/experimental/GxEPD2HelloWorldFreeRTOS/CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/GxEPD2HelloWorldFreeRTOS.elf.dir/depend

