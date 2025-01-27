// Dependencies
#include <stdint.h>

// Specify braille character designs
const char * const P_DESIGN_BRAILLE_A = "#."
                                        ".."
                                        "..";

// Specify intuitive braille dot types
enum braille_dot_e {
  BRAILLE_DOT_1,
  BRAILLE_DOT_2,
  BRAILLE_DOT_3,
  BRAILLE_DOT_4,
  BRAILLE_DOT_5,
  BRAILLE_DOT_6,
  BRAILLE_DOT_7,
  BRAILLE_DOT_8,
  BRAILLE_DOT_COUNT
};

// Specify braille dot type to digital arduino pin
int braille_dot_to_arduino_pin[BRAILLE_DOT_COUNT];

// Library: Direct rendering
void render_braille_uint8(uint8_t braille_char)
{
  for (int i_braille_dot = 0; i_braille_dot < BRAILLE_DOT_COUNT; ++i_braille_dot)
  {
    const int PIN = braille_dot_to_arduino_pin[BRAILLE_DOT_8 - i_braille_dot];
    digitalWrite(PIN, bitRead(braille_char, i_braille_dot) ? HIGH : LOW);
  }
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Configure braille dots to arduino pin configuration
  braille_dot_to_arduino_pin[BRAILLE_DOT_1] = 6;
  braille_dot_to_arduino_pin[BRAILLE_DOT_2] = 2;
  braille_dot_to_arduino_pin[BRAILLE_DOT_3] = 9;
  braille_dot_to_arduino_pin[BRAILLE_DOT_4] = 3;
  braille_dot_to_arduino_pin[BRAILLE_DOT_5] = 8;
  braille_dot_to_arduino_pin[BRAILLE_DOT_6] = 7;
  braille_dot_to_arduino_pin[BRAILLE_DOT_7] = 4;
  braille_dot_to_arduino_pin[BRAILLE_DOT_8] = 5;

  // Configure arduino pin modes accordingly
  for (int i_braille_dot = 0; i_braille_dot < BRAILLE_DOT_COUNT; ++i_braille_dot)
  {
    pinMode(braille_dot_to_arduino_pin[i_braille_dot], OUTPUT);
  }

  // Register and configure braille character designs
  Serial.print("\n\nBraille - A: "); Serial.print(P_DESIGN_BRAILLE_A);
}

void loop() {
  // Examples: Direct rendering into configuration
  /*
      Binary: 1100 1100
      Matrix:

          1  1
          0  0
          1  1
          0  0
  */
  render_braille_uint8(0xCC); // 1100 1100
  delay(1000);

  /*
      Binary: 0011 0011
      Matrix:

          1  1
          0  0
          1  1
          0  0
  */
  render_braille_uint8(0x33); // 0011 0011
  delay(1000);

  // Examples: Text . . .
}
