/*
 * ROLE_PERIPHERAL
 */

#define POT A1
#define DEBUG true

#include <Wire.h>
#include <I2Cdev.h>

#include <MPU6050.h>

MPU6050 mpu;

#include "define.h"

Adafruit_SSD1306 display(OLED_RESET);
MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;
int vx, vy, vz, fx, fy, fz;
String acc = "";
String output = "";
String Date = "N/A";
String Time = "N/A";
int potdata;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  p("Serial Communication Established.\n");
  p("Setting up Wire Connection... ");
  Wire.begin();
  p("Done.\n");
  p("Setting up Display... ");
  //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  //display.display();
  wait(1);
  //display.clearDisplay();
  p("Done.\n");
  p("Setting up Accelometer... ");
  mpu.initialize();
  while (!mpu.testConnection());
  p("Done.\n");
  p("Setting Completed.\n");
}

void loop() {
  Time = "N/A";
  Date = "N/A";

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  fx = vx = (gx + 300) / 200 - 1;
  fy = vy = (gz - 100) / 200;
  fz = vz = (gz - 600) / 200 + 3;

  acc = String(fx) + '|' +
        String(fy) + '|' +
        String(fz);

  output = "data:(" + acc + ")\n";

  char* data = new char[output.length() + 1];
  output.toCharArray(data, output.length() + 1);

  Serial.write(data);

  delete[] data; data = 0;

  if (Serial.available() > 0) {
    if (Serial.find("Time:(")) {
      Date = Serial.readStringUntil('|');
      Time = Serial.readStringUntil(')');
    }
  }

  potdata = analogRead(POT);

  if (potdata <= 512) {
    //displayTime(Date, Time);
  } else {
    //displayData(fx, fy, fz);
  }
  
  // time correcting

  String secNow = Time;

  char* timeNow = new char[secNow.length() + 1];
  char* timeBefore = new char[secNow.length() + 1];

  secNow.toCharArray(timeBefore, secNow.length() + 1);

  for (;;) {
    if(Serial.available() > 0) {
      if(Serial.find("Time:(")) {
        if(Serial.find('|')) {
          secNow = Serial.readStringUntil(')');
        }
      }
    }
    secNow.toCharArray(timeNow, secNow.length() + 1);
    if (!strcmp(timeBefore, timeNow))
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

  display.setCursor(10, 0);
  display.print("x:"); display.println(x);
  display.setCursor(10, 20);
  display.print("y:"); display.println(y);
  display.setCursor(10, 40);
  display.print("z:"); display.println(z);

  display.display();
}
