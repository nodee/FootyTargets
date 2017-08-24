#include <TimerOne.h>
#include <digitalWriteFast.h>

#define DEBOUNCE_MASK 0xC002
#define LED_CYCLE_RATE 3        // LED_CYCLE_RATE * 5ms - Speed of LED ring
#define LED_MAX 24              // Number of LEDs in ring
#define LED_HIT_DURATION 200    // LED_HIT_DURATION * 5ms

#define TARGET_0_CLK 2
#define TARGET_0_DAT 3
#define TARGET_0_BUZ 4
#define TARGET_0_NOK 5

#define TARGET_1_CLK 6
#define TARGET_1_DAT 7
#define TARGET_1_BUZ 8
#define TARGET_1_NOK 9

#define TARGET_2_CLK 10
#define TARGET_2_DAT 11
#define TARGET_2_BUZ 12
#define TARGET_2_NOK 13

#define TARGET_3_CLK 14
#define TARGET_3_DAT 15
#define TARGET_3_BUZ 16
#define TARGET_3_NOK 17

int activeTarget = 0;
int score = 0;
int changeTarget = 0;

int systemCounter = 0;

void setup() {
  pinMode(TARGET_0_DAT, OUTPUT);
  pinMode(TARGET_0_CLK, OUTPUT);
  pinMode(TARGET_0_BUZ, OUTPUT);
  pinMode(TARGET_0_NOK, INPUT);

  pinMode(TARGET_1_DAT, OUTPUT);
  pinMode(TARGET_1_CLK, OUTPUT);
  pinMode(TARGET_1_BUZ, OUTPUT);
  pinMode(TARGET_1_NOK, INPUT);
  
  pinMode(TARGET_2_DAT, OUTPUT);
  pinMode(TARGET_2_CLK, OUTPUT);
  pinMode(TARGET_2_BUZ, OUTPUT);
  pinMode(TARGET_2_NOK, INPUT);
  
  pinMode(TARGET_3_DAT, OUTPUT);
  pinMode(TARGET_3_CLK, OUTPUT);
  pinMode(TARGET_3_BUZ, OUTPUT);
  pinMode(TARGET_3_NOK, INPUT);

  Timer1.initialize(5000);
  Timer1.attachInterrupt(targetUpdate);
}

void loop() {

  if(changeTarget || !systemCounter){   // if score has changed (hit detected) or the counter has hit 0
      changeTarget = 0;
      activeTarget = random(0,4);               // generate random target between 0 and 3
      systemCounter = 2000;                     // value * 5ms before next target 2000 * 5ms = 10seconds
  }
  

}

void targetUpdate() {

  // 'static' variables are not lost when the function completes 
  // and the values are save until next time the function is called. 
  
  static int lastTarget = 0;
  int temp_activeTarget = 0;
  
  static int hitDetected = 0;
  static int hitCounter = 0;
  
  static int ledCounter = 0;
  static int ledPosition = 0;
  
  static int debounceBuffer = 0;

  if(systemCounter){
    systemCounter--;
  }
  
  if (activeTarget != lastTarget) {                       //
    temp_activeTarget = activeTarget;                     // 
    activeTarget = lastTarget;                            //    Switch active target to previous target
    for (int i = 0; i < LED_MAX; i++) {                   //
      sendData(0,0,0);                                    //    Set all LEDs to OFF
    }                                                     //                         
    activeTarget = temp_activeTarget;                     //    Restore active target     
                                                          //
    hitCounter = 0;                                       // 
    hitDetected = 0;                                      //
    ledCounter = 0;                                       //
    ledPosition = 0;                                      //
    debounceBuffer = 0;                                   //
  }                                                       //
  lastTarget = activeTarget;                              //

  if (!hitDetected) {                                     //
    debounceBuffer <<= 1;                                 //
    if (activeTarget == 0) {                              //
      if (digitalReadFast(TARGET_0_NOK)) {                //
        debounceBuffer |= 1;                              // detect current pin state. add current state to buffer.
      }
    }
    else if (activeTarget == 1) {
      if (digitalReadFast(TARGET_1_NOK)) {
        debounceBuffer |= 1;                              // detect current pin state. add current state to buffer.
      }
    }
    else if (activeTarget == 2) {
      if (digitalReadFast(TARGET_2_NOK)) {
        debounceBuffer |= 1;                              // detect current pin state. add current state to buffer.
      }
    }
    else if (activeTarget == 3) {
      if (digitalReadFast(TARGET_3_NOK)) {
        debounceBuffer |= 1;                              // detect current pin state. add current state to buffer.
      }
    }
    
    // mask middle bits and compare to the mask - 1100000000000011 = detected.
    if ((debounceBuffer & 0xC002) == DEBOUNCE_MASK) {     // HIT DETECTED!
      score++;                                            // detected a hit
      debounceBuffer = 0;                                 // clear buffer
      hitCounter = LED_HIT_DURATION;                      // 
      hitDetected = 1;                                    //
      for (int i = 0; i < LED_MAX; i++) {                 //
        sendData(0xff,0,0);                               // Red
      }                                                   //
    }                                                     //
    else {                                                // NO HIT DETECTED
      if (ledCounter) {                                   //
        ledCounter--;                                     //
      }                                                   //
      if (!ledCounter) {                                  // when counter hits 0 time to move LED
        ledCounter = LED_CYCLE_RATE;                      // set the counter back to the cycle time
        ledPosition++;                                    // move the led position by 1
        if (ledPosition > LED_MAX) {                      // if led position is greater than max number of leds
          ledPosition = 0;                                // set it back to 0 to start over
        }                                                 //
        for (int i = 0; i < LED_MAX; i++) {               // 
          if (i == ledPosition) {                         // 
            sendData(0xFF, 0xFF, 0xFF);                   //
          }                                               //
          else {                                          //
            sendData(0x00, 0x00, 0x00);                   //
          }
        }
      }
    }
  }
  else {
    enableBuzzer();                                 // Active - Hit
    if (hitCounter) {
      hitCounter--;
    }
    if (!hitCounter) {
      hitDetected = 0;
      disableBuzzer();
      changeTarget = 1;
    }
  }
}

