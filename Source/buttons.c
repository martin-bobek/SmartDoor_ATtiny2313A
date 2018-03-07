#include "buttons.h"

#define BUT1    MSK(0)
#define BUT2    MSK(1)
#define BUT3    MSK(2)
#define BUT4    MSK(3)

uint8_t Buttons;

void ButtonService() {
  
   uint8_t tempB = PINB;
   static uint8_t time1 = 0;
   static uint8_t time2 = 0;
   static uint8_t time3 = 0;
   static uint8_t time4 = 0;
   
   if(((tempB & BUTTON1B) == 0) != ((G_Status & BUTTON1_FLAG)!=0)) {
     time1++;
     if(time1 == 20) {
       G_Status ^= BUTTON1_FLAG;
       time1 = 0;
     }
   }
   else {
     time1 = 0;
   }
   //////////////////////////////////////////////////////////////
   if(((tempB & BUTTON2B) == 0) != ((G_Status & BUTTON2_FLAG)!=0)) {
     time2++;
     if(time2 == 20) {
       G_Status ^= BUTTON2_FLAG;
       time2 = 0;
     }
   }
   else {
     time2 = 0;
   }
   /////////////////////////////////////////////////////////////
   if(((tempB & BUTTON3B) == 0) != ((G_Status & BUTTON3_FLAG)!=0)) {
     time3++;
     if(time3 == 20) {
       G_Status ^= BUTTON3_FLAG;
       time3 = 0;
     }
   }
   else {
     time3 = 0;
   }
   ////////////////////////////////////////////////////////////
   uint8_t tempD = PIND;
   if(((tempD & BUTTON1D) == 0) != ((G_Status & BUTTON4_FLAG)!=0)) {
     time4++;
     if(time4 == 20) {
       G_Status ^= BUTTON4_FLAG;
       time4 = 0;
     }
   }
   else {
     time4 = 0;
   }
}