# esp32-internetwork-messaging-device

## Objective
This project uses two ESP32-DevKitC boards and SSD1306 OLED displays to send and display messages across separate Wi-Fi networks. The displays show the received messages in real-time.

## Current Progress
* one way communication over the same Wi-Fi network
  * one ESP32 acts as a soft access point and HTTP server
  * one ESP32 connects as a Wi-Fi station
* two way communication over AWS IoT Core MQTT broker over same Wi-Fi network 

## To Do
* test typed input over same and different Wi-Fi networks
* design custom keyboard/input hardware
* connect SSD1306 OLED screens to display sent and received messages

## Hardware

### MCUs
- [2x Espressif Systems ESP32-DevKitC Development Board](https://au.mouser.com/pdfDocs/esp32_devkitc_v4_schSchematic.pdf)
  - 32-bit Xtensa® dual-core at 240MHz
  - Wi-Fi® IEEE® 802.11b/g/n 2.4GHz
  - BLUETOOTH® 4.2 BR/EDR and BLE
  - 520KB SRAM (16KB for cache)
  - 448KB ROM
  - 34x GPIOs, 4x SPI, 3x UART, 2x I2C, 2x I2S, RMT, LED PWM, and 1x host SD/eMMC/SDIO
  - 1x slave SDIO/SPI, TWAI®, 12-bit ADC, and Ethernet

### Displays
- [2x DFRobot DFR0648 Monochrome 0.91 128x32 I2C OLED Display](https://github.com/DFRobot/Wiki/raw/master/DFR0648/SSD1306-1.5.pdf)
  - SSD1306 128 x 64 Dot Matrix OLED/PLED Segment/Common Driver with Controller
  - 3.3V / 5V operating supply voltage

### Power Components
- 2x USB A/USB Micro B hybrid power and data cable
  
### Wiring
- [2x 830 Tie Point (ZY-102) breadboard](https://core-electronics.com.au/solderless-breadboard-830-tie-point-zy-102.html)
- 2x 10KΩ resistor
- 10x male to male jumper cable
- 8x header pin
- 2x red LED

### Tools
- Multimeter
- Soldering iron

## Software

### Arduino Libraries
- [Adafruit BusIO](https://github.com/adafruit/Adafruit_BusIO)
- [Adafruit_GFX](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit_SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
- [ESP32 Webserver](https://github.com/espressif/arduino-esp32/tree/master/libraries/WebServer)
- [ESP32 Wifi](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi)
- [U8g2](https://github.com/olikraus/u8g2)
- [PubSubClient](https://github.com/knolleary/pubsubclient)
