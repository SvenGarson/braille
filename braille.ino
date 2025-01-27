// Dependencies
#include <stdint.h>
#include <string.h>

// Specify braille character designs
const char * const P_DESIGN_BRAILLE_A = "X."
                                        ".."
                                        "..";

const char * const P_DESIGN_BRAILLE_B = "X."
                                        "X."
                                        "..";

const char * const P_DESIGN_BRAILLE_C = "XX"
                                        ".."
                                        "..";

// Braille design validation
const int BRAILLE_DESIGN_WIDTH = 2;
const int BRAILLE_DESIGN_HEIGHT = 3;
const int BRAILLE_DESIGN_LENGTH = BRAILLE_DESIGN_WIDTH * BRAILLE_DESIGN_HEIGHT;

// Braille character set
struct braille_glyph_s {
  bool registered;
  const char * p_design;
};
const int SUPPORTED_ASCII_CHAR_COUNT = 128;
struct braille_glyph_s braille_glyphs[SUPPORTED_ASCII_CHAR_COUNT];

bool braille_character_supported(char character)
{
  const int ASCII_CODE = (int)character;
  return (
    ASCII_CODE < 0 ||
    ASCII_CODE >= SUPPORTED_ASCII_CHAR_COUNT
  ) ? false : true;
}

bool braille_character_not_supported(char character)
{
  return !braille_character_supported(character);
}

bool braille_design_valid(const char * p_braille_design)
{
  if (NULL == p_braille_design) return false;
  
  return strlen(p_braille_design) == BRAILLE_DESIGN_LENGTH;
}

bool braille_design_in_valid(const char * p_braille_design)
{
  return !braille_design_valid(p_braille_design);
}

bool register_braille_glyph_with_design(char character, const char * p_braille_design)
{
  if (
    braille_character_not_supported(character) ||
    braille_design_in_valid(p_braille_design)
  ) return false;

  const int ASCII_CODE = (int)character;
  struct braille_glyph_s * p_glyph = braille_glyphs + ASCII_CODE;
  p_glyph->registered = true;
  p_glyph->p_design = p_braille_design;

  return true;
}

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

// Entry point
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

  // Initialize braille character glyphs as un-registered
  for (int i_glyph = 0; i_glyph < SUPPORTED_ASCII_CHAR_COUNT; ++i_glyph)
  {
    struct braille_glyph_s * const p_glyph = braille_glyphs + i_glyph;
    p_glyph->registered = false;
    p_glyph->p_design = NULL;
  }

  // Register and configure braille character glyphs$
  register_braille_glyph_with_design('A', P_DESIGN_BRAILLE_A);
  register_braille_glyph_with_design('B', P_DESIGN_BRAILLE_B);
  register_braille_glyph_with_design('C', P_DESIGN_BRAILLE_C);

  // List registration result
  Serial.print("\n\nRegistered glyphs:");
  char reg_description[256];
  int registered_glyph_count = 0;
  for (int i_glyph_ascii = 0; i_glyph_ascii < SUPPORTED_ASCII_CHAR_COUNT; ++i_glyph_ascii)
  {
    const struct braille_glyph_s * const P_GLYPH = braille_glyphs + i_glyph_ascii;

    // Ignore un-registered glyphs
    if (!P_GLYPH->registered) continue;

    // List registration
    snprintf(
      reg_description,
      sizeof(reg_description),
      "\n     Ascii: [%-4d] registered with design [%-s]",
      (int)i_glyph_ascii,
      P_GLYPH->p_design
    );
    Serial.print(reg_description);

    // Count
    ++registered_glyph_count;
  }

  // Statistics
  Serial.print("\n     Registered ");
  Serial.print(registered_glyph_count);
  Serial.print(" out of ");
  Serial.print(SUPPORTED_ASCII_CHAR_COUNT);
  Serial.print(" ASCII character glyphs !");
}

// Loop
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
