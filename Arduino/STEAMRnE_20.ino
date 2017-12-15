
#include <Adafruit_MLX90614.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DS3231.h>
#include <I2Cdev.h>
#include <MPU6050.h>

#define OLED_RESET 4
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16  
#define PROCESSING_VISUALIZER 1
#define SERIAL_PLOTTER 2

Adafruit_SSD1306 display(OLED_RESET);
DS3231 rtc(SDA, SCL);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
MPU6050 mpu;

static const unsigned char PROGMEM logo16_glcd_bmp[] = {
  B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
};

int pulsePin = 2;
int blinkPin = 13, fadePin = 5;
int fadeRate = 0;
int potdata;
const int pot = 1;

volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded!
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat".
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

static int outputType = SERIAL_PLOTTER;

int16_t ax,ay, az, gx, gy, gz;
int vx, vy, vz, fx, fy, fz;

#if (SSD1306_LCDHEIGHT != 64)
#error ("Height incorrect, Please fix Adafruit_SSD1306.h!");
#endif

#include "AllSerialHandling.h"
#include "Interrupt.h"
#include "stringcontrol.h"

void ledFadeToBeat();
void timedisplay();
void sense();

void setup() {
  // 1. time(rtc)
  rtc.begin();
  
  // 2. pulse
  pinMode(blinkPin, OUTPUT);
  pinMode(fadePin, OUTPUT);
  Serial.begin(9600);
  interruptSetup();
  
  // 3. temp(mlx)
  mlx.begin();
  
  // 4. OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(1000);
  display.clearDisplay();
  
  //5. Acc.
  Wire.begin();
  mpu.initialize();
  if(!mpu.testConnection()) {
    while(1);
  }
}

void loop() {
  //serialOutput();
  if (QS == true) {
    fadeRate = 255;
    serialOutputWhenBeatHappens();
    QS = false;
  }
  ledFadeToBeat();
  
  display.clearDisplay();
  potdata = analogRead(pot);

  if(potdata <= 512) {
    timedisplay();
  } else {
    sense();
  }
  
  //Acc.
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  fx = vx = (gx+300)/200+2;
  fx = vy = -(gz-100)/200+2;
  fx = vz = (gz-600)/200;
  
  //Serial control
  Serial.print("\""); Serial.print(rtc.getDateStr());
  Serial.print("\", \""); Serial.print(rtc.getTimeStr());
  Serial.print("\", \""); Serial.print(mlx.readAmbientTempC());
  Serial.print("\", \""); Serial.print(mlx.readObjectTempC());
  Serial.print("\", \""); Serial.print(BPM);
  Serial.print("\", \""); Serial.print(fx);
  Serial.print("\", \""); Serial.print(fy);
  Serial.print("\", \""); Serial.print(fz);
  Serial.println("\"");
  
  // time correcting
  char* timeNow = new char[strlen(rtc.getTimeStr())];
  char* timeBefore = new char[strlen(rtc.getTimeStr())];
  
  strcpy(timeBefore, rtc.getTimeStr());
  
  for(;;) {
    strcpy(timeNow, rtc.getTimeStr());
    if(!strcmp(timeBefore, timeNow))
      break;
  }
  delete[] timeNow;
  delete[] timeBefore;
  
  timeNow = timeBefore = 0;
}

void ledFadeToBeat() {
  fadeRate -= 15;
  fadeRate = constrain(fadeRate, 0, 255);
  analogWrite(fadePin, fadeRate);
}

void timedisplay() {
  display.setTextSize(2);
  display.setTextColor(WHITE);

  display.setCursor(5,0);
  display.println("TIME");
  display.setCursor(0,20);
  display.print(rtc.getDateStr());
  display.print(" ");
  display.println(rtc.getTimeStr());

  display.display();
}

void sense() {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  
  display.setCursor(10,0);
  display.print("Amb:"); display.println(mlx.readAmbientTempC());
  display.setCursor(10,20);
  display.print("Obj:"); display.println(mlx.readObjectTempC());
  display.setCursor(10,40);
  display.print("Pul:"); display.println(BPM);
  
  display.display();
}
