#include "FootyTarget.h"

FTarget::FTarget(int knockPin, int dataPin, int clockPin, int buzzerPin){
  _knockPin = knockPin;
  _dataPin = dataPin;
  _clockPin = clockPin;
  _buzzerPin = buzzerPin;
  _targetState = 0;
  _score = 0;
  updateLED(0);
}
void FTarget::enable(void){
  _targetState = 1;
  _debounceBuffer = 0;
  _targetStateCounter = 0;
  _ledCounter = 0;
  _ledPosition = 0;
}
void FTarget::disable(void){
  _targetState = 0;
}
void FTarget::resetScore(void){
  _score = 0;
}
int FTarget::getScore(void){
  return _score;
}
void FTarget::update(void){

  if(_targetStateCounter){
    _targetStateCounter--;
  }

  switch(_targetState){
    case 0:{                                            // Inactive
      updateLED(0);
      _buzzerPin = 0;
      break;
    }
    case 1:{                                            // Active - Detect
      updateLED(1);
      _buzzerPin = 0;
      _debounceBuffer <<= 1;
      _debounceBuffer |=  digitalRead(_knockPin);       // detect current pin state. add current state to buffer.
      if((_debounceBuffer & 0x00C2) == DEBOUNCE_MASK){  // mask middle bits and compare to the mask - 11000011 = detected.
        _score++;                                       // detected a hit, increase the score and
        _targetState = 2;
        _targetStateCounter = LED_HIT_DURATION;         // move to the 'Hit' state.
      }
      break;
    }
    case 2:{
      updateLED(2);
      _buzzerPin = 1;                                   // Active - Hit
      if(!_targetStateCounter){
        _targetState = 1;
        _buzzerPin = 0;
      }
      break;
    }
  }
}

void FTarget::updateLED(int mode){

  long mask;
  long colour;
  int update;
  static int ledCounter = 0;
  static int ledSetOnce = 0;
  static int prevMode;

  if(ledCounter){
    ledCounter--;
  }
  if(mode != prevMode){
    ledSetOnce = 0;
  }
  prevMode = mode;

  switch(mode){
    case 0:{
      if(!ledSetOnce){
        for(int i = 0; i < LED_MAX; i++){
          _ledBuffer[i] = 0x00000000;               // Off
        }
        ledSetOnce = 1;
        update = 1;
      }
    }
    case 1:{          //  White ring
      if(!_ledCounter){                             // when counter hits 0 time to move LED
        _ledCounter = LED_CYCLE_RATE;               // set the counter back to the cycle time
        _ledPosition++;                             // move the led position by 1
        if(_ledPosition > LED_MAX){                 // if led position is greater than max number of leds
          _ledPosition = 0;                         // set it back to 0 to start over
        }
        for(int i = 0; i < LED_MAX; i++){           // load up the led buffer
          if(i == _ledPosition){                    // if buffer position = current led position
            _ledBuffer[i] = 0x00FFFFFF;             // set the led at current position to white.
          }
          else{                                     // if not current led postion
            _ledBuffer[i] = 0x00000000;             // turn the led off.
          }
        }
        update = 1;
      }
      break;
    }
    case 2:{          //  Full Red
      if(!ledSetOnce){
        for(int i = 0; i < LED_MAX; i++){
          _ledBuffer[i] = 0x00FF0000;               // Red
        }
        ledSetOnce = 1;
        update = 1;
      }
      break;
    }
  }

  if(update){
    digitalWriteFast(_clockPin, 0);
    digitalWriteFast(_dataPin, 0);
    for (int x = 0; x < NUM_LEDS; x++){
      colour = _ledBuffer[x];
      mask = 0x80000000;
      for(int i = 0; i < 32; i++){
        if(mask & colour){
          digitalWriteFast(_dataPin, 1);
        }
        else{
          digitalWriteFast(_dataPin, 0);
        }
        digitalWriteFast(_clockPin , 1);
        delayMicroseconds(10);
        digitalWriteFast(_clockPin , 0);
        mask = mask >> 1;
      }
    }
    digitalWriteFast(_clockPin, 0);
    digitalWriteFast(_dataPin, 0);
  }
}
