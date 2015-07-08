#define NUMBER_OF_LEDS 10
#define ON_TIME_PERCENT 20
#define OFF_TIME_PERCENT 60

typedef struct LED_t {
  int Pin_Number;
  long onTime;
  long offTime;
  long (*getTimerFunc)();
  boolean (*isTimerEnabledFunc)();
}LED_t;

LED_t LEDArray[NUMBER_OF_LEDS] = {
  // Pin Number
        14,   0,0,0,0, // LED 1
        15,   0,0,0,0, // LED 2
        16,   0,0,0,0, // LED 3
        17,   0,0,0,0, // LED 4
        18,   0,0,0,0, // LED 5
        19,   0,0,0,0, // LED 6
        20,   0,0,0,0, // LED 7
        21,   0,0,0,0, // LED 8
        22,   0,0,0,0, // LED 9
        23,   0,0,0,0, // LED 10
};

void initLEDs(void){
  int index;
  for(index =0; index < NUMBER_OF_LEDS; index++){
    pinMode(LEDArray[index].Pin_Number, OUTPUT);
    LEDArray[index].getTimerFunc = &getLEDTimer1Value;
    LEDArray[index].isTimerEnabledFunc = &isLEDTimer1Enabled;
  }
}

void LED_Controller(void){
  int index;
  long currentTimeSplit = calculateTime();
  for(index =0; index < NUMBER_OF_LEDS; index++){
    setLEDOnTime(index,currentTimeSplit);
    //Serial.printf("%u: ontime: %u, offtime: %u", index,LEDArray[index].onTime, LEDArray[index].offTime);
    //Serial.println("");
    updateLED(index);
  }
} 

void turnOnLED(int LEDIndex){
  digitalWrite(LEDArray[LEDIndex].Pin_Number,HIGH);
};

void turnOffLED(int LEDIndex){
  digitalWrite(LEDArray[LEDIndex].Pin_Number,LOW);
};

void switchLEDTimer(int LEDIndex){
  if(LEDArray[LEDIndex].getTimerFunc == &getLEDTimer1Value){
    LEDArray[LEDIndex].getTimerFunc = &getLEDTimer2Value;
    LEDArray[LEDIndex].isTimerEnabledFunc = &isLEDTimer2Enabled;
  } else if (LEDArray[LEDIndex].getTimerFunc == &getLEDTimer2Value) {
    LEDArray[LEDIndex].getTimerFunc = &getLEDTimer3Value;
    LEDArray[LEDIndex].isTimerEnabledFunc = &isLEDTimer3Enabled;
  } else {
    LEDArray[LEDIndex].getTimerFunc = &getLEDTimer1Value;
    LEDArray[LEDIndex].isTimerEnabledFunc = &isLEDTimer1Enabled;
  }
}

void updateLED(int LEDIndex){
  long currentTimerValue = LEDArray[LEDIndex].getTimerFunc();
  if(LEDArray[LEDIndex].isTimerEnabledFunc()){
    if(currentTimerValue > LEDArray[LEDIndex].onTime && currentTimerValue < LEDArray[LEDIndex].offTime ){
      turnOnLED(LEDIndex);
    } else if(currentTimerValue > LEDArray[LEDIndex].offTime) {
      turnOffLED(LEDIndex);
      switchLEDTimer(LEDIndex);
    } else {
      turnOffLED(LEDIndex);
    }
  }
}

void setLEDOnTime(int LEDIndex, long currentTimeSplit){
    long offset = ((currentTimeSplit * (360) / (NUMBER_OF_LEDS * 360)) * LEDIndex);
    long on_time = (currentTimeSplit * ON_TIME_PERCENT / 100) + offset;
    long off_time = (currentTimeSplit * OFF_TIME_PERCENT / 100) + offset;
    LEDArray[LEDIndex].onTime = on_time;
    LEDArray[LEDIndex].offTime = off_time;
}



