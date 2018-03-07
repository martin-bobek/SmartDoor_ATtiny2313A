#include "util.h"
#include "buttons.h"

uint8_t G_Status;

#pragma vector=TIMER0_COMPA_vect
__interrupt void SysTick_Handler(void);
#pragma inline=forced
static void SystemInit(void);
#pragma inline=forced
static void SystemSleep(void);

static volatile uint8_t G_SysTick;
static uint8_t G_ExpectSysTick;

__C_task void main(void) {  
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
__interrupt void SysTick_Handler(void) {
  G_SysTick++;
}

static void SystemInit() {
  DDRD = HEARTBEATPIN;
  MCUCR = MSK(SE);                      //enable sleep mode
  
  USISR = MSK(USISIF) | MSK(USIOIF);    // clears interrupts before turning on USI and enabling interrupts and clears counter
  USICR = MSK(USISIE) | MSK(USIWM1) | MSK(USICS1);        // turns on usi in twi mode
  PORTB = TWISCL_B;                     // when USI is enabled and output driver is enabled, the pin is driven open collector (low when port is 0)
  DDRB = TWISCL_B;                      // enables output driver on SCL pin

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