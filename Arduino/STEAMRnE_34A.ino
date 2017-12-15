
//peripheral

#define OLED_RESET 4
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

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

#include <Wire.h>
#include <I2Cdev.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MPU6050.h>
#include <Adafruit_MLX90614.h>

MPU6050 mpu;
Adafruit_SSD1306 display(OLED_RESET);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#if (SSD1306_LCDHEIGHT != 64)
//#error ("Height incorrect, Please fix Adafruit_SSD1306.h!");
#endif

int16_t ax, ay, az, gx, gy, gz;
int vx, vy, vz, fx, fy, fz;
int amb, obj;
unsigned long timeNow = 0, timeBefore = 0;
int delaysec = 1;
bool state;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);

  Wire.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(1000);
  display.clearDisplay();

  mpu.initialize();
  while (!mpu.testConnection());
}

void loop() {
  // put your main code here, to run repeatedly:
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  fx = vx = (gx + 300) / 200 - 1;
  fy = vy = (gy - 100) / 200 + 1;
  fz = vz = (gz - 600) / 200 + 3;

  amb = mlx.readAmbientTempC();
  obj = mlx.readObjectTempC();

  display.clearDisplay();
  int potdata = analogRead(A0);

  if (potdata < 256 || potdata > 256 + 512) {
    state = true;
  } else {
    state = false;
  }
  
  if (potdata > 512) {
    displayAccData(fx, fy, fz);
  } else {
    //displayTime();
    displayTempData(amb, obj);
  }

  timeNow = millis();
  if (timeNow - timeBefore >= delaysec * 1000) {
    timeBefore = timeNow;
    String output = String(fx) + "," + String(fy) + ',' + String(fz) + ',' + String(amb) + ',' + String(obj) + ',' + String(int(state));
    Serial.println(output);
  }
}

void displayAccData(int x, int y, int z) {
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(10, 0);
  display.print("x:"); display.println(x);
  display.setCursor(10, 10);
  display.print("y:"); display.println(y);
  display.setCursor(10, 20);
  display.print("z:"); display.println(z);

  display.display();
}

void displayTempData(int a, int o) {
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(10, 0);
  display.print("Amb:"); display.println(a);
  display.setCursor(10, 10);
  display.print("Obj:"); display.println(o);

  display.display();
}

