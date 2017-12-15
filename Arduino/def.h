#ifndef DEF_H
#define DEF_H

void p(String _txt) {
  if(DEBUG) {
    Serial.print(_txt);
  }
  return;
}

void wait(unsigned int sec) {
  delay(sec * 1000);
}

void save2digits(String *str, int number) {
  if(number >= 0 && number < 10) {
    *str += '0';
  }
  *str += String(number);
}

#endif
