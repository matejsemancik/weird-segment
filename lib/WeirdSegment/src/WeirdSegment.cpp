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

void WeirdSegment::writeDecimalPoint() { segment_buffer[16] = true; }

void WeirdSegment::writeSegment(uint8_t digit, uint8_t segment) {
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

  segment_buffer[index_offset + segment] = true;
}

void WeirdSegment::writeNumber(uint16_t number) {
  if (number > 1999) {
    writeSegment(3, 6);
    return;
  }

  uint8_t lastNumber = number % 10;
  for (uint8_t i = 0; i < all_digits[lastNumber].segment_count; i++) {
    uint8_t seg_index = all_digits[lastNumber].segment_indices[i];
    segment_buffer[seg_index + 17] = true;
  }
}

void WeirdSegment::update() {
  for (uint8_t i = 0; i < DISPLAY_SEGMENT_COUNT; i++) {
    Segment segment = all_segments[i];
    uint8_t anode_arduino_pin = getAnodePin(segment);
    uint8_t cathode_arduino_pin = getCathodePin(segment);

    for (uint8_t n = 0; n < DISPLAY_PIN_COUNT; n++) {
      pinMode(pin_mapping[n], INPUT);
      digitalWrite(pin_mapping[n], LOW);
    }

    if (segment_buffer[i] == true) {
      pinMode(anode_arduino_pin, OUTPUT);
      pinMode(cathode_arduino_pin, OUTPUT);
      digitalWrite(anode_arduino_pin, HIGH);
      digitalWrite(cathode_arduino_pin, LOW);
    }
  }
}

void WeirdSegment::clear() {
  for (uint8_t i = 0; i < DISPLAY_SEGMENT_COUNT; i++) {
    segment_buffer[i] = false;
  }

  update();
}

uint8_t WeirdSegment::getAnodePin(Segment segment) {
  return pin_mapping[segment.anode_display_pin - 1];
}

uint8_t WeirdSegment::getCathodePin(Segment segment) {
  return pin_mapping[segment.cathode_display_pin - 1];
}