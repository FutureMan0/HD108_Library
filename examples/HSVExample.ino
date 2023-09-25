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
