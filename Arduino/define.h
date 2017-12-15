#ifndef DEFINE_H
#define DEFINE_H

void save2digits(String *str, int number) {
  if (number >= 0 && number < 10) {
    *str += '0';
  }
  *str += String(number);
}

#endif
