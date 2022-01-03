#include <Arduino.h>
#include <WeirdSegment.h>

#define BTN1 D3
#define BTN2 D4

WeirdSegment display;
uint16_t number = 0;
unsigned long timestamp = 1000;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
  };

  display.begin(D0, D1, D2, D5, D6, D7);

  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
}

void loop() {
  if (millis() > timestamp) {
    timestamp += 50;
    number++;
    display.clear();
    display.writeNumber(number);
    display.writeDecimalPoint();
  }

  display.update();
}