void enableBuzzer() {
  switch (activeTarget) {
    case 0: {digitalWriteFast(TARGET_0_BUZ, HIGH);break;}
    case 1: {digitalWriteFast(TARGET_1_BUZ, HIGH);break;}
    case 2: {digitalWriteFast(TARGET_2_BUZ, HIGH);break;}
    case 3: {digitalWriteFast(TARGET_3_BUZ, HIGH);break;}
  }
}
void disableBuzzer() {
  digitalWriteFast(TARGET_0_BUZ, LOW);
  digitalWriteFast(TARGET_1_BUZ, LOW);
  digitalWriteFast(TARGET_2_BUZ, LOW);
  digitalWriteFast(TARGET_3_BUZ, LOW);
}

void sendData(int r, int g, int b) {

  long rgbData = 0;

  rgbData = r;
  rgbData <<= 8;
  rgbData |= g;
  rgbData <<= 8;
  rgbData |= b;
  rgbData &= 0x00FFFFFF;

  for (int x = 0; x < 24; x++) {
    if (rgbData & (1 << (24 - x))) {
      if (activeTarget == 0) {
        digitalWriteFast(TARGET_0_DAT, HIGH);
      }
      if (activeTarget == 1) {
        digitalWriteFast(TARGET_1_DAT, HIGH);
      }
      if (activeTarget == 2) {
        digitalWriteFast(TARGET_2_DAT, HIGH);
      }
      if (activeTarget == 3) {
        digitalWriteFast(TARGET_3_DAT, HIGH);
      }
    }
    else {
      if (activeTarget == 0) {
        digitalWriteFast(TARGET_0_DAT, LOW);
      }
      if (activeTarget == 1) {
        digitalWriteFast(TARGET_1_DAT, LOW);
      }
      if (activeTarget == 2) {
        digitalWriteFast(TARGET_2_DAT, LOW);
      }
      if (activeTarget == 3) {
        digitalWriteFast(TARGET_3_DAT, LOW);
      }
    }
    if (activeTarget == 0) {
      digitalWriteFast(TARGET_0_CLK, HIGH);            // CLOCK PIN
      digitalWriteFast(TARGET_0_CLK, LOW);             // CLOCK PIN
    }
    if (activeTarget == 1) {
      digitalWriteFast(TARGET_1_CLK, HIGH);            // CLOCK PIN
      digitalWriteFast(TARGET_1_CLK, LOW);             // CLOCK PIN
    }
    if (activeTarget == 2) {
      digitalWriteFast(TARGET_2_CLK, HIGH);            // CLOCK PIN
      digitalWriteFast(TARGET_2_CLK, LOW);             // CLOCK PIN
    }
    if (activeTarget == 3) {
      digitalWriteFast(TARGET_3_CLK, HIGH);            // CLOCK PIN
      digitalWriteFast(TARGET_3_CLK, LOW);             // CLOCK PIN
    }
  }
}
