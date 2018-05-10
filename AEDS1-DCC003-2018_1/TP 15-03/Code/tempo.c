#include <stdio.h>

int getHoursFromSec(int sec);
int getMinutesFromSec(int sec);
int getRemainingSeconds(int sec);

int main(void) {
  int sec1 = 5498;
  int sec2 = 1478;
  int sec3 = 48590;

  printf("%ih %im %is\n", getHoursFromSec(sec1), getMinutesFromSec(sec1), getRemainingSeconds(sec1));

  printf("%ih %im %is\n", getHoursFromSec(sec2), getMinutesFromSec(sec2), getRemainingSeconds(sec2));

  printf("%ih %im %is\n", getHoursFromSec(sec3), getMinutesFromSec(sec3), getRemainingSeconds(sec3));
}

int getHoursFromSec(int sec){
  return sec / 3600;
}

int getMinutesFromSec(int sec){
  return sec / 60 - getHoursFromSec(sec) * 60;
}

int getRemainingSeconds(int sec){
  return sec % 60;
}
