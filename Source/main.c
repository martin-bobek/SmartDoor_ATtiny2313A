#include "util.h"
#include "buttons.h"
#pragma vector=TIMER0_COMPA_vect
__interrupt void SysTick_Handler(void);
#pragma inline=forced
static void SystemInit(void);
#pragma inline=forced
static void SystemSleep(void);

static uint8_t G_SysTick=0;
static uint8_t G_ExpectSysTick=0;

int main(void) {
  
  SystemInit();
  
  while(1) {
    
    HEARTBEAT_ON();

    ButtonService();
    
    HEARTBEAT_OFF();
    SystemSleep();
  }
  
}

//output to mega: 19/17
#pragma vector=TIMER0_COMPA_vect
__interrupt void SysTick_Handler() {
  
  
  
  G_SysTick++;
}
static void SystemInit() {
  
  PORTD = HEARTBEATPIN;
  MCUCR = MSK(SE);                      //enable sleep mode
  TCCR0A = MSK(WGM01);                  //
  OCR0A = 0x7c;                         //compare pin for 
  
  TIMSK = MSK(OCIE0A);
  TCCR0B = MSK(CS01) | MSK(CS00);
  
  asm("SEI");
}

static void SystemSleep() {
  
  if(G_SysTick != G_ExpectSysTick) {
    asm("CLI");
    while(1);
  }
  
  while(G_SysTick == G_ExpectSysTick) {
    asm("SLEEP");
  }
  
  G_ExpectSysTick++;
}