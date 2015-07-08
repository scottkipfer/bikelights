elapsedMicros LEDTimer1;
elapsedMicros LEDTimer2;
elapsedMicros LEDTimer3;

bool LEDTimer1_isEnabled = true;
bool LEDTimer2_isEnabled = false;
bool LEDTimer3_isEnabled = false;

const long TIMED_OUT = 1000000; // 1 second

void resetLEDTimer1(void) {
  LEDTimer1 = 0;
}

void resetLEDTimer2(void) {
  LEDTimer2 = 0;
}

void resetLEDTimer3(void) {
  LEDTimer3 = 0;
}

void resetALLTimers(void){
  resetLEDTimer1();
  resetLEDTimer2();
  resetLEDTimer3();
}

void switchLEDTimers(void){
  if(isLEDTimer1Enabled() && !isLEDTimer2Enabled() && !isLEDTimer3Enabled()){
    resetLEDTimer2();
    enableLEDTimer2();
  } else if(isLEDTimer1Enabled() && isLEDTimer2Enabled() && !isLEDTimer3Enabled()){
    resetLEDTimer3();
    enableLEDTimer3();
    disableLEDTimer1();
    Serial.println("2 and 3");
  } else if(!isLEDTimer1Enabled() && isLEDTimer2Enabled() && isLEDTimer3Enabled()){
    resetLEDTimer1();
    enableLEDTimer1();
    disableLEDTimer2();
    Serial.println("3 and 1");
  } else if(isLEDTimer1Enabled() && !isLEDTimer2Enabled() && isLEDTimer3Enabled()){
    resetLEDTimer2();
    enableLEDTimer2();
    disableLEDTimer3();
    Serial.println("1 and 2");
  }
}

bool isSpeedTimerTimedOut(void) {
  if (LEDTimer1 > TIMED_OUT) {
    return true;
  } else {
    return false;
  }
}

long getLEDTimer1Value(void) {
  return LEDTimer1;
}

long getLEDTimer2Value(void) {
  return LEDTimer2;
}

long getLEDTimer3Value(void) {
  return LEDTimer3;
}

boolean isLEDTimer1Enabled(void){
  return LEDTimer1_isEnabled;
}
boolean isLEDTimer2Enabled(void){
  return LEDTimer2_isEnabled;
}
boolean isLEDTimer3Enabled(void){
  return LEDTimer3_isEnabled;
}

void enableLEDTimer1(void){
  LEDTimer1_isEnabled = true;
}

void enableLEDTimer2(void){
  LEDTimer2_isEnabled = true;
}
void enableLEDTimer3(void){
  LEDTimer3_isEnabled = true;
}

void disableLEDTimer1(void){
  LEDTimer1_isEnabled = false;
}

void disableLEDTimer2(void){
  LEDTimer2_isEnabled = false;
}
void disableLEDTimer3(void){
  LEDTimer3_isEnabled = false;
}

