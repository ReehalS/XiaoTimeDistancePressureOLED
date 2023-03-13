#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include "esp_wifi.h"
#include "time.h"
#include "Adafruit_VL53L0X.h"

const char* ssid       = "ENTER_YOUR_SSID";                            // CHANGE AS REQUIRED
const char* password   = "ENTER_YOUR_PASSWORD";                        // CHANGE AS REQUIRED

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -28800;                                    //offset for PST
const int   daylightOffset_sec = 0;

RTC_DATA_ATTR struct tm timeinfo;

Adafruit_BMP280 bmp;

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int button1State=LOW;                                        //button B1
int button2State=LOW;                                        //button B2
int menu=0;

int button1Pin=D0;
int button2Pin=D1;


int tempRefresh=1000;                                       //how long to wait between refreshes in temp display
int tempDisplayTime=7;                                      //how many times to refresh for displaying temperature
int distanceRefresh=100;                                    //how long to wait between refreshes in distance display
int distanceDisplayCount=70;                                //how many times to refresh for displaying distance

void setup() {
  Serial.begin(115200);

  bmp.begin(0x76);                                          //barometer setup

  lox.begin(0x29);                                          //ToF sensor setup

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);                //OLED display setup
  display.clearDisplay();
  display.display();
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(2);

  pinMode(button1Pin, INPUT_PULLUP);                                //activation button setup
  pinMode(button2Pin, INPUT_PULLUP);

  display.setCursor(0,0);                                   //connect to WiFi
  display.print(ssid);
  display.display();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
  }
  display.setCursor(0,20);
  display.print("Connected");
  display.display();

  delay(1000);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);  //NTP config
  display.setCursor(0,40);
  if(getLocalTime(&timeinfo)){
    display.print("TimeSet");
  }
  else{
    display.print("NoTime");
  }
  display.display();
  printLocalTime();

  WiFi.disconnect(true);                            //disconnect WiFi as it's no longer needed,
  WiFi.mode(WIFI_OFF);                              // need optimization here to switch on every few hours
  display.print("DC");                              // and sync time
  display.display();
  delay(1000);
  display.clearDisplay();

  for(int i=0; i<tempDisplayTime;i++){              //display first time (just to check)
    timePrint();
    tempAltPrint();
    display.display();
    delay(tempRefresh);
   }
   for(int j=0; j<distanceDisplayCount;j++){        //display first time (just to check)
    timePrint();
    distancePrint();
    display.display();
    delay(distanceRefresh);
   }
}

void printLocalTime()                                //prints local time
{
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void timePrint(){
  display.setTextSize(2);
  display.clearDisplay();

  display.setCursor(15,0);
  getLocalTime(&timeinfo);                          //prints local time
  display.print(&timeinfo, "%H:%M:%S");
}

void degreeSymbol(){
  display.drawPixel(111, 30, SSD1306_WHITE);        //degree symbol printing
  display.drawPixel(109, 30, SSD1306_WHITE);        //code to print a small, empty square, couldnt be bothered to find the code for a rectangle
  display.drawPixel(110, 30, SSD1306_WHITE);
  display.drawPixel(109, 31, SSD1306_WHITE);
  display.drawPixel(111, 31, SSD1306_WHITE);
  display.drawPixel(111, 32, SSD1306_WHITE);
  display.drawPixel(109, 32, SSD1306_WHITE);
  display.drawPixel(110, 32, SSD1306_WHITE);
}

void tempAltPrint(){                                 //prints temperature and altitude (found from pressure, inaccurate when weather)

  display.setCursor(0,30);                            //prints the temperature
  display.print(String("Temp=")+ String(bmp.readTemperature(),1));

  degreeSymbol();                                   //displays a Degree symbol

  display.setCursor(114,30);
  display.print("C");

  display.setCursor(0,50);                          //prints altitude
  display.println(String(bmp.readPressure(),1)+String("Pa"));
 }

 void distancePrint(){

  VL53L0X_RangingMeasurementData_t measure;
  display.setTextSize(4);
  display.setCursor(5,30);

  lox.rangingTest(&measure, false);                // pass in 'true' to get debug data printout

  if (measure.RangeStatus != 4) {                  // phase failures have incorrect data
    display.print(measure.RangeMilliMeter);
    display.print("mm");
  }
  else{
    display.print("Error");
  }

  display.setTextSize(2);

 }

void loop() {
  button1State=digitalRead(D0);                    //reads button state to decide whether or not to switch on display
  button2State=digitalRead(D1);                    //Button 1 is for Temp, Button 2 is for Distance

  if(button1State==LOW){                           //INPUT_PULLUP mode on buttons
   display.ssd1306_command(SSD1306_DISPLAYON);     //switch on display
   for(int i=0; i<tempDisplayTime;i++){
    timePrint();
    tempAltPrint();
    display.display();
    delay(tempRefresh);
   }
  }
  else if(button2State==LOW){
   for(int i=0; i<distanceDisplayCount;i++){
    display.ssd1306_command(SSD1306_DISPLAYON);     //switch on display
    timePrint();
    distancePrint();
    getLocalTime(&timeinfo);
    display.display();
    delay(distanceRefresh);
    }
   }
  else{
    display.ssd1306_command(SSD1306_DISPLAYOFF);   //switches display off if button not pressed or after displaying
  }
  getLocalTime(&timeinfo);                         //updates time in the background even if no button is pressed
}
