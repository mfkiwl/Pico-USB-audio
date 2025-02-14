#include "pdm.pio.h"
#include "SDM.h"

PIO pio = pio1;
uint sm;
const uint16_t sampleRate = 48000;
int16_t sig[sampleRate];

void setup() {

  // set new clock that is intger multiple of 48000*64
  uint32_t newClock = 230400;
  set_sys_clock_khz(newClock, false);

  //begin serial after clocks set
  Serial.begin(115200);
  Serial.println("hello");

  // signal to be modulated
  for (int i = 1; i < (sampleRate + 1); i++) {
    sig[i - 1] = (int16_t)(sin(2.0 * PI * 1000 * i / sampleRate) * 32767 * 1);
  }

  volatile uint32_t result;
  uint32_t end;
  uint32_t beg;
  // the class
  SDM sdm;



  // direct form 2;
  beg = micros();
  for (uint16_t i = 0; i < sampleRate; i++) {
    result = sdm.o4_os32_df2(sig[i]);
  }
  Serial.println(micros() - beg);

  // direct  form 1
  beg = micros();
  for (uint16_t i = 0; i < sampleRate; i++) {
    result = sdm.o4_os32(sig[i]);
  }
  Serial.println(micros() - beg);

  // direct  form 2 64Xoversampling
  volatile uint32_t result1;
  volatile uint32_t result2;

  SDM sdm2;
  beg = micros();
  for (uint16_t i = 0; i < sampleRate; i++) {
    result1 = sdm.o4_os32_df2(sig[i]);
    result2 = sdm.o4_os32_df2(sig[i]);
  }
  Serial.println(micros() - beg);
}

void loop() {
}