# Braille
## Brainstorming
- [OK] direct rendering bytes to configuration
- [OK] configure braille to LED pins left to right row, top to bottom
- documentation of the code
- text rendering with delay
- simple visual design registration
- design registration validation
- only registered characters are valid
- uppercase and lowercase characters
- overview registered glyphs
> printable chars to start with
   - [A; Z]
   - [a; z]
   - [0; 9] with leading number indicator (multiple characters)
   - punctuation (multiple characters)
> rules to show various things
   - numbers + leading number character
- cleanup implementation into single configuration struct and pass it around

## Library

## Q & A
- How to handle un-supported or un-registered characters ?