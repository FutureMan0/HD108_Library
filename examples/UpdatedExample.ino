/*
 * 🌟 HD108 LED Library 🌟
 * Developed by Luis Blüml
 * This library is free for commercial use.
 * Unleash the power of vibrant LEDs in your projects!
 * For more information, visit the GitHub repository: https://github.com/FutureMan0/HD108_Library
 */

#include <HD108_Library.h>

HD108 strip(252);

void setup() {
  strip.begin();
  strip.setBrightness(31, 31, 31); // Max brightness
}

void loop() {
  // Example 1: Setting individual pixel with RGB color
  strip.setColor16Bit(0, 0xFFFF, 0, 0); // Red for first pixel
  strip.show();
  delay(1000);
  strip.clear();

  // Example 2: Setting individual pixel with HEX color (#fcba03)
  strip.setColorHex(0, 0xfcba03);
  strip.show();
  delay(1000);
  strip.clear();

  // Example 3: Setting all pixels to the same color at once
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor16Bit(i, 0xFFFF, 0xFFFF, 0xFFFF); // White
  }
  strip.show();
  delay(1000);
  strip.clear();
}
