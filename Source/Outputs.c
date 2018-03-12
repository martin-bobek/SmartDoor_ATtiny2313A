#include "Outputs.h"

void OutputService(uint8_t Butts, uint8_t Sens) {
  
  USIDR = Butts | (Sens << 4);
}