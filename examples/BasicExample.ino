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
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor8Bit(i, 255, 0, 0); // Red
    strip.show();
    delay(50);
    strip.clear();
  }
}
