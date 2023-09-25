
# HD108 LED Library

Diese Bibliothek ermöglicht die Steuerung des HD108 LED-Chipsatzes.

## Installation

1. Laden Sie diese Bibliothek herunter.
2. Fügen Sie sie Ihrem Arduino- oder PlatformIO-Projekt hinzu.

## Beispiel

```cpp
#include <HD108_Library.h>

HD108 strip(252);
uint16_t colorIndex = 0;

void setup() {
  strip.begin();
  strip.setBrightness(31, 31, 31); // Max brightness
  strip.setSPISpeed(4000000); // ~4799999 Bits
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  uint8_t r, g, b;
  if (WheelPos < 85) {
    r = 255 - WheelPos * 3;
    g = 0;
    b = WheelPos * 3;
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    r = 0;
    g = WheelPos * 3;
    b = 255 - WheelPos * 3;
  } else {
    WheelPos -= 170;
    r = WheelPos * 3;
    g = 255 - WheelPos * 3;
    b = 0;
  }
  return (r << 16) | (g << 8) | b;
}

void loop() {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    uint16_t pos = (i + colorIndex) % 256;
    uint32_t color = Wheel(pos);
    uint8_t r = (color & 0xFF0000) >> 16;
    uint8_t g = (color & 0x00FF00) >> 8;
    uint8_t b = (color & 0x0000FF);
    strip.setPixelColor8Bit(i, r, g, b);
  }
  strip.show();
  colorIndex = (colorIndex + 1) % 256;
}

```

## Autor

- Luis Blüml

## Lizenz

Siehe `LICENSE` Datei für mehr Informationen.
