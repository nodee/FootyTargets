#ifndef FOOTYTARGET_H
#define FOOTYTARGET_H

#include <arduino.h>
#include <SPI.h>
#include <Adafruit_WS2801.h>

#define DEBOUNCE_MASK 0x00C2

#define LED_CYCLE_RATE 3
#define LED_MAX 24
#define LED_HIT_DURATION 200

class FTarget{
  public:
    FTarget(int knockPin, int dataPin, int clockPin, int buzzerPin);
    void enable(void);
    void disable(void);
    void update(void);
    int getScore(void);
    void resetScore(void);
    void updateLED(int mode);
  private:
    int _knockPin;
    int _buzzerPin;

    int _targetState;
    int _targetStateCounter;

    int _score;
    int _debounceBuffer;

    int _buzzerCounter;

    int _ledState;
    int _ledCounter;
    int _ledPosition;
    long _ledBuffer[LED_MAX];

    Adafruit_WS2801 strip;
};

#endif
