#include "pdm.pio.h"
#include "SDM.h"

PIO pio = pio1;
uint sm;
const uint16_t sampleRate = 48000;
int16_t sig[sampleRate];

void setup() {

  // set new clock that is intger multiple of 48000*32
  uint32_t newClock = 153600;
  set_sys_clock_khz(newClock, false);

 //begin serial after clocks set
  Serial.begin(115200);
  Serial.println("hello");

  // signal to be modulated
  for (int i = 1; i < (sampleRate + 1); i++) {
    sig[i - 1] = (int16_t)(sin(2.0 * PI * 1000 * i / sampleRate) * 32767 * 1);
  }

  uint32_t result;
  uint32_t beg;
  uint32_t end;

  // the class
  SDM sdm;

  // first run
  beg = micros();
  for (uint16_t i = 0; i < sampleRate; i++) {
    result = sdm.o4_os32(sig[i]);
  }
  end = micros();
  Serial.println(end - beg);

  // second run is so to ensure compiler doesnt optimise caculations away;
  beg = micros();
  for (uint16_t i = 0; i < sampleRate; i++) {
    result = sdm.o4_os32(sig[i]);
  }
  end = micros();
  Serial.println(end - beg);
  
}

void loop(){
    
}