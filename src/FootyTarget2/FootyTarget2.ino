#include <TimerOne.h>
#include <digitalWriteFast.h>

#define DEBOUNCE_MASK 0xC002
#define LED_CYCLE_RATE 3        // LED_CYCLE_RATE * 5ms - Speed of LED ring
#define LED_MAX 24              // Number of LEDs in ring
#define LED_HIT_DURATION 200    // LED_HIT_DURATION * 5ms
enum colours {WHITE = 0xFFFFFFFF, RED = 0x00FF0000};

int activeTarget = 0;
int ledPosition = 0;
long ledBuffer[LED_MAX] = {0};


// Target 0 Vars
int targetStateT0 = 1;
int targetStateCounterT0 = 0;
int scoreT0 = 0;
int debounceBufferT0 = 0;
int ledStateT0 = 0;
int ledCounterT0 = 0;


// Target 1 Vars
int targetStateT1 = 1;
int targetStateCounterT1 = 0;
int scoreT1 = 0;
int debounceBufferT1 = 0;
int ledStateT1 = 0;
int ledCounterT1 = 0;


// Target 2 Vars
int targetStateT2 = 1;
int targetStateCounterT2 = 0;
int scoreT2 = 0;
int debounceBufferT2 = 0;
int ledStateT2 = 0;
int ledCounterT2 = 0;


// Target 3 Vars
int targetStateT3 = 1;
int targetStateCounterT3 = 0;
int scoreT3 = 0;
int debounceBufferT3 = 0;
int ledStateT3 = 0;
int ledCounterT3 = 0;


void setup() {
  // put your setup code here, to run once:

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, INPUT);
  pinMode(5, OUTPUT);

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
  pinMode(9, OUTPUT);

  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);

  //pinMode(2, OUTPUT);
  //pinMode(3, OUTPUT);
  //pinMode(4, INPUT);
  //pinMode(5, OUTPUT);

  Timer1.initialize(5000);
  Timer1.attachInterrupt(targetUpdate);

  //Serial.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
  activeTarget = 0;
  delay(2000);
  activeTarget = 1;
  delay(2000);

}

