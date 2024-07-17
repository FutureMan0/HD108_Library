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
}

void loop() {
  strip.setPixelColorHSV(0, 0, 255, 255);  // Set first LED to Red
  strip.setPixelColorHSV(1, 120, 255, 255);  // Set second LED to Green
  strip.setPixelColorHSV(2, 240, 255, 255);  // Set third LED to Blue
  strip.show();
}
