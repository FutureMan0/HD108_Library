#include <HD108_Library.h>

HD108 strip(60);

void setup() {
  strip.begin();
  strip.setBrightness(31, 31, 31);
}

void loop() {
  strip.setPixelColor8Bit(0, 255, 0, 0);
  strip.showAfterDelay(1000);  // Show strip after 1 second delay
}