void targetUpdate() {

  static int lastTarget = 0;

  if (activeTarget != lastTarget) {
    switch (lastTarget) {
      case 0: {
          targetStateCounterT0 = 0;
          targetStateT0 = 0;
          debounceBufferT0 = 0;
          break;
        }
      case 1: {
          targetStateCounterT1 = 0;
          targetStateT1 = 0;
          debounceBufferT1 = 0;
          break;
        }
      case 2: {
          targetStateCounterT2 = 0;
          targetStateT2 = 0;
          debounceBufferT2 = 0;
          break;
        }
      case 3: {
          targetStateCounterT3 = 0;
          targetStateT3 = 0;
          debounceBufferT3 = 0;
          break;
        }
    }
  }
  lastTarget = activeTarget;
  switch (activeTarget) {
    case 0: {
        if (targetStateCounterT0) {
          targetStateCounterT0--;
        }

        switch (targetStateT0) {
          case 0: {
              updateLED(0);
              digitalWriteFast(5, LOW);
              break;
            }
          case 1: {
              updateLED(1);
              digitalWriteFast(5, LOW);
              debounceBufferT0 <<= 1;
              if (digitalReadFast(4)) {
                debounceBufferT0 |= 1;                              // detect current pin state. add current state to buffer.
              }
              if ((debounceBufferT0 & 0xC002) == DEBOUNCE_MASK) {  // mask middle bits and compare to the mask - 11000011 = detected.
                scoreT0++;                                         // detected a hit, increase the score and
                targetStateT0 = 2;
                targetStateCounterT0 = LED_HIT_DURATION;           // move to the 'Hit' state.
                debounceBufferT0 = 0;
              }
              break;
            }
          case 2: {
              updateLED(2);
              digitalWriteFast(5, HIGH);                                  // Active - Hit
              if (!targetStateCounterT0) {
                targetStateT0 = 1;
                digitalWriteFast(5, LOW);
              }
            }
            break;
        }
        break;
      }
    case 1: {
        if (targetStateCounterT1) {
          targetStateCounterT1--;
        }

        switch (targetStateT1) {
          case 0: {
              updateLED(0);
              digitalWriteFast(5, LOW);
              break;
            }
          case 1: {
              updateLED(1);
              digitalWriteFast(5, LOW);
              debounceBufferT1 <<= 1;
              if (digitalReadFast(4)) {
                debounceBufferT1 |= 1;                              // detect current pin state. add current state to buffer.
              }
              if ((debounceBufferT1 & 0xC002) == DEBOUNCE_MASK) {  // mask middle bits and compare to the mask - 11000011 = detected.
                scoreT1++;                                         // detected a hit, increase the score and
                targetStateT1 = 2;
                targetStateCounterT1 = LED_HIT_DURATION;           // move to the 'Hit' state.
                debounceBufferT1 = 0;
              }
              break;
            }
          case 2: {
              updateLED(2);
              digitalWriteFast(5, HIGH);                                  // Active - Hit
              if (!targetStateCounterT1) {
                targetStateT1 = 1;
                digitalWriteFast(5, LOW);
              }
            }
            break;
        }
        break;
      }
    case 2: {
        if (targetStateCounterT2) {
          targetStateCounterT2--;
        }

        switch (targetStateT2) {
          case 0: {
              updateLED(0);
              digitalWriteFast(5, LOW);
              break;
            }
          case 1: {
              updateLED(1);
              digitalWriteFast(5, LOW);
              debounceBufferT2 <<= 1;
              if (digitalReadFast(4)) {
                debounceBufferT2 |= 1;                              // detect current pin state. add current state to buffer.
              }
              if ((debounceBufferT2 & 0xC002) == DEBOUNCE_MASK) {  // mask middle bits and compare to the mask - 11000011 = detected.
                scoreT2++;                                         // detected a hit, increase the score and
                targetStateT2 = 2;
                targetStateCounterT2 = LED_HIT_DURATION;           // move to the 'Hit' state.
                debounceBufferT2 = 0;
              }
              break;
            }
          case 2: {
              updateLED(2);
              digitalWriteFast(5, HIGH);                                  // Active - Hit
              if (!targetStateCounterT2) {
                targetStateT2 = 1;
                digitalWriteFast(5, LOW);
              }
            }
            break;
        }
        break;
      }
    case 3: {
        if (targetStateCounterT3) {
          targetStateCounterT3--;
        }

        switch (targetStateT3) {
          case 0: {
              updateLED(0);
              digitalWriteFast(5, LOW);
              break;
            }
          case 1: {
              updateLED(1);
              digitalWriteFast(5, LOW);
              debounceBufferT3 <<= 1;
              if (digitalReadFast(4)) {
                debounceBufferT3 |= 1;                              // detect current pin state. add current state to buffer.
              }
              if ((debounceBufferT3 & 0xC002) == DEBOUNCE_MASK) {  // mask middle bits and compare to the mask - 11000011 = detected.
                scoreT3++;                                         // detected a hit, increase the score and
                targetStateT3 = 2;
                targetStateCounterT3 = LED_HIT_DURATION;           // move to the 'Hit' state.
                debounceBufferT3 = 0;
              }
              break;
            }
          case 2: {
              updateLED(2);
              digitalWriteFast(5, HIGH);                                  // Active - Hit
              if (!targetStateCounterT3) {
                targetStateT3 = 1;
                digitalWriteFast(5, LOW);
              }
            }
            break;
        }
        break;
      }
  }
}

