/*
 * ROLE_CENTRAL
 */

#include <Wire.h>
#include <I2Cdev.h>

#include <TimeLib.h>
#include <DS1307RTC.h>

#include "define.h"

tmElements_t tm;

void setup() {
  Serial.begin(115200);
  while(!Serial);

  Wire.begin();
}

void loop() {
  String Time = "N/A";
  String Date = "N/A";

  if(RTC.read(tm)) {
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

  String output_p = "Time:(" + Date + '|' + Time + ")\n";

  char* data = new char[output_p.length() + 1];
  output_p.toCharArray(data, output_p.length() + 1);

  Serial.write(data);

  delete[] data;
  data = 0;

  delay(1000);

  String x = "N/A", y = "N/A", z = "N/A";

  if(Serial.available() > 0) {
    delay(1000);
    Serial.println(Serial.read());
    if(Serial.find("data:(")) {
      x = Serial.readStringUntil('|');
      y = Serial.readStringUntil('|');
      z = Serial.readStringUntil(')');
    }
  }

  String output_r = "\"" + x + "\", \"" + y + "\", \"" + z + "\"";
  Serial.println(output_r);
  
   // time correcting
  /*
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
  */
}
