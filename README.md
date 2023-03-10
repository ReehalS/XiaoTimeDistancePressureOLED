# Time, Temperature, Pressure, Distance Sensor
This is a handheld device capable of telling time, temperature, pressure and can also function as a handheld distance measurer.
Pulls the time from the NTP servers by connecting to Wifi.

## Components used:

1. [Xiao ESP32-C3](https://www.seeedstudio.com/Seeed-XIAO-ESP32C3-p-5431.html?gclid=Cj0KCQiApKagBhC1ARIsAFc7Mc60khgql8XgAPUv_kWXXiOs9c-ZzNqNyL-MhDEzU8uwlYhVZclULnAaAi9WEALw_wcB)
2. [128x64 I2C OLED Screen](https://www.amazon.com/HiLetgo-Serial-128X64-Display-Color/dp/B06XRBTBTB/ref=sr_1_2_sspa?crid=3I2X1GGFF9JU8&keywords=128x64+i2c+oled+display&qid=1678425631&sprefix=128x64+i2c+oled+display%2Caps%2C138&sr=8-2-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEyRFJZUzRNNkJGR0JOJmVuY3J5cHRlZElkPUEwMzg0ODIyUVkxT1pEM042VEc2JmVuY3J5cHRlZEFkSWQ9QTA3OTg1ODJNNFJMSFY0TkJNSiZ3aWRnZXROYW1lPXNwX2F0ZiZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU=)
3. [BMP280](https://www.amazon.com/HiLetgo-Precision-BMP280-3-3-Atmospheric-Pressure/dp/B07VNDZ6N4/ref=sr_1_3?crid=292KE75CWB7U0&keywords=BMP280&qid=1678425681&sprefix=bmp280%2Caps%2C124&sr=8-3): Barometric or Pressure Sensor
4. [VL53L0X](https://www.amazon.com/HiLetgo-VL53L0X-Distance-Measurement-Breakout/dp/B071DW8M8V/ref=sr_1_1_sspa?keywords=vl53l0x&qid=1678425704&sprefix=VL53%2Caps%2C139&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEzUVE3M0RWSFJHS1BHJmVuY3J5cHRlZElkPUEwNjAyMDkwMTJaVDVHSUxTWTAwRCZlbmNyeXB0ZWRBZElkPUEwMTQ2NTYzQVY3MEpGMlg3U0dGJndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==): ToF Sensor
5. Push buttons (x2)
6. Slide switch
7. 1000mAh 3.7V battery (capacity can vary)    
8. Connecting wires

The Xiao ESP32-C3 has an inbuilt battery charging circuit, removing the need for an external one.

## Wiring Diagram

![TempDistTime_bb](https://user-images.githubusercontent.com/126985041/224226720-88c24c38-9e55-45de-94db-faa0005e6196.jpg)

## Modifications for personal use

1. In the Code, the SSID and Password (lines 10 and 11) for the WiFi network that the ESP32 will connect to in order to get the time.
2. In line 14, the offset time from GMT should be changed to match your own timezone.
3. Button pins D0 and D1 defined in lines 45 and 46 should also be changed as required.

## Constraints

* This version relies on the internal RTC of an ESP32, and will gradually lose seconds or minutes over the course of a day.
* An external RTC was ommited due to size constraints, but I will test code that also includes an external RTC for better timekeeping.
* Currently I recommend restarting at least once a day to pull the time from the NTP servers again.
* I have currently not tested the on time between charges

## Future work

* Upon completion, images of the physical version will be uploaded too.
* Current versions are simply on a breadboard.
* I will test with an external RTC for better timekeeping.
* Additional changes to code will be made in the following weeks to allow further improvements to code.