void updateLED(int mode) {

  int updateRequired = 0;
  static int ledCounter = 0;
  static int ledSetOnce = 0;
  static int prevMode;
  int red = 0;
  int grn = 0;
  int blu = 0;

  if (ledCounter) {
    ledCounter--;
  }
  if (mode != prevMode) {
    ledSetOnce = 0;
  }
  prevMode = mode;

  switch (mode) {
    case 0: {
        if (!ledSetOnce) {
          for (int i = 0; i < LED_MAX; i++) {
            ledBuffer[i] = 0x00000000;               // Off
          }
          ledSetOnce = 1;
          updateRequired = 1;
        }
        break;
      }
    case 1: {         //  White ring
        if (!ledCounter) {                           // when counter hits 0 time to move LED
          ledCounter = LED_CYCLE_RATE;               // set the counter back to the cycle time
          ledPosition++;                             // move the led position by 1
          if (ledPosition > LED_MAX) {               // if led position is greater than max number of leds
            ledPosition = 0;                         // set it back to 0 to start over
          }
          for (int i = 0; i < LED_MAX; i++) {         // load up the led buffer
            if (i == ledPosition) {                  // if buffer position = current led position
              ledBuffer[i] = 0x00FFFFFF;             // set the led at current position to white.
            }
            else {                                    // if not current led postion
              ledBuffer[i] = 0x00000000;             // turn the led off.
            }
          }
          updateRequired = 1;
        }
        break;
      }
    case 2: {         //  Full Red
        if (!ledSetOnce) {
          for (int i = 0; i < LED_MAX; i++) {
            ledBuffer[i] = 0x00FF0000;               // Red
          }
          ledSetOnce = 1;
          updateRequired = 1;
        }
        break;
      }
  }

  if (updateRequired) {
    for (int i = 0; i < LED_MAX; i++) {
      blu = ledBuffer[i] & 0x000000FF;
      grn = (ledBuffer[i] >> 8) & 0x000000FF;
      red = (ledBuffer[i] >> 16) & 0x000000FF;
      switch (activeTarget) {
        case 0: {
            sendDataT0(red, grn, blu);
            break;
          }
        case 1: {
            sendDataT1(red, grn, blu);
            break;
          }
        case 2: {
            sendDataT2(red, grn, blu);
            break;
          }
        case 3: {
            sendDataT3(red, grn, blu);
            break;
          }
      }

    }
  }
}

void sendDataT0(int r, int g, int b) {

  long rgbData = 0;

  rgbData = r;
  rgbData <<= 8;
  rgbData |= g;
  rgbData <<= 8;
  rgbData |= b;
  rgbData &= 0x00FFFFFF;

  for (int x = 0; x < 24; x++) {
    if (rgbData & (1 << (24 - x))) {
      digitalWriteFast(3, HIGH);          // DATA PIN
    }
    else {
      digitalWriteFast(3, LOW);           // DATA PIN
    }
    digitalWriteFast(2, HIGH);            // CLOCK PIN
    digitalWriteFast(2, LOW);             // CLOCK PIN
  }
}

void sendDataT1(int r, int g, int b) {

  long rgbData = 0;

  rgbData = r;
  rgbData <<= 8;
  rgbData |= g;
  rgbData <<= 8;
  rgbData |= b;
  rgbData &= 0x00FFFFFF;

  for (int x = 0; x < 24; x++) {
    if (rgbData & (1 << (24 - x))) {
      digitalWriteFast(3, HIGH);
    }
    else {
      digitalWriteFast(3, LOW);
    }
    digitalWriteFast(2, HIGH);
    digitalWriteFast(2, LOW);
  }
}

void sendDataT2(int r, int g, int b) {

  long rgbData = 0;

  rgbData = r;
  rgbData <<= 8;
  rgbData |= g;
  rgbData <<= 8;
  rgbData |= b;
  rgbData &= 0x00FFFFFF;

  for (int x = 0; x < 24; x++) {
    if (rgbData & (1 << (24 - x))) {
      digitalWriteFast(3, HIGH);
    }
    else {
      digitalWriteFast(3, LOW);
    }
    digitalWriteFast(2, HIGH);
    digitalWriteFast(2, LOW);
  }
}

void sendDataT3(int r, int g, int b) {

  long rgbData = 0;

  rgbData = r;
  rgbData <<= 8;
  rgbData |= g;
  rgbData <<= 8;
  rgbData |= b;
  rgbData &= 0x00FFFFFF;

  for (int x = 0; x < 24; x++) {
    if (rgbData & (1 << (24 - x))) {
      digitalWriteFast(3, HIGH);
    }
    else {
      digitalWriteFast(3, LOW);
    }
    digitalWriteFast(2, HIGH);
    digitalWriteFast(2, LOW);
  }
}

