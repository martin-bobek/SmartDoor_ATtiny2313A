#include "IR.h"

typedef enum {IRON = 0, IROFF, IREND = 10 } IRStates;

static void IRService(void);

static void IRService() {
   static uint8_t t1 = 0;
   static uint8_t t2 = 0;
   static uint8_t t3 = 0;
   static uint8_t t4 = 0;
   
   uint8_t tempIR = PIND;
   
   if(((tempIR & SENSOR1_D) == 0) != ((G_Status & IR1_FLAG)!=0)) {
     t1++;
     if(t1 == 10) {
       G_Status ^= IR1_FLAG;
       t1 = 0;
     }
   }
   else {
     t1 = 0;
   }
   //////////////////////////////////////////////////////////////
   if(((tempIR & SENSOR2_D) == 0) != ((G_Status & IR2_FLAG)!=0)) {
     t2++;
     if(t2 == 10) {
       G_Status ^= IR2_FLAG;
       t2 = 0;
     }
   }
   else {
     t2 = 0;
   }
   /////////////////////////////////////////////////////////////
   if(((tempIR & SENSOR3_D) == 0) != ((G_Status & IR3_FLAG)!=0)) {
     t3++;
     if(t3 == 10) {
       G_Status ^= IR3_FLAG;
       t3 = 0;
     }
   }
   else {
     t3 = 0;
   }
   ////////////////////////////////////////////////////////////
   if(((tempIR & SENSOR4_D) == 0) != ((G_Status & IR4_FLAG)!=0)) {
     t4++;
     if(t4 == 10) {
       G_Status ^= IR4_FLAG;
       t4 = 0;
     }
   }
   else {
     t4 = 0;
   }
}

void IRDrive() {
  static IRStates state = IRON;
  
  switch(state) {
    case IRON:
      TCCR1A = MSK(COM1A1) | MSK(COM1B1) | MSK(COM1A0) | MSK(COM1B0);
      break;
    
    case IROFF:
      IRService();
      TCCR1A = 0;
      break;
  }
  
  state++;
  if (state == IREND)
    state = IRON;
}
