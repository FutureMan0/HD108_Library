#include <HD108_Library.h>

HD108 strip(60);

void setup() {
  strip.begin();
  strip.setBrightness(31, 31, 31);
  strip.setPixelColor8Bit(0, 255, 0, 0);  // Set first LED to Red
  strip.setPixelColor8Bit(1, 0, 255, 0);  // Set second LED to Green
  strip.setPixelColor8Bit(2, 0, 0, 255);  // Set third LED to Blue
  strip.applyGammaCorrection(2.2);  // Apply Gamma Correction
  strip.show();
}

void loop() {
}
