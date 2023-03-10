# XiaoTimeDistancePressureOLED
Handheld device capable of telling time, the Temperature, Pressure and can also function as a handheld distance measurer

Circuit is wired up as in the file TempDistTime_bb.jpg

![TempDistTime_bb](https://user-images.githubusercontent.com/126985041/224226720-88c24c38-9e55-45de-94db-faa0005e6196.jpg)

In the Code, the SSID and Password (lines 10 and 11) for the WiFi network that the ESP32 will connect to in order to get the time
In line 14, the offset time from GMT should be changed to match your own timezone.
Button pins D0 and D1 defined in lines 45 and 46 should also be changed as required

Additional changes to code will be made in the following weeks to allow further improvements to code.

Upon completion, images of the physical version will be uploaded too.
Current versions are simply on a breadboard.
