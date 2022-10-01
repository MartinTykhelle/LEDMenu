#ifndef LEDMenu_h
#define LEDMenu_h
#define arrayLength 20
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include <RotaryEncoder.h>

class LEDMenu
{
  public:
    LEDMenu(uint8_t displayAddress
                        ,uint8_t _encPinA
                        ,uint8_t _encPinB
                        ,uint8_t _encButton);
    void addMenu(char menuItemName[]);
    void addVal(char menuItemVal[]);
    void init();
    void poll();
    uint8_t getVal(int menuItemIdx);
    uint8_t getVal(char menuItemName[]);
  private:
    Adafruit_AlphaNum4 _alpha4;
    RotaryEncoder *_encoder = nullptr;
    uint8_t _displayAddress;
    uint8_t _encPinA;
    uint8_t _encPinB;
    uint8_t _encButton;
    uint8_t _menuCnt;
    uint8_t _buttonState;
    uint8_t _menuPosition;
    uint8_t _subMenuPosition;
    uint8_t _menuValCnt[arrayLength];
    uint8_t _menuValues[arrayLength];
    char* _menuVal[arrayLength][arrayLength];
    char* _menu[arrayLength];
};

#endif