
#include "HD108_Library.h"

HD108::HD108(uint16_t numPixels) : _numPixels(numPixels), _spiSpeed(1E6), _lowPowerMode(false) {
  _red = new uint16_t[_numPixels]();
  _green = new uint16_t[_numPixels]();
  _blue = new uint16_t[_numPixels]();
}

// Destructor to free dynamically allocated memory
HD108::~HD108() {
  delete[] _red;
  delete[] _green;
  delete[] _blue;
}

void HD108::begin() {
  SPI.begin();
  _global = 0xFFFF; // Default: Max brightness for R, G, B
}

void HD108::setBrightness(uint8_t r, uint8_t g, uint8_t b) {
  _global = (1 << 15) | (r << 10) | (g << 5) | b;
}

// Set color using 8-bit RGB values
void HD108::setPixelColor8Bit(uint16_t pixel, uint8_t r, uint8_t g, uint8_t b) {
  if (pixel < _numPixels) {
    _red[pixel] = r << 8 | r;
    _green[pixel] = g << 8 | g;
    _blue[pixel] = b << 8 | b;
  }
}

// Set color using 16-bit RGB values
void HD108::setPixelColor16Bit(uint16_t pixel, uint16_t r, uint16_t g, uint16_t b) {
  if (pixel < _numPixels) {
    _red[pixel] = r;
    _green[pixel] = g;
    _blue[pixel] = b;
  }
}

void HD108::setPixelColorHex(uint16_t pixel, uint32_t color) {
  uint16_t r = (color & 0xFF0000) >> 8;
  uint16_t g = (color & 0x00FF00);
  uint16_t b = (color & 0x0000FF) << 8;
  setPixelColor16Bit(pixel, r, g, b);
}

void HD108::clear() {
  for (uint16_t i = 0; i < _numPixels; i++) {
    _red[i] = 0;
    _green[i] = 0;
    _blue[i] = 0;
  }
}

void HD108::show() {
  SPI.beginTransaction(SPISettings(_spiSpeed, MSBFIRST, SPI_MODE0));

  // Start frame - 64 bits of 0
  SPI.transfer32(0);
  SPI.transfer32(0);

  // LEDs
  for (uint16_t i = 0; i < _numPixels; i++) {
    SPI.transfer16(_global);
    SPI.transfer16(_red[i]);
    SPI.transfer16(_green[i]);
    SPI.transfer16(_blue[i]);
  }

  // End frame - write "1"s equal to at least how many pixels are in the string
  for (int i = 0; i < _numPixels / 16 + 1; i++) { SPI.transfer16(0xFFFF); }

  SPI.endTransaction();
}

void HD108::setSPISpeed(uint32_t speed) {
  _spiSpeed = speed;
}

void HD108::enableLowPower() {
  _redBackup = new uint16_t[_numPixels];
  _greenBackup = new uint16_t[_numPixels];
  _blueBackup = new uint16_t[_numPixels];
  // Backup current LED state
  memcpy(_redBackup, _red, _numPixels * sizeof(uint16_t));
  memcpy(_greenBackup, _green, _numPixels * sizeof(uint16_t));
  memcpy(_blueBackup, _blue, _numPixels * sizeof(uint16_t));
  // Set LEDs to black
  clear();
  show();
  _lowPowerMode = true;
}

void HD108::disableLowPower() {
  // Restore LED state
  memcpy(_red, _redBackup, _numPixels * sizeof(uint16_t));
  memcpy(_green, _greenBackup, _numPixels * sizeof(uint16_t));
  memcpy(_blue, _blueBackup, _numPixels * sizeof(uint16_t));
  // Free backup memory
  delete[] _redBackup;
  delete[] _greenBackup;
  delete[] _blueBackup;
  _lowPowerMode = false;
}

// Apply gamma correction to all pixels
void HD108::applyGammaCorrection(float gamma) {
  for (uint16_t i = 0; i < _numPixels; i++) {
    _red[i] = pow(_red[i] / 65535.0, gamma) * 65535;
    _green[i] = pow(_green[i] / 65535.0, gamma) * 65535;
    _blue[i] = pow(_blue[i] / 65535.0, gamma) * 65535;
  }
}

// Show the strip after a given delay
void HD108::showAfterDelay(unsigned long delayMillis) {
  delay(delayMillis);
  show();
}

// Rotate pixels to the left
void HD108::rotateLeft(uint16_t positions) {
  uint16_t tempRed, tempGreen, tempBlue;
  for (uint16_t j = 0; j < positions; j++) {
    tempRed = _red[0];
    tempGreen = _green[0];
    tempBlue = _blue[0];
    for (uint16_t i = 0; i < _numPixels - 1; i++) {
      _red[i] = _red[i + 1];
      _green[i] = _green[i + 1];
      _blue[i] = _blue[i + 1];
    }
    _red[_numPixels - 1] = tempRed;
    _green[_numPixels - 1] = tempGreen;
    _blue[_numPixels - 1] = tempBlue;
  }
}

// Rotate pixels to the right
void HD108::rotateRight(uint16_t positions) {
  uint16_t tempRed, tempGreen, tempBlue;
  for (uint16_t j = 0; j < positions; j++) {
    tempRed = _red[_numPixels - 1];
    tempGreen = _green[_numPixels - 1];
    tempBlue = _blue[_numPixels - 1];
    for (uint16_t i = _numPixels - 1; i > 0; i--) {
      _red[i] = _red[i - 1];
      _green[i] = _green[i - 1];
      _blue[i] = _blue[i - 1];
    }
    _red[0] = tempRed;
    _green[0] = tempGreen;
    _blue[0] = tempBlue;
  }
}

// Set color using HSV model
void HD108::setPixelColorHSV(uint16_t pixel, uint16_t h, uint8_t s, uint8_t v) {
  uint8_t region, remainder, p, q, t;

  if (s == 0) {
    setPixelColor8Bit(pixel, v, v, v);
    return;
  }

  region = h / 43;
  remainder = (h - (region * 43)) * 6;

  p = (v * (255 - s)) >> 8;
  q = (v * (255 - ((s * remainder) >> 8))) >> 8;
  t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

  switch (region) {
    case 0:
      setPixelColor8Bit(pixel, v, t, p);
      break;
    case 1:
      setPixelColor8Bit(pixel, q, v, p);
      break;
    case 2:
      setPixelColor8Bit(pixel, p, v, t);
      break;
    case 3:
      setPixelColor8Bit(pixel, p, q, v);
      break;
    case 4:
      setPixelColor8Bit(pixel, t, p, v);
      break;
    default:
      setPixelColor8Bit(pixel, v, p, q);
      break;
  }
}
