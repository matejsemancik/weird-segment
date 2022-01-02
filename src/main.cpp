#include <Arduino.h>
#include <WeirdSegment.h>

#define BTN1 D3
#define BTN2 D4

WeirdSegment display;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
  };

  display.begin(D0, D1, D2, D5, D6, D7);

  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);

  display.displayNumber(2000);
  delay(2000);
}

void loop() {
  display.activateSegment(display.getSegment(1, 0));
  delay(100);
  display.activateSegment(display.getSegment(2, 0));
  delay(100);
  display.activateSegment(display.getSegment(3, 0));
  delay(100);
  display.activateSegment(display.getSegment(2, 0));
  delay(100);
  display.activateSegment(display.getDecimalPointSegment());
  delay(100);
}