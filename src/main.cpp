#include <TimerThree.h>
#include <FootyTarget.h>

FTarget t1(A9,3,2,14);
/*FTarget t2(A8,5,4,15);
FTarget t3(A7,7,6,16);*/

void updateTargets(void);

void setup(void){
  Timer3.attachInterrupt(updateTargets, 20000);
  Serial.begin(115200);
}

void loop(void){

  t1.enable();
  Serial.println("Target 1 - Enabled");
  delay(8000);
  t1.disable();
  Serial.println("Target 1 - Disabled");
  Serial.print("Target 1 - Score: ");
  Serial.println(t1.getScore());
  t1.resetScore();

  /*delay(2000);

  t2.enable();
  Serial.println("Target 2 - Enabled");
  delay(8000);
  t2.disable();
  Serial.println("Target 2 - Disabled");
  Serial.print("Target 2 - Score: ");
  Serial.println(t2.getScore());
  t2.resetScore();

  delay(2000);

  t3.enable();
  Serial.println("Target 3 - Enabled");
  delay(8000);
  t3.disable();
  Serial.println("Target 3 - Disabled");
  Serial.print("Target 3 - Score: ");
  Serial.println(t3.getScore());
  t3.resetScore();
*/
  delay(2000);
}

void updateTargets(void){
  t1.update();
  //t2.update();
  //t3.update();
}
