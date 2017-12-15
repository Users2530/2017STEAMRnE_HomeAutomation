
#define DEBUG true
#define POT 1

// for Common:
#include <Wire.h>
#include <I2Cdev.h>

// for Acc:
#include <MPU6050.h>

// for Time:
#include <TimeLib.h>
#include <DS1307RTC.h>

// for Display:
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "define.h"

Adafruit_SSD1306 display(OLED_RESET);
MPU6050 mpu;
tmElements_t tm;

int16_t ax, ay, az, gx, gy, gz;
int vx, vy, vz, fx, fy, fz;
String Date = "N/A";
String Time = "N/A";
String acc = "";
String output = "";
int _wait = 0;
int potdata;

void setup() {

  Serial.begin(115200);
  while (!Serial);

  Wire.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  wait(1);
  display.clearDisplay();

  mpu.initialize();
  while (!mpu.testConnection());

}

void loop() {
  Time = "N/A";
  Date = "N/A";

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  fx = vx = (gx + 300) / 200 + 2;
  fy = vy = (gz - 100) / 200 + 2;
  fz = vz = (gz - 600) / 200;

  acc = String(fx) + '|' +
        String(fy) + '|' +
        String(fz);

  if (RTC.read(tm)) {
    Date = tmYearToCalendar(tm.Year);
    Date += '/';
    save2digits(&Date, tm.Month);
    Date += '/';
    save2digits(&Date, tm.Day);

    Time = "";
    save2digits(&Time, tm.Hour);
    Time += ':';
    save2digits(&Time, tm.Minute);
    Time += ':';
    save2digits(&Time, tm.Second);
  }

  output = "data:(" + Date + ' ' + Time + '|' + acc + ")\n";

  char* data = new char[output.length() + 1];
  output.toCharArray(data, output.length() + 1);

  Serial.write(data);

  delete[] data;
  data = 0;

  potdata = analogRead(POT);

  if(potdata <= 512) {
    displayTime(Date, Time);
  } else {
    displayData(fx, fy, fz);
  }

  // time correcting

  String secNow = String(tm.Second);
  
  char* timeNow = new char[secNow.length() + 1];
  char* timeBefore = new char[secNow.length() + 1];

  secNow.toCharArray(timeBefore, secNow.length() + 1);
  
  for(;;) {
    secNow = String(tm.Second);
    secNow.toCharArray(timeNow, secNow.length() + 1);
    if(!strcmp(timeBefore, timeNow))
      break;
  }
  delete[] timeNow;
  delete[] timeBefore;
  
  timeNow = timeBefore = 0;

}

void displayTime(String Date, String Time) {
  display.setTextSize(2);
  display.setTextColor(WHITE);

  display.setCursor(5, 0);
  display.println("TIME");
  display.setCursor(0, 20);
  display.print(Date);
  display.print(" ");
  display.println(Time);

  display.display();
}

void displayData(int x, int y, int z) {
  display.setTextSize(2);
  display.setTextColor(WHITE);

  display.setCursor(10,0);
  display.print("x:"); display.println(x);
  display.setCursor(10,20);
  display.print("y:"); display.println(y);
  display.setCursor(10,40);
  display.print("z:"); display.println(z);

  display.display();  
}


