
# HD108 LED Library

Welcome to the HD108 LED Library! This powerful and easy-to-use library allows you to control the HD108 LED chipset, bringing vibrant colors and stunning light effects to your projects.

## Installation

1. **Download the Library**: Get the latest version of the HD108 LED Library from [here](https://github.com/FutureMan0/HD108_Library/releases/download/first/HD108_Library.zip).
2. **Add to Your Project**:
   - **Arduino**: Place the downloaded library in the `libraries` folder of your Arduino sketchbook.
   - **PlatformIO**: Add the library to your `lib` directory or use the Library Manager to include it in your project.

## Example

Here’s a simple example to get you started with the HD108 LED Library:

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

## Author

- Luis Blüml

## License

See the `LICENSE` file for more information.

---

Finding the right library for your project can be a bit overwhelming. Here are some tips to discover great libraries:

1. **GitHub**: Search for repositories and filter by stars to find popular and well-maintained libraries.
2. **Arduino Library Manager**: Use the Library Manager in the Arduino IDE to browse and install libraries directly.
3. **PlatformIO Library Registry**: Explore the PlatformIO registry to find libraries tailored for your development environment.
4. **Community Forums and Blogs**: Engage with online communities and read blogs to get recommendations and insights.

## Download

You can download the HD108 LED Library by clicking the link below:

[Download HD108 LED Library](https://github.com/FutureMan0/HD108_Library/releases/download/first/HD108_Library.zip)
