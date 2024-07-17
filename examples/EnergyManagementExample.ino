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
  strip.show();
}

void loop() {
  delay(5000);  // Wait for 5 seconds
  strip.enableLowPower();  // Enable low-power mode
  delay(5000);  // Wait for 5 seconds
  strip.disableLowPower();  // Disable low-power mode
  strip.show();
}
