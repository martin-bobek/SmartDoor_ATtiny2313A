#include "IR.h"

static void IRService(void);

#define SENSOR1    MSK(0)
#define SENSOR2    MSK(1)
#define SENSOR3    MSK(2)
#define SENSOR4    MSK(3)

uint8_t G_Sensors = 0;

typedef enum {IRON, IROFF } IRStates;

static void IRService() {
  
   uint8_t tempIR = PIND;
   static uint8_t t1 = 0;
   static uint8_t t2 = 0;
   static uint8_t t3 = 0;
   static uint8_t t4 = 0;
   
   if(((tempIR & SENSOR1) == 0) != ((Sensors & SENSOR1)!=0)) {
     t1++;
     if(t1 == 20) {
       Sensors ^= SENSOR1;
       t1 = 0;
     }
   }
   else {
     t1 = 0;
   }
   //////////////////////////////////////////////////////////////
   if(((tempIR & SENSOR2) == 0) != ((Sensors & SENSOR2)!=0)) {
     t2++;
     if(t2 == 20) {
       Sensors ^= SENSOR2;
       t2 = 0;
     }
   }
   else {
     t2 = 0;
   }
   /////////////////////////////////////////////////////////////
   if(((tempIR & SENSOR3) == 0) != ((Sensors & SENSOR3)!=0)) {
     t3++;
     if(t3 == 20) {
       Sensors ^= SENSOR3;
       t3 = 0;
     }
   }
   else {
     t3 = 0;
   }
   ////////////////////////////////////////////////////////////
   if(((tempIR & SENSOR4) == 0) != ((Sensors & SENSOR4)!=0)) {
     t4++;
     if(t4 == 20) {
       Sensors ^= SENSOR4;
       t4 = 0;
     }
   }
   else {
     t4 = 0;
   }
}



void IRDrive() {
  static IRStates state = IRON;
  static uint8_t IRTick;
  
  IRTick++;
  
  switch(IRStates) {
    case IRON:
      TCCR1A = MSK(COM1A1) | MSK(COM1B1) | MSK(COM1A0) | MSK(COM1B0);
      state = IROFF;
      break;
    
    case IROFF:
      IRService();
      TCCR1A ^= (MSK(COM1A1) | MSK(COM1B1) | MSK(COM1A0) | MSK(COM1B0));
      state = HOLD;
      break;
      
    case HOLD:
      if(IRTick == 9) {
        IRTick == 0;
        state = IRON;
      }
      break;
  }
}
