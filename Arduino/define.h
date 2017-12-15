#ifndef DEFINE_H
#define DEFINE_H

const int BUTTON_PIN;

struct DATA {
  String CT;
  int acc[3];
  int real[3];
  // void reserved[2];
  bool button;
};

void delay_sec(unsigned int seconds) {
  delay(seconds * 1000);
}

void save2digits(String* str, int number) {
  if (number >= 0 && number < 10) {
    *str += '0';
  }
  *str += number;
}

#endif
