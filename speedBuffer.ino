//////////////////////////////////////////////////////   Defines  //////////////////////////////////////////////////////
const int MAX_BUFFER_SIZE = 10;

typedef struct speedCircularBuffer_t {
  volatile int head;
  bool isValid;
  long data[MAX_BUFFER_SIZE];
}circularBuffer_t;

/******************************************************************************************************
 *                                      Private Variables
 *****************************************************************************************************/
speedCircularBuffer_t speedBuffer;

/******************************************************************************************************
 *                                      Public Functions
 ******************************************************************************************************/
void initalizeSpeedBuffer(void){
  int index;
  speedBuffer.head = 0;
  speedBuffer.isValid = false;
  for(index = 0; index < MAX_BUFFER_SIZE; index++){
    speedBuffer.data[index] = 0;
  }
}

void addToSpeedBuffer(long data) {
  speedBuffer.data[speedBuffer.head] = data;
  speedBuffer.head++;
  if(speedBuffer.head == MAX_BUFFER_SIZE) {
    speedBuffer.head = 0;
    speedBuffer.isValid = true;
  }
}

long calculateTime(void) {
  int index;
  int average_time = 0;
  if(speedBufferIsValid()){
    for(index = 0; index < MAX_BUFFER_SIZE; index++){
      average_time = average_time + speedBuffer.data[index];
    }
    average_time = average_time / MAX_BUFFER_SIZE;
    return average_time;
  } else {
    return 0;
  }
}

bool speedBufferIsValid(void) {
  if(speedBuffer.isValid){
    return true;
  } else {
    return false;
  }
}



