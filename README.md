# esp32-internetwork-messaging-device

## Objective
This project uses two ESP32-DevKitC boards and SSD1306 OLED displays to send and display messages across separate Wi-Fi networks. The displays show the received messages in real-time.

## Current Progress
The two ESP32s are currently capable of simple one way communication over the same Wi-Fi network, with one device acting as a soft access point and HTTP server and the other acting as a station.  

## To Do
* set up MQTT IoT core
* connect to AWS endpoint
  * test esp32A publishing
  * test esp32B publishing
  * subscribe esp32A to esp32B's publish
* test typed input on different PCs
* test two way messaging over two different networks

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
