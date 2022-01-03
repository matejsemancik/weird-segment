#ifndef MATSEM_WEIRD_SEGMENT_H
#define MATSEM_WEIRD_SEGMENT

#include <stdlib.h>

#define DISPLAY_SEGMENT_COUNT 24
#define DISPLAY_PIN_COUNT 6

/**
 * @brief Represents a single segment on display.
 * Each segment is defined by it's anode and cathode pin.
 * The display hardware wiring ensures that each segment on display is
 * represented by unique combination of these two.
 */
struct Segment {
  uint8_t anode_display_pin;
  uint8_t cathode_display_pin;
};

/**
 * @brief Represents a single character display-able on a single display digit.
 * @param segment_count Number of display segments used to display the
 * character.
 * @param segment_indices 0-based indices of digit segments used to display the
 * character (0-6 -> A-G).
 */
struct Digit {
  uint8_t segment_count;
  uint8_t segment_indices[7];
};

/**
 * @brief Weird 7-segment display driver.
 * The display has 6 hardware pins and 188.8 form-factor.
 */
class WeirdSegment {
public:
  WeirdSegment();

  /**
   * @brief Anode to cathode mappings for each display segment.
   */
  Segment all_segments[DISPLAY_SEGMENT_COUNT] = {
      {4, 3}, {5, 3},                                         // Digit 1
      {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {3, 2}, {4, 2}, // Digit 2
      {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {5, 2}, {6, 2}, // Digit 3
      {6, 3},                                                 // Dp
      {2, 3}, {2, 4}, {2, 5}, {2, 6}, {3, 4}, {3, 5}, {3, 6}  // Digit 4
  };

  /**
   * @brief Configures the display pin mappings.
   *
   * @param pin1 Display pin 1.
   * @param pin2 Display pin 2.
   * @param pin3 Display pin 3.
   * @param pin4 Display pin 4.
   * @param pin5 Display pin 5.
   * @param pin6 Display pin 6.
   */
  void begin(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4,
             uint8_t pin5, uint8_t pin6);

  /**
   * @brief Activates decimal point segment on display.
   */
  void writeDecimalPoint();

  /**
   * @brief Activates a single LED segment on display addressed by display digit
   * and it's segment index.
   * @param digit 0-based index of display digit, between 0-3.
   *
   */
  void writeSegment(uint8_t digit, uint8_t segment);

  /**
   * @brief Displays the number on display.
   *
   * @param number Number in range 0..1999 (the displayable range).
   */
  void writeNumber(uint16_t number);

  /**
   * @brief Enables/disables display output.
   */
  void setOutputEnabled(bool outputEnabled);

  /**
   * @brief Returns if display output is enabled.
   * 
   * @return true If display output is enabled.
   * @return false If display output is disabled.
   */
  bool isOutputEnabled();

  /**
   * @brief Refreshes the display.
   * This needs to be ran as frequently as possible.
   * The driver turns on active display segments one by one (due to the display
   * wiring).
   */
  void update();

  /**
   * @brief Clears the display.
   */
  void clear();

private:
  /**
   * @brief Display character set.
   */
  Digit all_digits[10] = {
      {.segment_count = 6, .segment_indices = {0, 1, 2, 3, 4, 5}},    // 0
      {.segment_count = 2, .segment_indices = {1, 2}},                // 1
      {.segment_count = 5, .segment_indices = {0, 1, 3, 4, 6}},       // 2
      {.segment_count = 5, .segment_indices = {0, 1, 2, 3, 6}},       // 3
      {.segment_count = 4, .segment_indices = {1, 2, 5, 6}},          // 4
      {.segment_count = 5, .segment_indices = {0, 2, 3, 5, 6}},       // 5
      {.segment_count = 6, .segment_indices = {0, 2, 3, 4, 5, 6}},    // 6
      {.segment_count = 3, .segment_indices = {0, 1, 2}},             // 7
      {.segment_count = 7, .segment_indices = {0, 1, 2, 3, 4, 5, 6}}, // 8
      {.segment_count = 6, .segment_indices = {0, 1, 2, 3, 5, 6}},    // 9
  };

  /**
   * @brief Display pin to Arduino pin mapping, initialized by the begin()
   * method.
   */
  uint8_t pin_mapping[DISPLAY_PIN_COUNT];

  /**
   * @brief Boolean map of currently active display segments.
   * Segments marked as active are being currently displayed by the update
   * method.
   */
  bool segment_buffer[DISPLAY_SEGMENT_COUNT];

  /**
   * @brief Whether display output is enabled.
   */
  bool is_enabled;

  /**
   * @brief Get the Anode Pin of provided Segment
   */
  uint8_t getAnodePin(Segment segment);

  /**
   * @brief Get the Cathode pin of provided Segment.
   */
  uint8_t getCathodePin(Segment segment);
};

#endif