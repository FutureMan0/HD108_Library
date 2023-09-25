#include <HD108_Library.h>

HD108 strip(252);

void setup() {
  strip.begin();
  strip.setBrightness(31, 31, 31); // Max brightness
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor8Bit(i, 255, 255, 255); // White
  }
  strip.show();
}

void loop() {
}
