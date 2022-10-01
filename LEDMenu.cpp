#include "LEDMenu.h"
LEDMenu::LEDMenu(uint8_t displayAddress
                         , uint8_t encPinA
                         , uint8_t encPinB
                         , uint8_t encButton)
{
  _displayAddress = displayAddress;
  _encPinA = encPinA;
  _encPinB = encPinB;
  _encButton = encButton;
  _menuCnt = 0;
  _menuPosition = 0;
  _subMenuPosition  = 0;

}

void LEDMenu::init()
{

  _encoder = new RotaryEncoder(_encPinA, _encPinB, RotaryEncoder::LatchMode::FOUR3);

  _alpha4 = Adafruit_AlphaNum4();
  _alpha4.begin(_displayAddress);
  _alpha4.writeDigitAscii(0, 'I');
  _alpha4.writeDigitAscii(1, 'N');
  _alpha4.writeDigitAscii(2, 'I');
  _alpha4.writeDigitAscii(3, 'T');
  _alpha4.writeDisplay();
  pinMode(_encButton, INPUT_PULLUP);
  for (uint8_t i = 0; i < arrayLength; i++) {
    _menuValues[i] = 0;
  }

}
void LEDMenu::addMenu(char menuItemName[]) {
  _menu[_menuCnt] = menuItemName;
  _menuValCnt[_menuCnt] = 0;
  _menuCnt++;
}
void LEDMenu::addVal(char menuItemVal[]) {
  //-1 as _menuCnt is 1 once the first menu item is added
  _menuVal[_menuCnt - 1][_menuValCnt[_menuCnt - 1]] = menuItemVal;
  _menuValCnt[_menuCnt - 1]++;
}

void LEDMenu::print(char string[]){

  _alpha4.writeDigitAscii(0, string[0]);
  _alpha4.writeDigitAscii(1, string[1]);
  _alpha4.writeDigitAscii(2, string[2]);
  _alpha4.writeDigitAscii(3, string[3]);
  _alpha4.writeDisplay();
}


uint8_t LEDMenu::getVal(int menuItemIdx) {

  return _menuValues[menuItemIdx];
}
uint8_t LEDMenu::getVal(char menuItemName[]) {
  for (uint8_t i = 0; i < arrayLength; i++) {
    if (strcmp(_menu[_menuCnt], menuItemName) == 0) {
      return getVal(i);
    }
  }
}
void LEDMenu::poll() {
  static uint8_t pos = 0;

  uint8_t buttonState = digitalRead(_encButton);

  _encoder->tick();
  uint8_t newPos = _encoder->getPosition();

  if (pos != newPos || _buttonState != buttonState) {
    if (newPos < 0) {
      newPos = newPos * -1;
    }
    int8_t dir = (int8_t)_encoder->getDirection();
    Serial.println(dir);
    if (buttonState == LOW) {

      _subMenuPosition = (_subMenuPosition + dir) % _menuValCnt[_menuPosition];
      if (_subMenuPosition == 255) {
        _subMenuPosition = _menuValCnt[_menuPosition] - 1;
      }
      for (uint8_t i = 0; i < 4; i++) {
        _alpha4.writeDigitAscii(i, _menuVal[_menuPosition][_subMenuPosition][i]);
      }

      _menuValues[_menuPosition] = _subMenuPosition;
    }

    else {
      _menuPosition = (_menuPosition + dir) % _menuCnt;
      _subMenuPosition = _menuValues[_menuPosition];
      if (_menuPosition == 255) {
        _menuPosition = _menuCnt - 1;
      }

      for (uint8_t i = 0; i < 4; i++) {
        _alpha4.writeDigitAscii(i, _menu[_menuPosition][i]);
      }

    }

  }

  pos = newPos;

  _buttonState = buttonState;
  _alpha4.writeDisplay();
}