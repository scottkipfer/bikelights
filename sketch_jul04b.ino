
// Create an IntervalTimer object 
IntervalTimer myTimer;
IntervalTimer longerTimer;
const long usbUpdateRate = 1000000;

elapsedMicros timer;
const long sensorBlinkRate = 100000;

//////////////////////////////////////////////////////   Typedefs  //////////////////////////////////////////////////////

const int ledPin = 6;  // the pin with a LED
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
const int sensorPin = 3; 
int sensor_state = 0;

void setup() {
  // put your setup code here, to run once:
  initalizeSpeedBuffer();
  initLEDs();
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  attachInterrupt(sensorPin, register_high, RISING);
  Serial.begin(9600);
  myTimer.begin(blinkLED, sensorBlinkRate);
  longerTimer.begin(printTime,usbUpdateRate);
}

// The interrupt will blink the LED, and keep
// track of how many times it has blinked.
int ledState = LOW;
int ledState2 = LOW;
volatile unsigned long blinkCount = 0; // use volatile for shared variables

void register_high() {
  addToSpeedBuffer(timer);
  switchLEDTimers();
  timer = 0;
}
// functions called by IntervalTimer should be short, run as quickly as
// possible, and should avoid calling other functions if possible.
void blinkLED(void) {
  if (ledState == LOW) {
    ledState = HIGH;
  } else {
    ledState = LOW;
  }
  if(digitalRead(sensorPin)){
    sensor_state = 1;
  } else {
    sensor_state =0;
  }
  delayMicroseconds(100);
  digitalWrite(ledPin, ledState);

  //Serial.println(timer);
}

void loop(void) {
  LED_Controller();
  noInterrupts();
  interrupts();
}

void printTime(void){
  long time;
  time = calculateTime();
  Serial.printf("Sensor %d",time);
  Serial.println("");
}




