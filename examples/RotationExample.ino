/*
 * 🌟 HD108 LED Library 🌟
 * Developed by Luis Blüml
 * This library is free for commercial use.
 * Unleash the power of vibrant LEDs in your projects!
 * For more information, visit the GitHub repository: https://github.com/FutureMan0/HD108_Library
 */

#include <HD108_Library.h>

HD108 strip(60);

void setup() {
  strip.begin();
  strip.setBrightness(31, 31, 31);
  strip.setPixelColor8Bit(0, 255, 0, 0);
  strip.setPixelColor8Bit(1, 0, 255, 0);
  strip.setPixelColor8Bit(2, 0, 0, 255);
  strip.show();
}

void loop() {
  strip.rotateLeft(1);  // Rotate all pixels to the left by 1 position
  strip.show();
  delay(500);
  strip.rotateRight(1);  // Rotate all pixels to the right by 1 position
  strip.show();
  delay(500);
}
