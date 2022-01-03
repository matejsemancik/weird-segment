#include <Arduino.h>
#include <OneButton.h>
#include <Ticker.h>
#include <WeirdSegment.h>

/*
Example: Stopwatch.
*/

void onTicker();
void onResetBtnClick();
void onPlayPauseBtnClick();

OneButton btn1(D3, true, true);
OneButton btn2(D4, true, true);
Ticker ticker(onTicker, 500);
WeirdSegment display;

unsigned long counter = 0;
unsigned long counter_offset = 0;
bool is_running = false;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
  };

  display.begin(D0, D1, D2, D5, D6, D7);
  btn1.attachClick(onResetBtnClick);
  btn2.attachClick(onPlayPauseBtnClick);

  display.clear();
  display.writeNumber(0);
  display.update();
}

void loop() {
  if (is_running) {
    counter = millis() - counter_offset;
  }

  display.clear();
  display.writeNumber(counter / 100);
  display.writeDecimalPoint();
  display.update();

  btn1.tick();
  btn2.tick();
  ticker.update();
}

void onResetBtnClick() {
  counter_offset = millis();
  counter = 0;

  if (!is_running) {
    ticker.stop();
    display.setOutputEnabled(true);
  }
}

void onPlayPauseBtnClick() {
  if (!is_running) {
    is_running = true;
    counter_offset = millis() - counter;
    ticker.stop();
    display.setOutputEnabled(true);
  } else {
    is_running = false;
    ticker.start();
  }
}

void onTicker() { display.setOutputEnabled(!display.isOutputEnabled()); }