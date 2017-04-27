#ifndef FOOTYTARGET_H
#define FOOTYTARGET_H

#include <digitalWriteFast.h>
#include <arduino.h>

#define DEBOUNCE_MASK 0x00C2
#define NUM_LEDS 12
#define LED_CYCLE_RATE 20
#define LED_MAX 10
#define LED_HIT_DURATION 400

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
    int _dataPin;
    int _clockPin;
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
};

#endif
