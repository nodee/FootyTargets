#include <TimerOne.h>
#include <FootyTarget.h>

FTarget t1(1,2,3,4);
FTarget t2(5,6,7,8);
FTarget t3(9,10,11,12);
FTarget t4(13,14,15,16);

void updateTargets(void);

void setup(void){
  Timer1.initialize(5000);                //5ms
  Timer1.attachInterrupt(updateTargets);
}

void loop(void){

}

void updateTargets(void){
  t1.update();
  t2.update();
  t3.update();
  t4.update();
}
