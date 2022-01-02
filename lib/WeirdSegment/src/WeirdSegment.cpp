#include "WeirdSegment.h"

WeirdSegment::WeirdSegment() {}

void WeirdSegment::begin(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4,
                         uint8_t pin5, uint8_t pin6) {

  pin_mapping[0] = pin1;
  pin_mapping[1] = pin2;
  pin_mapping[2] = pin3;
  pin_mapping[3] = pin4;
  pin_mapping[4] = pin5;
  pin_mapping[5] = pin6;

  clear();
}

Segment WeirdSegment::getSegment(uint8_t digit, uint8_t segment) {
  uint8_t index_offset;
  switch (digit) {
  case 0:
    index_offset = 0;
    break;
  case 1:
    index_offset = 2;
    break;
  case 2:
    index_offset = 9;
    break;
  case 3:
    index_offset = 17;
    break;
  default:
    index_offset = 0;
    break;
  }

  return all_segments[index_offset + segment];
}

Segment WeirdSegment::getDecimalPointSegment() { return all_segments[16]; }

void WeirdSegment::activateSegment(Segment segment) {
  clear();

  uint8_t anode_arduino_pin = getAnodePin(segment);
  uint8_t cathode_arduino_pin = getCathodePin(segment);

  pinMode(anode_arduino_pin, OUTPUT);
  pinMode(cathode_arduino_pin, OUTPUT);
  digitalWrite(anode_arduino_pin, HIGH);
  digitalWrite(cathode_arduino_pin, LOW);
}

void WeirdSegment::displayNumber(uint16_t number) {
  clear();
  if (number > 1999) {
      activateSegment(getSegment(3, 6));
      return;
  }
}

void WeirdSegment::clear() {
  for (uint8_t i = 0; i < DISPLAY_PIN_COUNT; i++) {
    digitalWrite(pin_mapping[i], LOW);
    pinMode(pin_mapping[i], INPUT);
  }
}

uint8_t WeirdSegment::getAnodePin(Segment segment) {
  return pin_mapping[segment.anode_display_pin - 1];
}

uint8_t WeirdSegment::getCathodePin(Segment segment) {
  return pin_mapping[segment.cathode_display_pin - 1];
}