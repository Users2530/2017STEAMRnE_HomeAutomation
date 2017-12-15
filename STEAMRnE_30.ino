
#include "define.h"

#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

DATA data;
MPU6050 mpu;
tmElements_t tm;
int16_t ax, ay, az, gx, gy, gz;
int vx, vy, vz;
int fx, fy, fz;
String Time = "None.";
String acc = "";
String output = "";
bool first = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);
  Wire.begin();
  mpu.initialize();
  while(!mpu.testConnection());
}

void loop() {
  // put your main code here, to run repeatedly:
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  fx = vx = (gx + 300) / 200 + 2;
  fy = vy = (gz - 100) / 200 + 2;
  fz = vz = (gz - 600) / 200;

  output += "data:(";

  if (RTC.read(tm)) {
    Time = tmYearToCalendar(tm.Year);
    Time += '/';
    save2digits(&Time, tm.Month);`
    Time += '/';
    save2digits(&Time, tm.Day);
    Time += '/';
    save2digits(&Time, tm.Hour);
    Time += ':';
    save2digits(&Time, tm.Minute);
    Time += ':';
    save2digits(&Time, tm.Second);
  }

  acc = String(fx) + '|' +
        String(fy) + '|' +
        String(fz);

  output = "data:(" + Time + '|' + acc + ")";

  Serial.println(output);

  delay_sec(1);

}

