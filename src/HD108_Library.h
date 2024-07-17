/*
 * 🌟 HD108 LED Library 🌟
 * Developed by Luis Blüml
 * This library is free for commercial use.
 * Unleash the power of vibrant LEDs in your projects!
 * For more information, visit the GitHub repository: https://github.com/FutureMan0/HD108_Library
 */

#ifndef HD108_Library_h
#define HD108_Library_h

#include <Arduino.h>
#include <SPI.h>

class HD108 {
  public:
    HD108(uint16_t numPixels);
    void begin();
    void setBrightness(uint8_t r, uint8_t g, uint8_t b);
    void setPixelColor8Bit(uint16_t pixel, uint8_t r, uint8_t g, uint8_t b);
    void setPixelColor16Bit(uint16_t pixel, uint16_t r, uint16_t g, uint16_t b);
    void setPixelColorHex(uint16_t pixel, uint32_t color);
    void clear();
    void show();
    void setSPISpeed(uint32_t speed);
    // Gamma correction
    void applyGammaCorrection(float gamma);

    // Scheduling and timing
    void showAfterDelay(unsigned long delayMillis);
    
    // Rotation and shifting
    void rotateLeft(uint16_t positions);
    void rotateRight(uint16_t positions);
    
    // Energy management
    void enableLowPower();
    void disableLowPower();
    
    // HSV color model
    void setPixelColorHSV(uint16_t pixel, uint16_t h, uint8_t s, uint8_t v);

    uint16_t numPixels() const { return _numPixels; }  // Added method

  private:
    uint16_t _numPixels;
    uint16_t *_red;
    uint16_t *_green;
    uint16_t *_blue;
    uint16_t _global;
    uint32_t _spiSpeed;
    bool _lowPowerMode;
    uint16_t *_redBackup;
    uint16_t *_greenBackup;
    uint16_t *_blueBackup;


    public:
    ~HD108();  // Destructor to free allocated memory
};


#endif
