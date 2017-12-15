
#define DEBUG true

#include "def.h"

#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

MPU6050 mpu;
tmElements_t tm;

int16_t ax, ay, az, gx, gy, gz;
int vx, vy, vz, fx, fy, fz;
String Time = "N/A";
String acc = "";
String output = "";
int _wait = 0;

void setup() {
  Serial.begin(115200);
  p(" Setting up Serial Communication with baudrate 115200... done.\n Waiting for response... ");
  while (!Serial);
  p("done.\n Setting up Wire System... ");
  Wire.begin();
  p("done.\n Setting up MPU6050... ");
  mpu.initialize();
  p("done.\n Waiting for response... ");
  while (!mpu.testConnection()){
    wait(1);
    _wait++;
    Serial.println(_wait);
  }
  p("done.\n ");

  Serial.write("+++");
  Serial.write("AT+ROLE=?\r\n");
  Serial.write("AT+BIND=?\r\n");
  /*
  p("Trying to connect to Central... ");
  Serial.write("test\n");
  if(Serial.available() > 0) {
    asdf
  }
  */
}

void loop() {
  Time = "N/A";

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  fx = vx = (gx + 300) / 200 + 2;
  fy = vy = (gz - 100) / 200 + 2;
  fz = vz = (gz - 600) / 200;

  acc = String(fx) + '|' +
        String(fy) + '|' +
        String(fz);

  if (RTC.read(tm)) {
    Time = tmYearToCalendar(tm.Year);
    Time += '/';
    save2digits(&Time, tm.Month);
    Time += '/';
    save2digits(&Time, tm.Day);
    Time += ' ';
    save2digits(&Time, tm.Hour);
    Time += ':';
    save2digits(&Time, tm.Minute);
    Time += ':';
    save2digits(&Time, tm.Second);
  }

  output = "data:(" + Time + '|' + acc + ")\n";

  char* data = new char[output.length() + 1];
  output.toCharArray(data, output.length() + 1);

  Serial.write(data);

  delete[] data;
  data = 0;
  
  wait(1);

}
